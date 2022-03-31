#include "include/parser.hpp"
#include <iostream>

// TODO: checar se o tamanho do int eh valido
bool Parser::isNumber(const string &str)
{
    size_t i = 0;

    // ignora o sinal de menos
    if (str[0] == '-')
        i++;

    for (; i < str.size(); i++)
    {
        if (isdigit(str[i]) == 0)
            return false;
    }
    return true;
}

vector<string> Parser::splitLine(string line)
{
    vector<string> words;

    string word;
    stringstream iss(line);

    // TODO: ver o caso de ter um comentario logo apos uma operacao ou operando eg. PUSH $R;comment here
    while (iss >> word)
    {
        if (word[0] == ';')
            break;
        words.push_back(word);
    }

    return words;
}

bool Parser::isStringValidInstruction(string instructionString)
{
    for (size_t i = ADD; i < JN; i++)
        if (instructionString == instructioString[i])
            return true;

    return false;
}

Operation Parser::convertLineToInst(string line, uint16_t lineCount, PreParser preParser)
{
    vector<string> words = splitLine(line);

    // caso de uma linha vazia ou so de comentario
    if (words.size() == 0)
        throw Comment;

    // caso de uma linha indentificada no pre parse
    if (find(preParser.lines.begin(), preParser.lines.end(), lineCount) != preParser.lines.end())
        throw Comment;

    for (auto &&c : words[0])
        c = toupper(c);

    if (!isStringValidInstruction(words[0]))
        throw InvalidInstruction;

    if (words[0] == instructioString[PUSH])
    {
        if (words.size() != 2)
            throw SyntaxError;

        if (words[1] == "$R")
            return (Operation){lineCount, PUSHR, 0};

        if (!isNumber(words[1]))
        {
            auto constantIterator = preParser.constants.find(words[1]);
            if (constantIterator == preParser.constants.end())
                throw InvalidArgument;

            return (Operation){lineCount, PUSH, constantIterator->second};
        }

        return (Operation){lineCount, PUSH, stoi(words[1])};
    }
    else if (words[0] == instructioString[JMP] || words[0] == instructioString[JZ] || words[0] == instructioString[JN])
    {
        if (words.size() != 2)
            throw SyntaxError;

        if (!isNumber(words[1]))
            throw InvalidArgument;

        Instruction instructon = words[0] == instructioString[JMP] ? JMP : words[0] == instructioString[JZ] ? JZ
                                                                                                            : JN;
        return (Operation){lineCount, instructon, stoi(words[1])};
    }
    else if (words.size() > 1)
        throw SyntaxError;

    for (size_t i = ADD; i < PUSHR; i++)
        if (words[0] == instructioString[i])
            return (Operation){lineCount, (Instruction)i, 0};

    return (Operation){lineCount, ADD, 0}; // default return
}

PreParser Parser::preParse(ifstream &input)
{
    PreParser res;
    uint16_t lineCount = 0;

    input.clear();
    input.seekg(0, ios::beg);

    for (string line; getline(input, line);)
    {
        vector<string> words = splitLine(line);
        lineCount++;

        // CONSTANT_NAME EQU expression
        if (words.size() == 3)
        {
            for (auto &&c : words[1])
                c = toupper(c);

            if (words[1] == CONSTANT_WORD && isNumber(words[2]))
            {
                res.constants[words[0]] = stoi(words[2]);
                res.lines.push_back(lineCount);
            }

            continue;
        }

        // LABEL:
        if (words.size() == 1 && words[0].back() == ':')
        {
            words[0].pop_back();

            if (res.labels.find(words[0]) != res.labels.end())
                throw RepeatedLabel;

            res.labels[words[0]] = lineCount;
            res.lines.push_back(lineCount);
            continue;
        }
    }

    input.clear();
    input.seekg(0, ios::beg);

    return res;
}

vector<Operation> Parser::parseFile(string inputFile)
{
    ifstream input(inputFile);
    uint16_t lineCount = 0;
    vector<MachineStatus> status;
    vector<Operation> program;

    if (!input.good())
    {
        input.close();
        status.push_back({0, CouldNotReadFile});
        throw status;
    }

    PreParser preParser = preParse(input);

    for (string line; getline(input, line);)
    {
        lineCount++;
        try
        {
            Operation lineInst = convertLineToInst(line, lineCount, preParser);
            program.push_back(lineInst);
        }
        catch (const ErrorCode err)
        {
            if (err != Comment)
                status.push_back({lineCount, err});
        }
    }

    input.close();

    if (status.size() > 0)
        throw status;

    return program;
}

Parser::Parser()
{
}

Parser::~Parser()
{
}
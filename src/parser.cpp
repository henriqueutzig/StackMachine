#include "include/parser.hpp"

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
    for (size_t i = ADD; i < PUSHR; i++)
        if (instructionString == instructioString[i])
            return true;

    return false;
}

InstAndArg Parser::convertLineToInst(string line)
{
    vector<string> words = splitLine(line);

    // caso de uma linha vazia ou so de comentario
    if (words.size() == 0)
        throw Comment;

    if (!isStringValidInstruction(words[0]))
        throw InvalidInstruction;

    if (words[0] == instructioString[PUSH])
    {
        if (words.size() != 2)
            throw SyntaxError;

        if (words[1] == "$R")
            return (InstAndArg){PUSHR, 0};

        if (!isNumber(words[1]))
            throw InvalidArgument;

        return (InstAndArg){PUSH, stoi(words[1])};
    }
    else if (words.size() > 1)
        throw SyntaxError;

    for (size_t i = ADD; i < PUSHR; i++)
        if (words[0] == instructioString[i])
            return (InstAndArg){(Instruction)i, 0};

    return (InstAndArg){ADD, 0}; // default return
}

vector<ParserStatus> Parser::readProgram(string inputFile)
{
    ifstream inputEx(inputFile);
    uint32_t lineCount = 0;
    vector<ParserStatus> status;

    if (!inputEx.good())
    {
        inputEx.close();
        status.push_back({0, CouldNotReadFile});
        return status;
    }

    for (string line; getline(inputEx, line);)
    {
        lineCount++;
        try
        {
            InstAndArg lineInst = this->convertLineToInst(line);
            this->program.push_back(lineInst);
        }
        catch (const ParserError err)
        {
            if (err != Comment)
                status.push_back({lineCount, err});
        }
    }

    inputEx.close();
    return status;
}

vector<InstAndArg> Parser::getProgram()
{
    return this->program;
}

Parser::Parser()
{
}

Parser::~Parser()
{
}
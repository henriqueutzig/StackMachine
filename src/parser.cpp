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

InstAndArg Parser::convertLineToInst(string line, ParserStatus &lineStatus)
{
    vector<string> words = splitLine(line);

    // caso de uma linha vazia ou so de comentario
    if (words.size() == 0)
    {
        lineStatus.error = Comment;
        return (InstAndArg){ADD, 0};
    }

    if (!isStringValidInstruction(words[0]))
        lineStatus.error = InvalidInstruction;
    else if (words[0] == "PUSH")
    {
        if (words.size() != 2)
            lineStatus.error = SyntaxError;
        else if (words[1] == "$R")
            return (InstAndArg){PUSHR, 0};
        else if (isNumber(words[1]))
            return (InstAndArg){PUSH, stoi(words[1])};
        else
            lineStatus.error = InvalidArgument;
    }
    else if (words.size() > 1)
        lineStatus.error = SyntaxError;

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
        return vector<ParserStatus>({0});

    for (string line; getline(inputEx, line);)
    {
        ParserStatus lineStatus = {++lineCount, NoError};
        InstAndArg lineInst = this->convertLineToInst(line, lineStatus);

        if (lineStatus.error == NoError)
            this->program.push_back(lineInst);
        else if (lineStatus.error != Comment)
            status.push_back(lineStatus);
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
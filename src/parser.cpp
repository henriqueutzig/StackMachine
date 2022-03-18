#include "include/parser.hpp"

std::vector<std::string> Parser::splitLine(std::string line)
{
    std::vector<std::string> words;

    std::string word;
    std::stringstream iss(line);

    // Read and print each word.
    while (iss >> word)
    {
        if (word[0] == ';')
            break;
        words.push_back(word);
    }

    return words;
}

instAndArg Parser::convertLineToInst(std::string line, ParserError &status)
{
    std::vector<std::string> words = splitLine(line);
    
    if(words.size() == 2 && words[0] != "PUSH")
    {
        status = InvalidArgument;
    }


    return (instAndArg){AND, NoError};
}

ParserError Parser::readProgram(std::string inputFile)
{
    std::ifstream inputEx(inputFile);
    if (!inputEx.good())
        return CouldNotReadFile;

    for (std::string line; std::getline(inputEx, line);)
    {
        ParserError status = NoError;
        instAndArg lineInst = this->convertLineToInst(line, status);
        if (status != NoError)
            return status;

        this->program.push_back(lineInst);
    }

    inputEx.close();
    return NoError;
}

std::vector<instAndArg> Parser::getProgram()
{
    return this->program;
}

Parser::Parser()
{

}

Parser::~Parser()
{

}
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <exception>

#include "instructions.hpp"

using namespace std;

enum ParserError
{
    SyntaxError = 000,
    InvalidInstruction = 001,
    InvalidArgument = 002,
    CouldNotReadFile = 003,
    Comment = 254,
    NoError = 255
};

struct ParserStatus
{
    uint32_t line;
    ParserError error;
};

class Parser
{
private:
    static Operation convertLineToInst(string line);
    static bool isStringValidInstruction(string instructionString);
    static bool isNumber(const string &str);
    static vector<string> splitLine(string line);

public:
    // read
    static vector<Operation> parseFile(string inputFile);
    Parser(/* args */);
    ~Parser();
};

#endif
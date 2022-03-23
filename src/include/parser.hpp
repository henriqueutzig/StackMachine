#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <cstring>

#include "instructions.hpp"

using namespace std;

class Parser
{
private:
    static Operation convertLineToInst(string line, uint32_t lineCount);
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
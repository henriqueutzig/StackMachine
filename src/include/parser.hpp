#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include "instructions.hpp"

#define CONSTANT_WORD "EQU"

using namespace std;

struct PreParser
{
    unordered_map<string, int> constants;
    unordered_map<string, int> labels;
    vector<uint16_t> lines;
};

class Parser
{
private:
    static Operation convertLineToInst(string line, uint16_t fileLine, PreParser preParser);
    static bool isStringValidInstruction(string instructionString);
    static bool isNumber(const string &str);
    static vector<string> splitLine(string line);

    static PreParser preParse(ifstream &input);

public:
    // read
    static vector<Operation> parseFile(string inputFile);
    Parser();
    ~Parser();
};

#endif
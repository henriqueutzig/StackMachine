#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;

enum Instruction
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD, // Arithmetic
    NOT,
    OR,
    AND,
    MIR, // Logic
    PUSH,
    POP, // Control
    OUT, // IO
    CLEAR,
    PUSHR // overload de PUSH para argumento $R, "PUSHR" eh invalido no assembly
};

static const char *instructioString[] =
    {
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "MOD",
        "NOT",
        "OR",
        "AND",
        "MIR",
        "PUSH",
        "POP",
        "OUT",
        "CLEAR"};

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

typedef pair<Instruction, bitset<16>> InstAndArg;

class Parser
{
private:
    // vars
    vector<InstAndArg> program;
    vector<string> programLine;
    //
    InstAndArg convertLineToInst(string line, ParserStatus &lineStatus);
    bool isStringValidInstruction(string instructionString);
    bool isNumber(const string &str);
    vector<string> splitLine(string line);

public:
    // read
    vector<ParserStatus> readProgram(string inputFile);
    //
    vector<InstAndArg> getProgram();
    //
    Parser(/* args */);
    ~Parser();
};

#endif
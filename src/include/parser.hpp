#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include "stackMachine.hpp"

enum Instruction{
    ADD, SUB, MUL, DIV, MOD,    //Arithmetic 
    NOT, OR, AND, MIR,          //Logic
    PUSH, POP,                  //Control
    OUT,                        //IO
    Error
};

enum ParserError{
    SyntaxError = 000,
    InvalidInstruction = 001,
    InvalidArgument = 002,
    CouldNotReadFile = 003,
    NoError = 255
};

typedef std::pair<Instruction, std::bitset<16>> instAndArg;

class Parser
{
private:
    //vars
    std::vector<instAndArg> program;
    std::vector<std::string> programLine;
    //
    instAndArg convertLineToInst(std::string line, ParserError &status);
    std::vector<std::string> splitLine(std::string line);
public:
    // read
    ParserError readProgram(std::string inputFile);
    // 
    std::vector<instAndArg> getProgram();
    //
    Parser(/* args */);
    ~Parser();
};


#endif
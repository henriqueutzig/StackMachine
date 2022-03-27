#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;
#define INT_SIZE 16

enum Flags
{
    Verbose=0,
    Debug=1
};

enum ErrorCode
{
    SyntaxError,
    InvalidInstruction,
    InvalidArgument,
    EmptyStack,
    FullStack,
    CouldNotReadFile,
    GenericRunTimeError,
    DivisionByZero,
    PowOfNegativenumber,
    SqrtOfNegativeNumber,
    Comment = 255,
};

struct MachineStatus
{
    uint32_t line;
    ErrorCode errorCode;
};

enum Instruction
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD, // Arithmetic
    POW,
    SQRT,
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

struct Operation
{
    uint32_t lineInFile;
    Instruction instruction;
    bitset<INT_SIZE> argument;
};

static const char *instructioString[] =
    {
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "MOD",
        "POW",
        "SQRT",
        "NOT",
        "OR",
        "AND",
        "MIR",
        "PUSH",
        "POP",
        "OUT",
        "CLEAR",
        "PUSH"};

static const char *errorString[] =
    {
        "Syntax error",
        "Invalid instruction",
        "Invalid argument",
        "Stack already empty",
        "Stack overflow",
        "Could not read file",
        "Unexpected runtime error",
        "Division by zero not allowed",
        "Number raised to negative number not allowed",
        "Square root of negative numbers not allowed"};

#endif
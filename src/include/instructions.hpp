#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>

using namespace std;
#define INT_SIZE 16

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
    SqrtOfNegativeNumber,
    Comment = 255,
};

struct MachineStatus
{
    uint32_t line;
    ErrorCode error;
};

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
        "NOT",
        "OR",
        "AND",
        "MIR",
        "PUSH",
        "POP",
        "OUT",
        "CLEAR"};

#endif
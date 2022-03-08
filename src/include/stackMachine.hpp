#ifndef STACKMACHINE_HPP
#define STACKMACHINE_HPP

#include <iostream>
#include <stdint.h>

#define STACK_SIZE 128

enum Instruction{
    ADD, SUB, MUL, DIV, MOD,    //Arithmetic 
    NOT, OR, AND, MIR,          //Logic
    PUSH, POP,                  //Control
    OUT                         //IO
};

enum OpStatus{
    SyntaxError = 000,
    InvalidInstruction = 001,
    InvalidArgument = 002,
    EmptyStack = 003,
    FullStack = 004,
    Normal = 255
};

class StackMachine
{
private:
    uint32_t PC;
    uint8_t stackPointer;
    uint16_t R;
    uint16_t stack[STACK_SIZE];
    OpStatus push(uint16_t val);   // Stack full, returns value 1
    OpStatus pop();                // Empty stack, returns 2
public:
    StackMachine(/* args */);
    ~StackMachine();
};



#endif
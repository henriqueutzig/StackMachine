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

class StackMachine
{
private:
    uint16_t R;
    uint16_t stack[STACK_SIZE];
public:
    StackMachine(/* args */);
    ~StackMachine();
};



#endif
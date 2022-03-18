#ifndef STACKMACHINE_HPP
#define STACKMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <bitset>
#include "parser.hpp"

#define STACK_SIZE 128

enum OpStatus{
    // SyntaxError = 000,
    // InvalidInstruction = 001,
    // InvalidArgument = 002,
    EmptyStack = 000,
    FullStack = 001,
    Normal = 255
};

class StackMachine
{
private:
    // Vars
    uint32_t PC = 0;
    uint16_t stackPointer = 0;
    bitset<16> R = 0;
    bitset<16> stack[STACK_SIZE] = {0};
    // Controll
    OpStatus push(bitset<16> val);   // Stack full, returns value 1
    OpStatus pop();                       // Empty stack, returns 2
    // IO
    void out();
    // Logic
    void opNot();
    void opOr();
    void opAnd();
    void opMir();
    // Arithmetic 
    void add();
    void sub();
    void mul();
    void div();
    void mod();

public:
    StackMachine(/* args */);
    ~StackMachine();
};



#endif
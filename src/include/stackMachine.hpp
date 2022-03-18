#ifndef STACKMACHINE_HPP
#define STACKMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <bitset>
#include "instructions.hpp"

#define STACK_SIZE 128


enum OpStatus
{
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
    bitset<INT_SIZE> R = 0;
    bitset<INT_SIZE> stack[STACK_SIZE] = {0};
    // Controll
    OpStatus push(bitset<INT_SIZE> val); // Stack full, returns value 1
    OpStatus pop();                      // Empty stack, returns 2
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
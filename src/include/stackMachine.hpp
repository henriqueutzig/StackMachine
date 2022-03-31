#ifndef STACKMACHINE_HPP
#define STACKMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <bitset>
#include <bits/stdc++.h>
#include "instructions.hpp"
#include "bitArithmetic.hpp"

#define STACK_SIZE 128

class StackMachine
{
private:
    uint8_t SP = 0;
    uint16_t PC = 0;
    uint32_t lineInFile = 0;
    bitset<INT_SIZE> R = 0;
    bitset<INT_SIZE> M = 0;

    bool ZF = 0;
    bool NF = 0;
    bitset<INT_SIZE> stack[STACK_SIZE] = {0};

    // Flags
    bool flags[2];
    // Controll
    void clear();
    void push(bitset<INT_SIZE> val); // Stack full, returns value 1
    void push();                     // Stack full, returns value 1
    void pop();                      // Empty stack, returns 2
    // IO
    void out();
    void printStack();
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
    void pow();
    void sqrt();

    // branches
    void jmp(bitset<INT_SIZE> val);
    void jz(bitset<INT_SIZE> val);
    void jn(bitset<INT_SIZE> val);

    // register
    void store();
    void load();

    // misc
    void callOperation(Operation op);

public:
    StackMachine(/* args */);
    void run(vector<Operation> program);
    // set flags
    void setVerbose();
    void setDebug();
    ~StackMachine();
};

#endif
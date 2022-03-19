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
    // Vars
    uint8_t PC = 0; // PC é o stackPointer
    uint32_t lineInFile = 0;
    bitset<INT_SIZE> R = 0;
    bitset<INT_SIZE> stack[STACK_SIZE] = {0};
    // Controll
    void clear();
    void push(bitset<INT_SIZE> val); // Stack full, returns value 1
    void push();                     // Stack full, returns value 1
    void pop();                      // Empty stack, returns 2
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

    // misc
    void callOperation(Operation op);

public:
    StackMachine(/* args */);
    void run(vector<Operation> program);
    ~StackMachine();
};

#endif
#ifndef STACKMACHINE_HPP
#define STACKMACHINE_HPP

#include <iostream>
#include <stdint.h>
#include <bitset>

#define STACK_SIZE 128

enum Instruction{
    ADD, SUB, MUL, DIV, MOD,    //Arithmetic 
    NOT, OR, AND, MIR,          //Logic
    PUSH, POP,                  //Control
    OUT                         //IO
};

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
    std::bitset<16> R = 0;
    std::bitset<16> stack[STACK_SIZE] = {0};
    // Controll
    OpStatus push(std::bitset<16> val);   // Stack full, returns value 1
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
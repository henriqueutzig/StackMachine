#include "include/stackMachine.hpp"

StackMachine::StackMachine(/* args */)
{
    this->PC = 0;
    this->R = 0;
    this->stackPointer = 0;
    for (uint8_t i = 0; i < STACK_SIZE; i++)
        this->stack[i] = 0;
}

StackMachine::~StackMachine()
{
    // cout << "end" << endl;
    // for (uint8_t i = 0; i < STACK_SIZE; i++)
    //     cout << this->stack[i] << endl;

    // cout << "R: " << this->R << endl;
    // cout << "StackPointer: " << this->stackPointer << endl;
}

// =============== CONTROL INSTRUCTIONS ===============
OpStatus StackMachine::pop()
{
    if (this->stackPointer == 0)
        return EmptyStack;

    this->stack[this->stackPointer] = 0;
    this->stackPointer--;

    return Normal;
}

OpStatus StackMachine::push(bitset<16> val)
{
    if (this->stackPointer >= STACK_SIZE - 1)
        return FullStack;

    this->stackPointer++;
    this->stack[this->stackPointer] = val;

    return Normal;
}

// =============== IO INSTRUCTIONS ===============
void StackMachine::out()
{
    cout << this->stack[this->stackPointer] << endl;
}

// =============== LOGIC INSTRUCTIONS ===============

// =============== ARITHMETIC INSTRUCTIONS ===============
void StackMachine::add()
{
    uint8_t c = 0;
    uint16_t stckP = this->stackPointer;
    for (uint8_t i = 0; i < 16; i++)
    {
        this->R[i] = ((this->stack[stckP][i] ^ this->stack[stckP - 1][i]) ^ c); // c is carry
        c = ((this->stack[stckP][i] & this->stack[stckP - 1][i]) | (this->stack[stckP][i] & c)) | (this->stack[stckP - 1][i] & c);
    }
}
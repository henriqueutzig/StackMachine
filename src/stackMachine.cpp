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
    // std::cout << "end" << std::endl;
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

OpStatus StackMachine::push(uint16_t val)
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
    std::cout << this->stack[this->stackPointer] << std::endl;
}
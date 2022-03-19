#include "include/stackMachine.hpp"

StackMachine::StackMachine(/* args */)
{
    PC = 0;
    R = 0;
    for (uint8_t i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

StackMachine::~StackMachine()
{
    // cout << "end" << endl;
    // for (uint8_t i = 0; i < STACK_SIZE; i++)
    //     cout << stack[i] << endl;

    // cout << "R: " << R << endl;
    // cout << "StackPointer: " << stackPointer << endl;
}

// =============== CONTROL INSTRUCTIONS ===============
void StackMachine::clear()
{
    PC = 0;
    for (uint8_t i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

OpStatus StackMachine::pop()
{
    if (PC == 0)
        return EmptyStack;

    stack[PC] = 0;
    PC--;

    return Normal;
}

OpStatus StackMachine::push(bitset<INT_SIZE> val)
{
    if (PC >= STACK_SIZE - 1)
        return FullStack;

    PC++;
    stack[PC] = val;

    return Normal;
}

// =============== IO INSTRUCTIONS ===============
void StackMachine::out()
{
    cout << stack[PC] << endl;
}

// =============== LOGIC INSTRUCTIONS ===============

void StackMachine::opNot()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = ~stack[PC][i];
}

void StackMachine::opOr()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = stack[PC][i] | stack[PC - 1][i];
}

void StackMachine::opAnd()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = stack[PC][i] & stack[PC - 1][i];
}

void StackMachine::opMir()
{
    for (uint8_t i = INT_SIZE - 1; i >= 0; i--)
        R[INT_SIZE - i - 1] = stack[PC][i];
}

// =============== ARITHMETIC INSTRUCTIONS ===============
void StackMachine::add()
{
    bool c = 0;
    // R = op1 + op2
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = bitArithmetic::Adder(stack[PC][i], stack[PC - 1][i], c);
}

void StackMachine::sub()
{
    bool b = 0;
    // R = op1 - op2
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = bitArithmetic::Subtractor(stack[PC][i], stack[PC - 1][i], b);
}

// void StackMachine::sub()
// {
//     // R = op1 - op2
//     bitset<INT_SIZE> op1 = stack[PC];
//     bitset<INT_SIZE> op2 = stack[PC - 1];
//     bitset<INT_SIZE> temp;
//     const bitset<INT_SIZE> ONE = 1;
//     uint8_t c = 0;

//     // complemento de 2 do op2
//     for (uint8_t i = 0; i < INT_SIZE; i++)
//     {
//         temp[i] = ~op2[i];
//         op2[i] = ((temp[i] ^ ONE[i]) ^ c); // c is carry
//         c = ((temp[i] & ONE[i]) | (temp[i] & c)) | (ONE[i] & c);
//     }

//     c = 0;

//     for (uint8_t i = 0; i < INT_SIZE; i++)
//     {
//         R[i] = ((op1[i] ^ op2[i]) ^ c); // c is carry
//         c = ((op1[i] & op2[i]) | (op1[i] & c)) | (op2[i] & c);
//     }
// }

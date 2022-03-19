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

void StackMachine::run(vector<Operation> program)
{
    cout << "PROGRAM STARTED" << endl;

    for (auto &&op : program)
    {
        try
        {
            callOperation(op);
        }
        catch (const ErrorCode &err)
        {
            throw(MachineStatus){op.lineInFile, err};
        }
    }

    cout << "PROGRAM ENDED" << endl;
}

// =============== CONTROL INSTRUCTIONS ===============
void StackMachine::clear()
{
    PC = 0;
    for (uint8_t i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

void StackMachine::pop()
{
    if (PC == 0)
        throw EmptyStack;

    stack[PC] = 0;
    PC--;
}

void StackMachine::push(bitset<INT_SIZE> val)
{
    if (PC >= STACK_SIZE - 1)
        throw FullStack;

    PC++;
    stack[PC] = val;
}

void StackMachine::push()
{
    if (PC >= STACK_SIZE - 1)
        throw FullStack;

    PC++;
    stack[PC] = R;
}

// =============== IO INSTRUCTIONS ===============
void StackMachine::out()
{
    int16_t outInt = (int)(stack[PC].to_ulong());
    cout << "INT: " << outInt << " BINARY: " << stack[PC] << endl;
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

    for (int8_t i = INT_SIZE - 1; i >= 0; i--)
        R[INT_SIZE - i - 1] = stack[PC][i];
}

// =============== ARITHMETIC INSTRUCTIONS ===============
void StackMachine::add()
{
    R = bitArithmetic::adder16Bits(stack[PC], stack[PC - 1]);
}

void StackMachine::sub()
{
    R = bitArithmetic::subtractor16Bits(stack[PC], stack[PC - 1]);
}

void StackMachine::mul()
{
    bitset<INT_SIZE> op1 = stack[PC];
    bitset<INT_SIZE> op2 = stack[PC - 1];

    R = 0;

    for (int i = 0; i < INT_SIZE; i++)
        if (op1[i])
            R = bitArithmetic::adder16Bits(R, op2 << i);
}

void StackMachine::div() {}
void StackMachine::mod() {}

// =============== MISC ===============
void StackMachine::callOperation(Operation op)
{
    switch (op.instruction)
    {
    case ADD:
        add();
        break;
    case SUB:
        sub();
        break;
    case MUL:
        mul();
        break;
    case DIV:
        div();
        break;
    case MOD:
        mod();
        break;
    case NOT:
        opNot();
        break;
    case OR:
        opOr();
        break;
    case AND:
        opAnd();
        break;
    case MIR:
        opMir();
        break;
    case PUSH:
        push(op.argument);
        break;
    case POP:
        pop();
        break;
    case OUT:
        out();
        break;
    case CLEAR:
        clear();
        break;
    case PUSHR:
        push();
        break;

    default:
        throw GenericRunTimeError;
    }
}

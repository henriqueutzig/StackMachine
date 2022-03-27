#include "include/stackMachine.hpp"

StackMachine::StackMachine(/* args */)
{
    PC = 0;
    R = 0;
    for (uint8_t i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

StackMachine::~StackMachine() {}

void StackMachine::run(vector<Operation> program)
{
    int order = 0;
    cout << "PROGRAM STARTED" << endl;

    for (auto &&op : program)
    {
        if (this->flags[Verbose] || this->flags[Debug])
            cout << order+1 << ". " << instructioString[op.instruction];
        try
        {
            callOperation(op);
            if (this->flags[Verbose] || this->flags[Debug])
                printStack();
            order++;
            if (this->flags[Debug])
            {
                cout << "Press 'ENTER' to continue.. \n";
                cin.get();
            }
        }
        catch (const ErrorCode &err)
        {
            throw(MachineStatus){op.lineInFile, err};
        }
    }

    cout << "\nPROGRAM ENDED" << endl;
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
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " " << (int16_t)(val.to_ulong());

    if (PC >= STACK_SIZE - 1)
        throw FullStack;

    PC++;
    stack[PC] = val;
}

void StackMachine::push()
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " $R" ;//<< (int16_t)(R.to_ulong());

    if (PC >= STACK_SIZE - 1)
        throw FullStack;

    PC++;
    stack[PC] = R;
}

// =============== IO INSTRUCTIONS ===============
void StackMachine::out()
{
    int16_t outInt = (int)(stack[PC].to_ulong());

    if (PC == 0)
        cout << "\nEMPTY STACK" << endl;
    else
        cout << "\t\nOUTPUT:\tINT: " << outInt << " || BINARY: " << stack[PC];
}

void StackMachine::printStack()
{
    cout << "\n\tSTACK:\tR: " << (int16_t)(this->R.to_ulong()) << endl;
    for (uint16_t i = PC; i > 0; i--)
    {
        cout << "\t"
             << "[ " << (int16_t)(stack[i].to_ulong()) << " ]" << endl;
    }
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
    R = bitArithmetic::adderNBits(stack[PC], stack[PC - 1]);
}

void StackMachine::sub()
{
    R = bitArithmetic::subtractorNBits(stack[PC], stack[PC - 1]);
}

void StackMachine::mul()
{
    R = bitArithmetic::multiplicationNbits(stack[PC], stack[PC - 1]);
}

// R = op1 / op2
void StackMachine::div()
{
    bitset<INT_SIZE> r = 0;
    try
    {
        R = bitArithmetic::divisionNbits(stack[PC], stack[PC - 1], r);
    }
    catch (const int err)
    {
        throw DivisionByZero;
    }
}

// R = op1 mod 2
void StackMachine::mod()
{
    try
    {
        bitArithmetic::divisionNbits(stack[PC], stack[PC - 1], R);
    }
    catch (const int err)
    {
        throw DivisionByZero;
    }
}

// R = op1^op2
void StackMachine::pow()
{
    bitset<INT_SIZE> op1 = stack[PC];
    bitset<INT_SIZE> op2 = stack[PC - 1];

    if (op2[INT_SIZE - 1])
        throw PowOfNegativenumber;

    R = 1;

    for (size_t i = 0; bitArithmetic::lessThen(i, op2); i++)
        R = bitArithmetic::multiplicationNbits(op1, R);
}

// R = (int)op1^(-2)
// TODO: extremely rudimentary algorithm, please improve
void StackMachine::sqrt()
{
    bitset<INT_SIZE> op = stack[PC];

    if (op[INT_SIZE - 1])
        throw SqrtOfNegativeNumber;

    if (op == 0 || op == 1)
    {
        R = op;
        return;
    }

    bitset<INT_SIZE> i = 1;
    bitset<INT_SIZE> res = 1;

    while (bitArithmetic::lessOrEqThen(res, op))
    {
        i = bitArithmetic::adderNBits(i, 1);
        res = bitArithmetic::multiplicationNbits(i, i);
    }

    R = bitArithmetic::subtractorNBits(i, 1);
}

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
    case POW:
        pow();
        break;
    case SQRT:
        sqrt();
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

void StackMachine::setVerbose()
{
    this->flags[Verbose] = true;
}

void StackMachine::setDebug()
{
    this->flags[Debug] = true;
}
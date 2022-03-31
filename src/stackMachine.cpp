#include "include/stackMachine.hpp"

StackMachine::StackMachine()
{
    SP = 0;
    PC = 0;
    R = 0;
    M = 0;
    NF = 0;
    ZF = 0;

    for (uint8_t i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;
}

StackMachine::~StackMachine() {}

void StackMachine::run(vector<Operation> program)
{
    int order = 1;
    cout << "PROGRAM STARTED" << endl;

    for (PC = 0; PC < program.size(); PC++)
    {
        if (this->flags[Verbose] || this->flags[Debug])
            cout << order << ". " << instructioString[program[PC].instruction];

        uint16_t oldPC = PC;
        try
        {
            callOperation(program[PC]);
        }
        catch (const ErrorCode &err)
        {
            throw(MachineStatus){program[PC].lineInFile, err};
        }

        if (PC >= program.size())
            break;

        NF = bitArithmetic::lessThen(R, 0) ? true : false;
        ZF = bitArithmetic::isZero(R) ? true : false;

        if (this->flags[Verbose] || this->flags[Debug])
            printStack();
        order++;
        if (this->flags[Debug])
        {
            cout << "Press 'ENTER' to continue.. \n";
            cin.get();
        }
    }
    cout << "\nPROGRAM ENDED" << endl;
}

// =============== CONTROL INSTRUCTIONS ===============
void StackMachine::clear()
{
    StackMachine();
}

void StackMachine::pop()
{
    if (SP == 0)
        throw EmptyStack;

    stack[SP] = 0;
    SP--;
}

void StackMachine::push(bitset<INT_SIZE> val)
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " " << (int16_t)(val.to_ulong());

    if (SP >= STACK_SIZE - 1)
        throw FullStack;

    SP++;
    stack[SP] = val;
}

void StackMachine::push()
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " $R"; //<< (int16_t)(R.to_ulong());

    if (SP >= STACK_SIZE - 1)
        throw FullStack;

    SP++;
    stack[SP] = R;
}

// =============== IO INSTRUCTIONS ===============
void StackMachine::out()
{
    int16_t outInt = (int)(stack[SP].to_ulong());

    if (SP == 0)
        cout << "\nEMPTY STACK" << endl;
    else
        cout << "\t\nOUTPUT:\tINT: " << outInt << " || BINARY: " << stack[SP];
}

void StackMachine::printStack()
{
    cout << "\n\tSTACK:\tR: " << (int16_t)(this->R.to_ulong()) << "\tM: " << (int16_t)(this->M.to_ulong()) << "\tZF: " << ZF << "\tNF: " << NF << endl;
    for (uint16_t i = SP; i > 0; i--)
    {
        cout << "\t"
             << "[ " << (int16_t)(stack[i].to_ulong()) << " ]" << endl;
    }
}

// =============== LOGIC INSTRUCTIONS ===============

void StackMachine::opNot()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = ~stack[SP][i];
}

void StackMachine::opOr()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = stack[SP][i] | stack[SP - 1][i];
}

void StackMachine::opAnd()
{
    for (uint8_t i = 0; i < INT_SIZE; i++)
        R[i] = stack[SP][i] & stack[SP - 1][i];
}

void StackMachine::opMir()
{

    for (int8_t i = INT_SIZE - 1; i >= 0; i--)
        R[INT_SIZE - i - 1] = stack[SP][i];
}

// =============== ARITHMETIC INSTRUCTIONS ===============
void StackMachine::add()
{
    R = bitArithmetic::adderNBits(stack[SP], stack[SP - 1]);
}

void StackMachine::sub()
{
    R = bitArithmetic::subtractorNBits(stack[SP], stack[SP - 1]);
}

void StackMachine::mul()
{
    R = bitArithmetic::multiplicationNbits(stack[SP], stack[SP - 1]);
}

// R = op1 / op2
void StackMachine::div()
{
    bitset<INT_SIZE> r = 0;
    try
    {
        R = bitArithmetic::divisionNbits(stack[SP], stack[SP - 1], r);
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
        bitArithmetic::divisionNbits(stack[SP], stack[SP - 1], R);
    }
    catch (const int err)
    {
        throw DivisionByZero;
    }
}

// R = op1^op2
void StackMachine::pow()
{
    bitset<INT_SIZE> op1 = stack[SP];
    bitset<INT_SIZE> op2 = stack[SP - 1];

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
    bitset<INT_SIZE> op = stack[SP];

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

// =============== JUMPS ===============

void StackMachine::jmp(bitset<INT_SIZE> val)
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " " << (int16_t)(val.to_ulong());

    PC = val.to_ulong() - 1;
}

void StackMachine::jz(bitset<INT_SIZE> val)
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " " << (int16_t)(val.to_ulong());

    if (ZF)
        PC = val.to_ulong() - 1;
}

void StackMachine::jn(bitset<INT_SIZE> val)
{
    if (this->flags[Verbose] || this->flags[Debug])
        cout << " " << (int16_t)(val.to_ulong());

    if (NF)
        PC = val.to_ulong() - 1;
}

// =============== REGISTER ===============

void StackMachine::store()
{
    M = stack[SP];
}

void StackMachine::load()
{
    push(M);
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
    case JMP:
        jmp(op.argument);
        break;
    case JZ:
        jz(op.argument);
        break;
    case JN:
        jn(op.argument);
        break;
    case LOAD:
        load();
        break;
    case STORE:
        store();
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
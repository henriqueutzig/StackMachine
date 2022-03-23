#include "include/bitArithmetic.hpp"

bool bitArithmetic::adder(bool b1, bool b2, bool &carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

bool bitArithmetic::subtractor(bool b1, bool b2, bool &borrow)
{
    bool diff;
    if (borrow)
    {
        diff = !(b1 ^ b2);
        borrow = !b1 || (b1 && b2);
    }
    else
    {
        diff = b1 ^ b2;
        borrow = !b1 && b2;
    }
    return diff;
}

bitset<N> bitArithmetic::adderNBits(const bitset<N> &op1, const bitset<N> &op2)
{
    bitset<N> res;
    bool c = 0;

    for (uint8_t i = 0; i < N; i++)
        res[i] = adder(op1[i], op2[i], c);

    return res;
}

bitset<N> bitArithmetic::subtractorNBits(const bitset<N> &op1, const bitset<N> &op2)
{
    bitset<N> res;
    bool b = 0;

    for (uint8_t i = 0; i < N; i++)
        res[i] = subtractor(op1[i], op2[i], b);

    return res;
}

bool bitArithmetic::lessOrEqThen(const bitset<N> &op1, const bitset<N> &op2)
{
    bitset<N> res = subtractorNBits(op1, op2);

    if (res == 0)
        return true;
    return subtractorNBits(op1, op2)[N - 1];
}

bool bitArithmetic::lessThen(const bitset<N> &op1, const bitset<N> &op2)
{
    return subtractorNBits(op1, op2)[N - 1];
}

bool bitArithmetic::greaterOrEqThen(const bitset<N> &op1, const bitset<N> &op2)
{
    bitset<N> res = subtractorNBits(op2, op1);

    if (res == 0)
        return true;

    return subtractorNBits(op2, op1)[N - 1];
}

bool bitArithmetic::greaterThen(const bitset<N> &op1, const bitset<N> &op2)
{
    return subtractorNBits(op2, op1)[N - 1];
}

bitset<N> bitArithmetic::abs(const bitset<N> &op)
{
    return lessThen(op, 0) ? subtractorNBits(0, op) : op;
}

bitset<N> bitArithmetic::multiplicationNbits(bitset<N> op1, bitset<N> op2)
{
    bitset<N> res = 0;
    for (int i = 0; i < N; i++)
        if (op1[i])
            res = bitArithmetic::adderNBits(res, op2 << i);
    return res;
}

int topBitSet(const bitset<N> &op)
{
    int i;
    for (i = N - 1; i >= 0; i--)
        if (op[i])
            break;
    return i;
}

bitset<N> bitArithmetic::divisionNbits(bitset<N> op1, bitset<N> op2, bitset<N> &r)
{
    bitset<N> q = 0;

    bitset<N> absOp1 = abs(op1);
    bitset<N> absOp2 = abs(op2);

    int divisor_size = topBitSet(absOp2);

    if (divisor_size < 0)
        throw 0;

    int bit;

    while ((bit = topBitSet(absOp1)) >= divisor_size)
    {
        q.set(bit - divisor_size);
        absOp1 ^= absOp2 << (bit - divisor_size);
    }

    r = absOp1;

    if (lessThen(op1, 0))
    {
        r = subtractorNBits(0, r);
        if (greaterThen(op2, 0))
            q = subtractorNBits(0, q);
    }
    else
    {
        if (lessThen(op2, 0))
            q = subtractorNBits(0, q);
    }

    return q;
}
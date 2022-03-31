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

bool bitArithmetic::isZero(const bitset<N> &op)
{
    for (uint8_t i = 0; i < N; i++)
        if (op[i] & op[i])
            return false;

    return true;
}

bool bitArithmetic::lessOrEqThen(const bitset<N> &op1, const bitset<N> &op2)
{
    bitset<N> res = subtractorNBits(op1, op2);

    if (res == 0)
        return true;

    return res[N - 1];
}

bool bitArithmetic::lessOrEqThenABS(const bitset<N> &op1, const bitset<N> &op2)
{
    for (int i = N - 1; i >= 0; i--)
    {
        if (op1[i] ^ op2[i])
            return op2[i];
    }
    return true;
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

    return res[N - 1];
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

bitset<N> bitArithmetic::divisionNbits(bitset<N> op1, bitset<N> op2, bitset<N> &r)
{
    bitset<N> q = 0;

    bitset<N> absOp1 = abs(op1);
    bitset<N> absOp2 = abs(op2);

    if (isZero(absOp2))
        throw 0;

    for (int16_t i = N - 1; i >= 0; i--)
    {
        if (lessOrEqThenABS(absOp2 << i, absOp1))
        {
            absOp1 = subtractorNBits(absOp1, absOp2 << i);
            q = adderNBits(q, 1 << i);
        }
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
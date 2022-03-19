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

bitset<16> bitArithmetic::adder16Bits(bitset<16> op1, bitset<16> op2)
{
    bitset<16> res;
    bool c = 0;

    for (uint8_t i = 0; i < 16; i++)
        res[i] = adder(op1[i], op2[i], c);

    return res;
}

bitset<16> bitArithmetic::subtractor16Bits(bitset<16> op1, bitset<16> op2)
{
    bitset<16> res;
    bool b = 0;

    for (uint8_t i = 0; i < 16; i++)
        res[i] = subtractor(op1[i], op2[i], b);

    return res;
}
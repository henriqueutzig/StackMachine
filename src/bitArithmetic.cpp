#include "include/bitArithmetic.hpp"

bool bitArithmetic::Adder(bool b1, bool b2, bool &carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

bool bitArithmetic::Subtractor(bool b1, bool b2, bool &borrow)
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
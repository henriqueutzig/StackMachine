#ifndef BITARITHMETIC_HPP
#define BITARITHMETIC_HPP

struct bitArithmetic
{
    static bool Adder(bool b1, bool b2, bool &carry);

    static bool Subtractor(bool b1, bool b2, bool &borrow);
};

#endif
#ifndef BITARITHMETIC_HPP
#define BITARITHMETIC_HPP

#include <bitset>

using namespace std;
struct bitArithmetic
{
    static bool adder(bool b1, bool b2, bool &carry);

    static bool subtractor(bool b1, bool b2, bool &borrow);

    static bitset<16> adder16Bits(bitset<16> op1, bitset<16> op2);

    static bitset<16> subtractor16Bits(bitset<16> op1, bitset<16> op2);
};

#endif
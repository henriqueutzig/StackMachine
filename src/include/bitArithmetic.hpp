#ifndef BITARITHMETIC_HPP
#define BITARITHMETIC_HPP

#include <bitset>

#define N 16

using namespace std;
struct bitArithmetic
{
    static bool adder(bool b1, bool b2, bool &carry);

    static bool subtractor(bool b1, bool b2, bool &borrow);

    static bitset<N> adderNBits(const bitset<N> &op1, const bitset<N> &op2);

    static bitset<N> subtractorNBits(const bitset<N> &op1, const bitset<N> &op2);

    static bool lessOrEqThen(const bitset<N> &op1, const bitset<N> &op2);

    static bool lessThen(const bitset<N> &op1, const bitset<N> &op2);

    static bool greaterOrEqThen(const bitset<N> &op1, const bitset<N> &op2);

    static bool greaterThen(const bitset<N> &op1, const bitset<N> &op2);

    static bitset<N> abs(const bitset<N> &op);

    static bitset<N> divisionNbits(bitset<N> op1, bitset<N> op2, bitset<N> &r);
};

#endif
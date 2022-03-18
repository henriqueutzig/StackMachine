#include <iostream>
#include "include/stackMachine.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;
    Parser parser;
    parser.readProgram("tests/test1.txt");
    // cout << "StackMachine" << endl;
    return 0;
}
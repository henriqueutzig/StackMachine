#include <iostream>
#include "include/stackMachine.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;
    Parser parser;
    std::vector<ParserStatus> status = parser.readProgram("tests/test2.txt");

    for (auto &&error : status)
    {
        cout << "ERROR: Line: " << error.line << " code: " << error.error << endl;
    }

    for (auto &&instAndArg : parser.getProgram())
    {
        cout << "instruction: " << instAndArg.first << " argument: " << instAndArg.second << endl;
    }

    // cout << "StackMachine" << endl;
    return 0;
}
#include <iostream>
#include "include/stackMachine.hpp"
#include "include/parser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;
    Parser parser;

    try
    {
        vector<Operation> program = Parser::parseFile("tests/test1.txt");
        for (auto &&op : program)
            cout << "instruction: " << op.instruction << " argument: " << op.argument << endl;
    }
    catch (const vector<ParserStatus> &status)
    {
        for (auto &&error : status)
            cout << "ERROR: Line: " << error.line << " code: " << error.error << endl;
    }

    // cout << "StackMachine" << endl;
    return 0;
}
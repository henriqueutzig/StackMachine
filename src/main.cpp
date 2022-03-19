#include <iostream>
#include "include/stackMachine.hpp"
#include "include/parser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;

    try
    {
        vector<Operation> program = Parser::parseFile("tests/arithmeticOp.txt");
        machine.run(program);
    }
    catch (const vector<MachineStatus> &parserErrors)
    {
        for (auto &&error : parserErrors)
            cout << "PARSER ERROR: Line: " << error.line << " code: " << error.error << endl;
    }
    catch (const MachineStatus &runTimeError)
    {
        cout << "RUNTIME ERROR: Line: " << runTimeError.line << " code: " << runTimeError.error << endl;
    }

    // cout << "StackMachine" << endl;
    return 0;
}
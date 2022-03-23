#include <iostream>
#include "include/stackMachine.hpp"
#include "include/parser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;

    try
    {
        vector<Operation> program = Parser::parseFile("apps/bhaskara.txt");
        machine.run(program);
    }
    catch (const vector<MachineStatus> &parserErrors)
    {
        for (auto &&error : parserErrors)
            cout << "PARSER ERROR (Line: " << error.line << ","
                 << " ErrorCode: " << error.errorCode << ","
                 << " Message: " << errorString[error.errorCode] << ")" << endl;
    }
    catch (const MachineStatus &runTimeError)
    {
        cout << "RUNTIME ERROR (Line: " << runTimeError.line << ","
             << " ErrorCode: " << runTimeError.errorCode << ","
             << " Message: " << errorString[runTimeError.errorCode] << ")" << endl;
    }

    return 0;
}
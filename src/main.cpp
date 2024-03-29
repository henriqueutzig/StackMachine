#include <iostream>
#include <string.h>
#include "include/stackMachine.hpp"
#include "include/parser.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    StackMachine machine;
    string filename;

    try
    {
        if (argc < 2)
        {
            cout << "Enter file name: ";
            cin >> filename;
        }
        else
        {
            for (int i = 1; i < argc; i++)
                if (strlen(argv[i]) > 2)
                    filename = argv[i];
                else
                {
                    if (strcmp(argv[i], "-d") == 0)
                        machine.setDebug();
                    if (strcmp(argv[i], "-v") == 0)
                        machine.setVerbose();
                }
        }
        vector<Operation> program = Parser::parseFile(filename);
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
        cout << endl
             << "RUNTIME ERROR (Line: " << runTimeError.line << ","
             << " ErrorCode: " << runTimeError.errorCode << ","
             << " Message: " << errorString[runTimeError.errorCode] << ")" << endl;
    }

    return 0;
}
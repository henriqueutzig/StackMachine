#include <iostream>
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
                    if (strcasecmp(argv[i], "-v"))
                        machine.setVerbose();
                    if (strcasecmp(argv[i], "-d"))
                        machine.setDebug();
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
        cout << "RUNTIME ERROR (Line: " << runTimeError.line << ","
             << " ErrorCode: " << runTimeError.errorCode << ","
             << " Message: " << errorString[runTimeError.errorCode] << ")" << endl;
    }

    return 0;
}
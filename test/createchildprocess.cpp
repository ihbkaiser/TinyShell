
#include "./include/createchildprocess.h"
#include "./utils/splitcommand.h"
#include <string>
#include <iostream>

using namespace std;


int _tmain( int argc, TCHAR *argv[] )
{
    while(true) {
        string input;
        cout << "\nEnter command: ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        if (input.substr(0, 4) == "fork")
        {
            vector<string> command = split(input, ' ');

            if (command.size() > 1)
            {
                TCHAR arg[50];
                _stprintf(arg, _T("%s"), command[1].c_str());
                TCHAR* new_argv[] = { NULL, arg };
                createChildProcess(2, new_argv);
            }
            else
            {
                cout << "Usage: fork <dir>" << endl;
            }
        }
        // add more commands here
    }

    return 0;
}

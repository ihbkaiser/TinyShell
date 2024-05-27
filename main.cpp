#include "./include/createchildprocess.h"
#include "./utils/splitcommand.h"
#include <string>
#include <iostream>
#include <vector>
#include <tchar.h>

std::vector<Process*> list_of_process; // vector of processes.
int _tmain(int argc, TCHAR *argv[])
{
    while (true) {
        std::string input;
        cout << "\nEnter command: ";
        // remove all Ctrl-C when call itterupt signal from the buffer
        while(true){
        	if(getline(cin, input)) break;
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
 		}
        if (input == "exit") {
            break;
        }

        if (input.substr(0, 4) == "fork")
        {
            vector<string> command = split(input, ' ');

            if (command.size() == 2)
            {
                TCHAR arg[50];
                _stprintf(arg, _T("%s"), command[1].c_str());
                TCHAR* new_argv[] = { NULL, arg };
                createChildProcess(2, new_argv);
            }
            else if (command.size() == 3)
            {
                TCHAR arg1[50];
                TCHAR arg2[50];
                _stprintf(arg1, _T("%s"), command[1].c_str());
                _stprintf(arg2, _T("%s"), command[2].c_str());
                TCHAR* new_argv[] = { NULL, arg1, arg2 };
                createChildProcess(3, new_argv);
            }
            else
            {
                cout << "Usage: fork <dir> [foreground/background]" << endl;
            }
        }
        // add more commands here
    }

    return 0;
}


#include "../include/createchildprocess.h"
#include "../include/executebatchfile.h"
#include "../utils/splitcommand.h"
#include "../include/path.h"
#include "../include/date.h"
#include <string>
#include <iostream>
#include <vector>
#include <tchar.h>

std::vector<Process*> list_of_process; // vector of processes.
std::vector<std::string> Path;
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
        if (input == "date"){
        	PrintDate();
		}
        if (input == "listpath"){
        	listpath();
        	continue;
		}
		if (input.substr(0,7) == "addpath"){
			vector<string> command = split(input, ' ');
			if(command.size() == 1){
				cout << "Usage: addpath <path>";
			}
			if(command.size() == 2){
				std::string new_path = command[1];
				addpath(new_path);
				continue;
			}
		}

        if (input.substr(0, 4) == "fork")
        {
            vector<string> command = split(input, ' ');
            // command = {"fork" , "test/example.exe"}
            // kill 6969 

            if (command.size() == 2)
            {
                TCHAR arg[50];
                _stprintf(arg, _T("%s"), command[1].c_str());
                TCHAR* new_argv[] = { NULL, arg };
                createChildProcess(2, new_argv);
                // int argc, char ** argv
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
        if (input.substr(0, 6) == "exebat") {
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                executeBatchFile(command[1]);
            } else {
                std::cout << "Usage: exebat <filepath>\n";
            }
        }
        // add more commands here
    }

    return 0;
}


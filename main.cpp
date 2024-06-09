#include "./include/createchildprocess.h"
#include "./include/executebatchfile.h"
#include "./include/listprocess.h"
#include "./utils/splitcommand.h"
#include "./utils/cursor.h"
#include "./include/path.h"
#include "./include/date.h"
#include "./include/clock.h"
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
        if (input.substr(0,4) == "exit") {
        	vector<string> command = split(input, ' ');
        	if(command.size() == 1){
        		//todo: fix exits, exitss, exitsss
        		killbg();
        		break;
			}
            else if(command.size() == 2){
            	if(command[1] == "sf") break;
            	else std::cout<<"Usage: exit [sf]";
            	
			}
			else std::cout<<"Usage: exit [sf]";
        }
        if (input == "clear") system("cls");
        if (input == "time"){
        	COORD here = cursor();
        	printClock(here);
		}
        if (input == "listpath"){
        	listpath();
        	continue;
		}
		if (input == "date"){
			PrintDate();
			continue;
		}
		if (input == "list"){
			listprocess();
		}
		if (input == "close"){
			close();
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
        if (input.substr(0,4) == "stop"){
        	vector<string> command = split(input, ' ');
        	bool found = false; //did we found a process with that pid ?
        	if(command.size() == 2){
        		DWORD pid = stoi(command[1]);
        		for(Process* process : list_of_process){
        			if(process->pi.dwProcessId == pid){
        				process->stop();
        				found = true;
        				break;
					}
				}
				if(!found){
					std::cout << "Cannot find process with PID " << pid << endl;
				}
			}
			else{
				std::cout << "Usage: stop <pid>" << endl;
			}
		}

         if (input.substr(0,6) == "resume"){
        	vector<string> command = split(input, ' ');
        	bool found = false; //did we found a process with that pid ?
        	bool findStop = false;
        	if(command.size() == 2){
        		DWORD pid = stoi(command[1]);
        		for(Process* process : list_of_process){
        			if(process->pi.dwProcessId == pid) found = true;
        			if(process->pi.dwProcessId == pid && process->isStop){
        				process->resume();
        				findStop = true;
        				break;
					}
				}
				if(!found){
					std::cout << "Cannot find process with PID " << pid << endl;
				}
				if(found && !findStop){
					std::cout << "Process with PID " << pid << " not stopped";
				}
			}
			else{
				std::cout << "Usage: resume <pid>" << endl;
			}
		}
        if (input.substr(0,4) == "kill"){
        	vector<string> command = split(input, ' ');
        	bool found = false; //did we found a process with that pid ?
        	if(command.size() == 2){
        		DWORD pid = stoi(command[1]);
        		for(Process* process : list_of_process){
        			if(process->pi.dwProcessId == pid){
        				process->terminate();
        				found = true;
        				break;
					}
				}
				if(!found){
					std::cout << "Cannot find process with PID " << pid << endl;
				}
			}
			else{
				std::cout << "Usage: kill <pid>" << endl;
			}
		}
    }

    return 0;
}


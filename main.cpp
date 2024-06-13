#include "./include/createchildprocess.h"
#include "./include/executebatchfile.h"
#include "./include/openwebsite.h"
#include "./include/listprocess.h"
#include "./utils/splitcommand.h"
#include "./utils/cursor.h"
#include "./include/path.h"
#include "./include/date.h"
#include "./include/clock.h"
#include "./include/cd.h"
#include "./include/help.h"
#include <string>
#include <iostream>
#include <vector>
#include <tchar.h>

std::vector<Process*> list_of_process; // vector of processes.
std::vector<std::string> Path;
int _tmain(int argc, TCHAR *argv[])
{
	makeColor();
	help();
    while (true) {
    	
    	bool exec = false;
        std::string input;
        cout << "\nEnter command: ";
        // remove all Ctrl-C when call itterupt signal from the buffer
        while(true){
        	if(getline(cin, input)) break;
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
 		}
 		if (input == "help"){ exec = true; help();
		 }
        if (input.substr(0,4) == "exit") {
        	exec = true;
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
			continue;
        }
        if (input == "clear") {
        	exec = true;
        	system("cls"); continue;
		}
        if (input == "time"){
        	exec = true;
        	COORD here = cursor();
        	printClock(here);
        	continue;
		}
        if (input == "listpath"){
        	exec = true;
        	listpath();
        	continue;
		}
		if (input == "date"){
			exec = true;
			PrintDate();
			continue;
		}
		if (input == "list"){
			exec = true;
			listprocess();
			continue;
		}
		if (input == "close"){
			exec = true;
			close();
			continue;
		}
		if (input == "dir"){
			exec = true;
			dir();
			continue;
		}
		if (input.substr(0,7) == "addpath"){
			exec = true;
			vector<string> command = split(input, ' ');
			if(command.size() == 1){
				cout << "Usage: addpath <path>";
			}
			if(command.size() == 2){
				std::string new_path = command[1];
				addpath(new_path);
				continue;
			}
			continue;
		}

        if (input.substr(0, 4) == "fork")
        {
        	exec = true;
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
            continue;
        }
        if (input.substr(0, 6) == "exebat") {
        	exec = true;
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                executeBatchFile(command[1]);
            } else {
                std::cout << "Usage: exebat <filepath>\n";
            }
            continue;
        } 
        if (input.substr(0, 3) == "cmd") {
            if (input.size() <= 4) {
                std::cout << "Usage: cmd <cmd Command>\n";
                continue;
            }
            string command = input.substr(4);
            execute_command(command);
            continue;
        }
		if (input.substr(0, 7) == "youtube") {
            open_website("https://www.youtube.com");
            continue;
		}
        if (input.substr(0, 7) == "chatgpt") {
            open_website("https://chat.openai.com");
            continue;
        }
        if (input.substr(0, 8) == "facebook") {
            open_website("https://facebook.com");
            continue;
        }
        if (input.substr(0, 3) == "web") {
			vector<string> command = split(input, ' ');
			string url = "https://" + command[1];
            open_website(url);
            continue;
        }
        if (input.substr(0,2) == "cd"){
        	exec = true;
        	vector<string> command = split(input, ' ');
        	if(command.size()==2){
        		cd(command[1]);
			}
			else std::cout<<"Usage: cd <dir>";
			continue;
		}
        if (input.substr(0,4) == "stop"){
        	exec = true;
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
			continue;
		}

         if (input.substr(0,6) == "resume"){
         	exec = true;
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
			continue;
		}
        if (input.substr(0,4) == "kill"){
        	exec = true;
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
			continue;
		}
		if(!exec){
			std::cout << "Invalid command. Type 'help' for more details\n";
		}
    }
    

    return 0;
}


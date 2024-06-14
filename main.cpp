
#include "./include/executebatchfile.h"

#include <string>
#include <iostream>
#include <vector>
#include <tchar.h>
std::vector<std::string> History;
std::vector<Process*> list_of_process; // vector of processes.
std::vector<std::string> Path;
int _tmain(int argc, TCHAR *argv[])
{
	makeColor();
	help();

    while (true) {
    	bool exec = false;
        std::string input;
        
        std::cout << "\nEnter command: ";
        // remove all Ctrl-C when call itterupt signal from the buffer
        std::cin.clear();
        while(true){
        	if(getline(std::cin, input)) break;
        	std::cin.clear();
        	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
 		}
// skip leading strange characters
// The input string might contain strange characters after calling SearchGoogle().
// This is a temporary solution to address this issue.
 		int first_alphabet = -1;
        for(int i=0; i<input.size(); i++){
        	if(std::isalpha(input[i])){
        		first_alphabet = i;
        		break;
			}
		}
		if(first_alphabet == -1) continue;
		input = input.substr(first_alphabet);
//////
        History.push_back(input);
        if(input == "google"){
        	exec = true;
        	Search();
        	std::cin.clear();
		}
 		if (input == "help"){ exec = true; help();
		 }
		if (input == "history"){
			exec = true;
			printHistory();
		}
		if (input == "clearhistory"){
			exec = true;
			clearHistory();
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
        	exec = true;
            if (input.size() <= 4) {
                std::cout << "Usage: cmd <cmd Command>\n";
                continue;
            }
            string command = input.substr(4);
            execute_command(command);
            continue;
        }
		if (input == "youtube") {
			exec = true;
            open_website("https://www.youtube.com");
            continue;
		}
        if (input == "chatgpt") {
        	exec = true;
            open_website("https://chat.openai.com");
            continue;
        }
        if (input == "facebook") {
        	exec = true;
            open_website("https://facebook.com");
            continue;
        }
        if (input.substr(0, 3) == "web") {
        	exec = true;
        	
        	vector<string> command = split(input, ' ');
        	if(command.size() == 2){
			string url = "https://" + command[1];
            open_website(url);
        		
			}
			else std::cout << "Usage: web <url>";
			
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
		if(input.substr(0,4) == "exeb"){
			exec = true;
			vector<string> command = split(input, ' ');
			if(command.size() == 2) parse(command[1]);
			else std::cout<<"Usage: exeb <filepath>";
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
		if (!exec && std::any_of(input.begin(), input.end(), [](char c){ return std::isalpha(c); })) {
    std::cout << "Invalid command. Type 'help' for more details\n";
}
    }
    

    return 0;
}


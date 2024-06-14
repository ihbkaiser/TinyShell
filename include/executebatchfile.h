#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include "createchildprocess.h"
#include "openwebsite.h"
#include "listprocess.h"
#include "../utils/splitcommand.h"
#include "../utils/cursor.h"
#include "path.h"
#include "date.h"
#include "clock.h"
#include "cd.h"
#include "help.h"
#include "history.h"
#include "search.h"
extern std::vector<std::string> History;
extern std::vector<Process*> list_of_process;
extern std::vector<std::string> Path;
void executeBatchFile(std::string& filePath) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    
    // accept file path with '/' 
    std::replace(filePath.begin(), filePath.end(), '/', '\\');
    std::string command = "cmd /c " + filePath;

    if (CreateProcess(
        NULL,                      // No module name (use command line)
        &command[0],               // Command line
        NULL,                      // Process handle not inheritable
        NULL,                      // Thread handle not inheritable
        FALSE,                     // Set handle inheritance to FALSE
        0,                         // No creation flags
        NULL,                      // Use parent's environment block
        NULL,                      // Use parent's starting directory 
        &si,                       // Pointer to STARTUPINFO structure
        &pi)                       // Pointer to PROCESS_INFORMATION structure
    ) {
        DWORD exitCode;
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        if(exitCode == 0) std::cout << "Batch file executed successfully.\n";
        else{
        	std::cerr << "Failed to execute batch file. Error: " << exitCode << "\n";
		}
    } else {
        std::cerr << "Failed to execute batch file. Error: " << GetLastError() << "\n";
    }
}

void execute_command(const std::string &command) {
    std::string cmd_command = "cmd /c " + command;
    int result = system(cmd_command.c_str());
    if (result == -1) {
        perror("system failed");
    } 
    
}
void HandleInput(std::string input){
	bool exec = false;
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

			}
            else if(command.size() == 2){
            	if(command[1] == "sf") return;
            	else std::cout<<"Usage: exit [sf]";
            	
			}
			else std::cout<<"Usage: exit [sf]";
        }
        if (input == "clear") {
        	exec = true;
        	system("cls"); 
		}
        if (input == "time"){
        	exec = true;
        	COORD here = cursor();
        	printClock(here);
        
		}
        if (input == "listpath"){
        	exec = true;
        	listpath();
        
		}
		if (input == "date"){
			exec = true;
			PrintDate();
		
		}
		if (input == "list"){
			exec = true;
			listprocess();
		
		}
		if (input == "close"){
			exec = true;
			close();
		
		}
		if (input == "dir"){
			exec = true;
			dir();
		
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
			
			}
			
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
          
        }
        if (input.substr(0, 6) == "exebat") {
        	exec = true;
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                executeBatchFile(command[1]);
            } else {
                std::cout << "Usage: exebat <filepath>\n";
            }
            
        } 
        if (input.substr(0, 3) == "cmd") {
        	exec = true;
            if (input.size() <= 4) {
                std::cout << "Usage: cmd <cmd Command>\n";
                
            }
            string command = input.substr(4);
            execute_command(command);
            
        }
		if (input == "youtube") {
			exec = true;
            open_website("https://www.youtube.com");
           
		}
        if (input == "chatgpt") {
        	exec = true;
            open_website("https://chat.openai.com");
        
        }
        if (input == "facebook") {
        	exec = true;
            open_website("https://facebook.com");

        }
        if (input.substr(0, 3) == "web") {
        	exec = true;
        	
        	vector<string> command = split(input, ' ');
        	if(command.size() == 2){
			string url = "https://" + command[1];
            open_website(url);
        		
			}
			else std::cout << "Usage: web <url>";
			
        }
        if (input.substr(0,2) == "cd"){
        	exec = true;
        	vector<string> command = split(input, ' ');
        	if(command.size()==2){
        		cd(command[1]);
			}
			else std::cout<<"Usage: cd <dir>";
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
        				return;
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
        				return;
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
        	exec = true;
        	vector<string> command = split(input, ' ');
        	bool found = false; //did we found a process with that pid ?
        	if(command.size() == 2){
        		DWORD pid = stoi(command[1]);
        		for(Process* process : list_of_process){
        			if(process->pi.dwProcessId == pid){
        				process->terminate();
        				found = true;
        				return;
					}
				}
				if(!found){
					std::cout << "Cannot find process with PID " << pid << endl;
				}
			}
			else{
				std::cout << "Usage: kill <pid>" << endl;
			}
			return;
		}
		if (!exec && std::any_of(input.begin(), input.end(), [](char c){ return std::isalpha(c); })) {
    std::cout << "Invalid command. Type 'help' for more details\n";
}
    }
void parse(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    while (getline(file, line)) {
        // Trim leading and trailing whitespace from the line
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v")); // Leading
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); // Trailing

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#' || line[0] == ';') continue;

        // Handle the command
        HandleInput(line);
    }

    file.close();
}

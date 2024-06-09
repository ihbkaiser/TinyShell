#include "./include/createchildprocess.h"
#include "./include/executebatchfile.h"
#include "./utils/splitcommand.h"
#include "./utils/cursor.h"
#include "./include/path.h"
#include "./include/date.h"
#include "./include/clock.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <tchar.h>
#include <sys/types.h>
#include <signal.h>
#include <limits>

using namespace std;

std::vector<Process*> list_of_process; // vector of processes.
std::vector<std::string> Path;
std::map<pid_t, string> processes;  // Map to keep track of child processes

int _tmain(int argc, TCHAR *argv[])
{
    while (true) {
        std::string input;
        cout << "\nEnter command: ";
        // remove all Ctrl-C when call interrupt signal from the buffer
        while(true) {
            if(getline(cin, input)) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if (input == "exit") {
            break;
        }
        
        if (input == "clear") {
            system("cls");
        }
        
        if (input == "time") {
            COORD here = cursor();
            printClock(here);
        }
        
        if (input == "listpath") {
            listpath();
            continue;
        }
        
        if (input == "date") {
            PrintDate();
            continue;
        }
        
        if (input.substr(0, 7) == "addpath") {
            vector<string> command = split(input, ' ');
            if(command.size() == 1) {
                cout << "Usage: addpath <path>";
            }
            if(command.size() == 2) {
                std::string new_path = command[1];
                addpath(new_path);
                continue;
            }
        }

        if (input.substr(0, 4) == "fork") {
            vector<string> command = split(input, ' ');
            // command = {"fork", "test/example.exe"}

            if (command.size() == 2) {
                TCHAR arg[50];
                _stprintf(arg, _T("%s"), command[1].c_str());
                TCHAR* new_argv[] = { NULL, arg };
                pid_t pid = createChildProcess(2, new_argv);
                if (pid > 0) {
                    processes[pid] = command[1];
                }
            } else if (command.size() == 3) {
                TCHAR arg1[50];
                TCHAR arg2[50];
                _stprintf(arg1, _T("%s"), command[1].c_str());
                _stprintf(arg2, _T("%s"), command[2].c_str());
                TCHAR* new_argv[] = { NULL, arg1, arg2 };
                pid_t pid = createChildProcess(3, new_argv);
                if (pid > 0) {
                    processes[pid] = command[1];
                }
            } else {
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

        if (input == "list") {
            cout << "Running processes:" << endl;
            for (const auto &entry : processes) {
                cout << "PID: " << entry.first << ", Command: " << entry.second << endl;
            }
        }

        if (input.substr(0, 4) == "kill") {
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                pid_t pid = stoi(command[1]);
                if (processes.find(pid) != processes.end()) {
                    if (kill(pid, SIGKILL) == 0) {
                        processes.erase(pid);
                        cout << "Process " << pid << " killed." << endl;
                    } else {
                        perror("Failed to kill process");
                    }
                } else {
                    cout << "Process not found." << endl;
                }
            } else {
                cout << "Usage: kill <pid>" << endl;
            }
        }

        if (input.substr(0, 4) == "stop") {
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                pid_t pid = stoi(command[1]);
                if (processes.find(pid) != processes.end()) {
                    if (kill(pid, SIGSTOP) == 0) {
                        cout << "Process " << pid << " stopped." << endl;
                    } else {
                        perror("Failed to stop process");
                    }
                } else {
                    cout << "Process not found." << endl;
                }
            } else {
                cout << "Usage: stop <pid>" << endl;
            }
        }

        if (input.substr(0, 6) == "resume") {
            vector<string> command = split(input, ' ');
            if (command.size() == 2) {
                pid_t pid = stoi(command[1]);
                if (processes.find(pid) != processes.end()) {
                    if (kill(pid, SIGCONT) == 0) {
                        cout << "Process " << pid << " resumed." << endl;
                    } else {
                        perror("Failed to resume process");
                    }
                } else {
                    cout << "Process not found." << endl;
                }
            } else {
                cout << "Usage: resume <pid>" << endl;
            }
        }

        // add more commands here
    }

    return 0;
}
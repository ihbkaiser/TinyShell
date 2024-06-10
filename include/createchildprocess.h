#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

struct Process {
    PROCESS_INFORMATION pi;
    std::string name;
    bool foreground;
    bool isStop = false;

    Process(TCHAR* processName, bool isForeground) 
        : name(processName), foreground(isForeground) {
        ZeroMemory(&pi, sizeof(pi));
    }

    bool isForeground() {
        return foreground;
    }

    bool currentActive() {
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        return exitCode == STILL_ACTIVE;
    }

    void terminate() {
    	if(currentActive()){
    	if(!TerminateProcess(pi.hProcess, 1)) std::cerr << "Error terminating the process." << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        // after terminate process, we should delete it from the list list_of_process vector.
		}
		else std::cout<<"The process already terminated\n";
        
    }
    void stop() {
    if (currentActive()) {
        if (SuspendThread(pi.hThread) == -1) {
            // Handle error
            std::cerr << "Error stopping the process." << std::endl;
        } else {
            isStop = true;
        }
    } else {
        std::cerr << "Process is not currently running." << std::endl;
    }
}
    void resume() {
    if (isStop) {
        if (ResumeThread(pi.hThread) == -1) {
            // error occurred 
            std::cerr << "Error resuming the process." << std::endl;
        } else {
            isStop = false;
        }
    } else {
        std::cerr << "Process is not stopped." << std::endl;
    }
}
};


extern std::vector<Process*> list_of_process; // the list_of_process vector move to main() function
void killbg() {
    std::vector<Process*> toTerminate;

    // Find all background processes
    for (auto& process : list_of_process) {
        if (!process->isForeground()) {
            toTerminate.push_back(process);
        }
    }

    // Terminate all background processes and remove them from the list
    for (auto& process : toTerminate) {
        process->terminate();
        for (auto it = list_of_process.begin(); it != list_of_process.end(); ++it) {
            if ((*it)->pi.dwProcessId == process->pi.dwProcessId) {
                list_of_process.erase(it);
                break;
            }
        }
    }
}
BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
    bool hasForeground = false;
    std::vector<Process*> toTerminate;

    switch (fdwCtrlType) {
        case CTRL_C_EVENT:
        	// terminate all foreground processes
            for (auto& process : list_of_process) {
                if (process->isForeground()) {
                    toTerminate.push_back(process);
                    hasForeground = true;
                }
            }
            for (auto& process : toTerminate) {
                process->terminate();
                for (auto it = list_of_process.begin(); it != list_of_process.end(); ++it) {
                    if ((*it)->pi.dwProcessId == process->pi.dwProcessId) {
                        list_of_process.erase(it);
                        break;
                    }
                }
            }
            // if we have some foreground process, we dont terminate the shell when Ctrl-C
            if (hasForeground) {
                printf("\nCtrl-C event detected, all foreground child processes terminated\n");
                return TRUE; 
            } 
            /* if we have 0 foreground but some background list_of_process, Ctrl-C will terminate
            the shell (after waiting all background processes end)  (1) */ 
            
            /* 9-6-2024 now background process will be killed along with the shell after Ctrl-C
            if u want to use (1) , then type "exit sf" instead.*/
			else {
				killbg();
                printf("\nCtrl-C event detected, no foreground process\nThe shell will terminate after all background processes have ended.");
                return FALSE; // Allow the parent process to be terminated
            }

        default:
            return FALSE;
    }
}

void createChildProcess(int argc, TCHAR* argv[]) {
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    if (argc < 2 || argc > 3) {
        printf("Usage: %s [cmdline] [foreground/background]\n", argv[0]);
        return;
    }

    bool isForeground = true;
    if (argc == 3) {
        if (_tcscmp(argv[2], _T("foreground")) == 0) {
            isForeground = true;
        } else if (_tcscmp(argv[2], _T("background")) == 0) {
            isForeground = false;
        } else {
            printf("Invalid argument for foreground/background. Use 'foreground' or 'background'.\n");
            return;
        }
    }

    Process* process = new Process(argv[1], isForeground);
    
    // we set only one Ctrl Handler.

    static bool handlerSet = false;
    if (!handlerSet) {
        if (!SetConsoleCtrlHandler(CtrlHandler, TRUE)) {
            printf("ERROR: Could not set control handler\n"); 
            return;
        }
        handlerSet = true;
    }

    if (!CreateProcess(NULL, argv[1], NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &process->pi)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_FILE_NOT_FOUND:
                printf("Error: Executable file not found.\n");
                break;
            case ERROR_PATH_NOT_FOUND:
                printf("Error: Specified path not found.\n");
                break;
            case ERROR_ACCESS_DENIED:
                printf("Error: Access denied.\n");
                break;
            case ERROR_INVALID_HANDLE:
                printf("Error: Invalid handle.\n");
                break;
            case ERROR_NOT_ENOUGH_MEMORY:
                printf("Error: Not enough memory to execute.\n");
                break;
            default:
                printf("Create Process failed with error code %d.\n", errorCode);
        }
        return;
    }

    list_of_process.push_back(process);
    printf("Created process PID: %d\n", process->pi.dwProcessId);

    if (process->isForeground()) {
        WaitForSingleObject(process->pi.hProcess, INFINITE);
        CloseHandle(process->pi.hProcess);
        CloseHandle(process->pi.hThread);
        // after this , the foreground process ends
        // now we delete it from the processes list vector.
        for (auto it = list_of_process.begin(); it != list_of_process.end(); ++it) {
            if ((*it)->pi.dwProcessId == process->pi.dwProcessId) {
                list_of_process.erase(it);
                break;
            }
        }
    } else {
        // CloseHandle(process->pi.hProcess);
        // CloseHandle(process->pi.hThread);
        printf("Child process is running in background\n");
    }
}


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <iostream>
extern std::vector<Process*> list_of_process;
void listprocess(){
	for (const auto& process : list_of_process) {
        std::cout << "PID: " << process->pi.dwProcessId << " --> ";
        std::cout << "Name: " << process->name << " --> ";
        std::cout << "Status: ";
        if (!process->currentActive()) {
            std::cout << "Terminated";
        } else if (process->isStop) {
            std::cout << "Stopped";
        } else {
            std::cout << "Running";
        }
        std::cout << std::endl;
    }
}
void close() {
    // Close those handles
    for (auto& process : list_of_process) {
        if (!process->foreground && !process->currentActive()) {  
            CloseHandle(process->pi.hProcess);
            CloseHandle(process->pi.hThread);
        }
    }

    // Find all terminated processes
    std::vector<Process*> processes_to_remove;
    for (auto& proc : list_of_process) {
        if (!proc->currentActive()) {
            processes_to_remove.push_back(proc);
        }
    }

    // Delete all terminated processes from the vector and delete the objects
    for (auto& proc : processes_to_remove) {
        auto it = find(list_of_process.begin(), list_of_process.end(), proc);
        if (it != list_of_process.end()) {
            list_of_process.erase(it);
            delete proc;  // Delete the Process object
        }
    }
}

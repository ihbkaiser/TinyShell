#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void createChildProcess(int argc, TCHAR *argv[])
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (argc != 2)
    {
        printf("Usage: %s [cmdline]\n", argv[0]);
        return;
    }

    // Start the child process.
    if (!CreateProcess(NULL,   // No module name (use command line)
                       argv[1],        // Command line
                       NULL,           // Process handle not inheritable
                       NULL,           // Thread handle not inheritable
                       FALSE,          // Set handle inheritance to FALSE
                       0,              // No creation flags
                       NULL,           // Use parent's environment block
                       NULL,           // Use parent's starting directory 
                       &si,            // Pointer to STARTUPINFO structure
                       &pi            // Pointer to PROCESS_INFORMATION structure
    ))
    {
        // Custom error messages based on failure reasons
        DWORD errorCode = GetLastError();
        if (errorCode == ERROR_FILE_NOT_FOUND)
        {
            printf("Error: Executable file not found.\n");
        }
        else if (errorCode == ERROR_PATH_NOT_FOUND)
        {
            printf("Error: Specified path not found.\n");
        }
        else if (errorCode == ERROR_ACCESS_DENIED)
        {
            printf("Error: Access denied.\n");
        }
        else if (errorCode == ERROR_INVALID_HANDLE)
        {
            printf("Error: Invalid handle.\n");
        }
        else if (errorCode == ERROR_NOT_ENOUGH_MEMORY)
        {
            printf("Error: Not enough memory to execute.\n");
        }
        else
        {
            printf("Create Process failed with error code %d.\n", errorCode);
        }
        return;
    }

    // Print the PID of the created process
    printf("Created process PID: %d\n", pi.dwProcessId);

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    TerminateProcess(pi.hProcess, 0);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    printf("End of child process");
}


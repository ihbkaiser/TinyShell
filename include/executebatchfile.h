#include <iostream>
#include <string>
#include <windows.h>

void executeBatchFile(const std::string& filePath) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Thiết lập thuộc tính để không hiển thị cửa sổ
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // Chuỗi lệnh để chạy file batch
    std::string command = "cmd /c " + filePath;

    // Khởi tạo quá trình
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
        // Đợi quá trình hoàn thành
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        std::cout << "Batch file executed successfully.\n";
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
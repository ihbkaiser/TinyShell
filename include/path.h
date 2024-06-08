#include <vector>
#include <string>
#include <windows.h>
#include <iostream>
#define MAX_PATH_SIZE 4096
extern std::vector<std::string> Path;
void listpath() {
    for (const auto& path : Path) {
        std::cout << path << std::endl;
    }
}

void addpath(const std::string& new_path) {
    Path.push_back(new_path);
    std::string system_path;
    char path_buffer[MAX_PATH_SIZE];
    DWORD buffer_size = GetEnvironmentVariable("PATH", path_buffer, 4096);
    if (buffer_size > 0) {
        system_path = path_buffer;
    }
    system_path += ";" + new_path;
    SetEnvironmentVariable("PATH", system_path.c_str());
}

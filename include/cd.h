#include <unistd.h>
#include <iostream>

void cd(std::string path) {
    if (chdir(path.c_str()) != 0) {
        perror("cd failed");
    } else {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            std::cout << cwd << std::endl;
        } else {
            perror("getcwd() error");
        }
    }
}

void dir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        perror("getcwd() error");
    }
}

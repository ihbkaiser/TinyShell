#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
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
        
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(cwd)) != NULL) {
            std::cout << "Directory contents:" << std::endl;
            while ((ent = readdir(dir)) != NULL) {
                std::cout << ent->d_name << std::endl;
            }
            closedir(dir);
        } else {
            perror("opendir() error");
        }
    } else {
        perror("getcwd() error");
    }
}

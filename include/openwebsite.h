#include <iostream>
#include <cstring>
#include <windows.h>

void open_website(const std::string& url) {
    std::cout << "Opening " << url << " in the default web browser...\n";
        std::string command = "start " + url;
        system(command.c_str());
    
}
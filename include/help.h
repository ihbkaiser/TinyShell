#include <iostream>
#include <string>
#include <windows.h>
#include <thread>
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

void help() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(hConsole, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, consoleMode);
    std::cout << GREEN << "exit [sf]" << RESET << " - Exit the shell along with all running background processes. \nIf 'sf' is provided, the shell waits for all background processes to exit before it exits." << std::endl;
    std::cout << GREEN << "clear" << RESET << " - Clear the console." << std::endl;
    std::cout << GREEN << "time" << RESET << " - Print the current time in different time zones." << std::endl;
    std::cout << GREEN << "listpath" << RESET << " - List all paths in the PATH environment variable." << std::endl;
    std::cout << GREEN << "date" << RESET << " - Print the current date." << std::endl;
    std::cout << GREEN << "list" << RESET << " - List all background processes." << std::endl;
    std::cout << GREEN << "close" << RESET << " - Close handles and delete all terminated background processes." << std::endl;
    std::cout << GREEN << "dir" << RESET << " - Print the current working directory." << std::endl;
    std::cout << GREEN << "addpath <path>" << RESET << " - Add a new path to the PATH environment variable." << std::endl;
    std::cout << GREEN << "fork <dir> [foreground/background]" << RESET << " - Create a new process to run an executable file\n from the specified directory in the foreground or background. The default is foreground." << std::endl;
    std::cout << GREEN << "exebat <filepath>" << RESET << " - Execute a batch file from the specified filepath." << std::endl;
    std::cout << GREEN << "cd <dir>" << RESET << " - Change the current directory." << std::endl;
    std::cout << GREEN << "stop <pid>" << RESET << " - Stop a process with the specified process ID (pid)." << std::endl;
    std::cout << GREEN << "resume <pid>" << RESET << " - Resume a stopped process with the specified process ID (pid)." << std::endl;
    std::cout << GREEN << "kill <pid>" << RESET << " - Terminate a process with the specified process ID (pid)." << std::endl;
}
void makeColor() {
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//COORD coordScreen = { 0, 0 }; // top left corner


//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const std::string message = R"(

 .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. 
/ .. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \
\ \/\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ \/ /
 \/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\/ / 
 / /\                                                                            / /\ 
/ /\ \                                                                          / /\ \
\ \/ /  ,--.   ,--.       ,--.                                   ,--.           \ \/ /
 \/ /   |  |   |  | ,---. |  | ,---. ,---. ,--,--,--. ,---.    ,-'  '-. ,---.    \/ / 
 / /\   |  |.'.|  || .-. :|  || .--'| .-. ||        || .-. :   '-.  .-'| .-. |   / /\ 
/ /\ \  |   ,'.   |\   --.|  |\ `--.' '-' '|  |  |  |\   --.     |  |  ' '-' '  / /\ \
\ \/ /  '--'   '--' `----'`--' `---' `---' `--`--`--' `----'     `--'   `---'   \ \/ /
 \/ /       ,--------.,--.                     ,---.  ,--.            ,--.,--.   \/ / 
 / /\       '--.  .--'`--',--,--, ,--. ,--.   '   .-' |  ,---.  ,---. |  ||  |   / /\ 
/ /\ \         |  |   ,--.|      \ \  '  /    `.  `-. |  .-.  || .-. :|  ||  |  / /\ \
\ \/ /         |  |   |  ||  ||  |  \   '     .-'    ||  | |  |\   --.|  ||  |  \ \/ /
 \/ /          `--'   `--'`--''--'.-'  /      `-----' `--' `--' `----'`--'`--'   \/ / 
 / /\                             `---'                                          / /\ 
/ /\ \                                                                          / /\ \
\ \/ /                                                                          \ \/ /
 \/ /                                                                            \/ / 
 / /\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\ 
/ /\ \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \.. \/\ \
\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `'\ `' /
 `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' 


)";
    const int colors[] = {
    FOREGROUND_BLUE,
    FOREGROUND_GREEN,
    FOREGROUND_RED,
    FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_GREEN,
    FOREGROUND_BLUE | FOREGROUND_RED,
    FOREGROUND_GREEN | FOREGROUND_RED,
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
    BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
};

    for (char c : message) {
        SetConsoleTextAttribute(hConsole, colors[rand() % 12]);
        std::cout << c << std::flush;
//        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    // Reset the color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    //SetConsoleCursorPosition(hConsole, coordScreen);
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}





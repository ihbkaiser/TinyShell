#include <iostream>
#include <ctime>
void PrintDate() {

    time_t now = time(0);
    tm *ltm = localtime(&now);
    const char* dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    char buffer[80];
    strftime(buffer, 80, "%d-%m-%Y (%A)", ltm);
    std::cout << "Date: " << buffer << std::endl;
}

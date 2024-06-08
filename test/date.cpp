#include "../include/date.h"
#include <iostream>
#include <ctime>

void PrintDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::cout << "Date: "
              << 1900 + ltm->tm_year << "-"
              << 1 + ltm->tm_mon << "-"
              << ltm->tm_mday << std::endl;
}

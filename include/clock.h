#include <conio.h>
#include <atomic>
#include <thread>
#include <windows.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
#include<thread>

struct TimeZone {
    std::string name;
    int offset;
};

std::vector<TimeZone> timeZones = {
    {"Hanoi", 7},
    {"Bangkok", 7},
    {"London", 1},
    {"New York", -4},
    {"Tokyo", 9},
    {"Sydney", 10}
    // Add more time zones (city, UTC +x)
};

void printAvailableCities() {
    std::cout << "Available cities: ";
    for (size_t i = 0; i < timeZones.size(); ++i) {
        std::cout << timeZones[i].name;
        if (i < timeZones.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

TimeZone* getTimeZone(const std::string& cityName) {
    for (auto& timeZone : timeZones) {
        if (timeZone.name == cityName) {
            return &timeZone;
        }
    }
    return nullptr;
}

void printClock(COORD startpos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool runClock = true;

    while (runClock) {
        printAvailableCities();
        
        std::string cityName;
        std::cout << "Enter the city name to display its time: ";
        while (true) {
            if (getline(std::cin, cityName)) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        TimeZone* selectedTimeZone = getTimeZone(cityName);
        if (selectedTimeZone != nullptr) {
            std::cout << "Press 'h' to terminate the clock !" << std::endl;
            while (runClock) {
                std::time_t t = std::time(nullptr);
                t += selectedTimeZone->offset * 3600;
                std::tm* now = std::gmtime(&t);

                SetConsoleCursorPosition(hConsole, startpos);
                std::cout << "Current time in " << selectedTimeZone->name << ": "
                          << (now->tm_hour < 10 ? "0" : "") << now->tm_hour << ':'
                          << (now->tm_min < 10 ? "0" : "") << now->tm_min << ':'
                          << (now->tm_sec < 10 ? "0" : "") << now->tm_sec << "   " << std::flush;

                for (int i = 0; i < 10; ++i) {
                    if (_kbhit()) {
                        char ch = _getch();
                        if (ch == 'h' || ch == 'H') {
                            runClock = false;
                            break;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        } else {
            std::cout << "City not found! Please enter a valid city name.\n";
        }
    }
}
// just for testing
//int main() {
//    COORD startPos = {0, 2};
//    printClock(startPos);
//    return 0;
//}

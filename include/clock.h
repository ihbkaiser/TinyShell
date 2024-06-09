#include <conio.h> 
#include <atomic> 
#include <thread> 
#include <windows.h> 
#include <ctime> 
#include <iostream> 
#include <vector> 
#include <chrono> 

struct TimeZone {
    std::string name;
    int offset;
};
const std::vector<TimeZone> timeZones = {
        {"Hanoi", 7}, 
        {"Bangkok", 7}, 
        {"London", 1}, 
        {"New York", -4}, 
        {"Tokyo", 9},
        {"Sydney", 10} 
        // Add more time zones (city, UTC +x)
    };

void printClock(COORD startpos) {
    std::cout << "Press 'h' to terminate the clock !\n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool runClock = true;

    while (runClock) {
        std::time_t t = std::time(nullptr);
        std::tm* local = std::localtime(&t);
        std::tm localCopy = *local; 
        std::time_t localTime = std::mktime(&localCopy);
        int localOffset = (localTime - t) / 3600; 
        for (size_t i = 0; i < timeZones.size(); ++i) {
            const auto& timeZone = timeZones[i];
            t = std::time(nullptr);
            t += (timeZone.offset + localOffset) * 3600; 
            std::tm* now = std::gmtime(&t); 
            SetConsoleCursorPosition(hConsole, {startpos.X, startpos.Y+ static_cast<SHORT>(i + 1)}); 
            std::cout << "Current time in " << timeZone.name << ": "
                      << (now->tm_hour < 10 ? "0" : "") << now->tm_hour << ':'
                      << (now->tm_min < 10 ? "0" : "") << now->tm_min << ':'
                      << (now->tm_sec < 10 ? "0" : "") << now->tm_sec << std::flush;
        }

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
}

#ifndef SEARCH_H
#define SEARCH_H

#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>

void SearchGoogle(const std::string& query) {
    // Đường dẫn tới trình duyệt Chrome
    const char* chromePath = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";

    std::ostringstream urlStream;
    urlStream << "https://www.google.com/search?q=" << query;
    std::string url = urlStream.str();

    // Tạo lệnh để mở URL bằng Chrome
    ShellExecute(NULL, "open", chromePath, url.c_str(), NULL, SW_SHOWNORMAL);
}

#endif // SEARCH_H

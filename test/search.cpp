#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (unsigned char c : value) {
        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int(c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}
// thu di bro

void SearchGoogle(const std::string& query) {
    // Đường dẫn tới trình duyệt Chrome
    const char* chromePath = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";

    // Tạo URL tìm kiếm
    std::string encodedQuery = urlEncode(query);
    std::string url = "https://www.google.com/search?q=" + encodedQuery;

    // Convert the UTF-8 string to a wide string
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, NULL, 0);
    wchar_t* wideUrl = new wchar_t[wideSize];
    MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, wideUrl, wideSize);

    // Convert the wide string to the system's default encoding
    int ansiSize = WideCharToMultiByte(CP_ACP, 0, wideUrl, -1, NULL, 0, NULL, NULL);
    char* ansiUrl = new char[ansiSize];
    WideCharToMultiByte(CP_ACP, 0, wideUrl, -1, ansiUrl, ansiSize, NULL, NULL);

    // Tạo lệnh để mở URL bằng Chrome
    ShellExecute(NULL, "open", chromePath, ansiUrl, NULL, SW_SHOWNORMAL);

    // Clean up
    delete[] wideUrl;
    delete[] ansiUrl;
}
// test thu 1 cau tieng viet xem dc chua
int main(){
	system("chcp 65001");
	std::cout << "Pls enter by English \n";
    std::cout << "Enter query: ";
    std::string s;
    std::getline(std::cin, s);
    SearchGoogle(s);
}
//
//int main(){
//	std::cout << "Enter query: ";
//	std::string s;
//	std::getline(std::cin, s);
//	SearchGoogle(s);
//}
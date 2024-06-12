#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>

std::string urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int(c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

void SearchGoogle(const std::string& query) {
    const char* chromePath = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";

    std::string encodedQuery = urlEncode(query);
    std::string url = "https://www.google.com/search?q=" + encodedQuery;

    int wideSize = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, NULL, 0);
    wchar_t* wideUrl = new wchar_t[wideSize];
    MultiByteToWideChar(CP_UTF8, 0, url.c_str(), -1, wideUrl, wideSize);

    int ansiSize = WideCharToMultiByte(CP_ACP, 0, wideUrl, -1, NULL, 0, NULL, NULL);
    char* ansiUrl = new char[ansiSize];
    WideCharToMultiByte(CP_ACP, 0, wideUrl, -1, ansiUrl, ansiSize, NULL, NULL);

    ShellExecute(NULL, "open", chromePath, ansiUrl, NULL, SW_SHOWNORMAL);

    delete[] wideUrl;
    delete[] ansiUrl;
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
//    system("chcp 65001");
    std::wcout << L"Pls enter by English \n";
    std::wcout << L"Enter query: ";
    std::wstring ws;
    if(std::getline(std::wcin, ws))cout<<"ok";
    else cout<<"error";

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string s = converter.to_bytes(ws);

    SearchGoogle(s);
}

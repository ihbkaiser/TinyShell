#include "../include/executebatchfile.h"

int main() {
    std::string input;

    while (true) {
        std::cout << "tiny-shell> ";
        std::getline(std::cin, input);

        // Kiểm tra lệnh "exit"
        if (input == "exit") {
            break
        }

        // Kiểm tra và thực thi file batch
        if (input.substr(input.find_last_of(".") + 1) == "bat") {
            executeBatchFile(input);
        } else {
            std::cout << "Unsupported command or file type. Please enter a .bat file or type 'exit' to quit.\n";
        }
    }

    return 0;
}

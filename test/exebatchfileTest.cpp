#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <tchar.h>
#include "../utils/splitcommand.h"
#include "../include/executebatchfile.h"


using namespace std;


int _tmain( int argc, TCHAR *argv[] )
{
    while(true) {
        string input;
        cout << "\nEnter command: ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        if (input.substr(0, 8) == "exebatch")
        {
            vector<string> command = split(input, ' ');

            if (command.size() > 1)
            {
                exeBatchFile(command[1].c_str());
            }
            else
            {
                cout << "Usage: exebatch <filepath>" << endl;
            }
        }
        // add more commands here
    }

    return 0;
}
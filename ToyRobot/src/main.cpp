#include "parse.h"
#include "command.h"

bool Command::place_initialized_ = false;
bool kLoopFlag = true;

/// @brief This contains the main loop of the program
/// @return Returns 0 upon exit
int main()
{
    int result;
    string input;

    cout << "-----------------------\n";

    while(kLoopFlag)
    {
        getline(cin >> ws, input);
                   
        Command* command = NULL;
        list<string> arguments = {};
        Parse parser;  

        result = parser.ParseInput(input, &command, &arguments);
        if(result == kOk)
        {
            result = command->ValidateArgument(arguments);
            if(result == kOk)
            {
                result = command->Execute();
            }
            delete (command);
        }

        if(result != kOk && result != kExit)
        {
            cout << kError.at(result) << endl;
        }
    }
    
    cout << "\n-----------------------\n";

    return 0;
}
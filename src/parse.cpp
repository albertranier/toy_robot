#include "parse.h"

/// @brief Splits the input string to command and argument strings
/// @param input User input string
void Parse::SetInput(string input)
{
    char* token = strtok(&input[0], " ");
    if(token != NULL) {
        this->parsed_command_ = token;
    }
    
    token = strtok(NULL, " ");
    if(token != NULL) {
        this->parsed_argument_ = token;
    }
}

/// @brief Converts the argument string to argument list
/// @param output_argument The output argument list
void Parse::GetArguments(list<string>* output_argument)
{
    list<string> args;
    char* input = &this->parsed_argument_[0];

    if(input != NULL)
    {
        char* token = strtok(input, ","); 

        while (token != NULL) {
            args.emplace_back(token);
            token = strtok(NULL, ",");
        }
    }

    *output_argument = args;
}

/// @brief Generates a command object depending on the input command
/// @param output_command The output command object
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int Parse::CreateCommand(Command** output_command)
{
    Command* command = NULL;
    string input = this->parsed_command_;
    int result = kOk;

    if(input.compare(PLACE) == 0)
    {
        command = new CommandPlace();
    }
    else if(input.compare(MOVE) == 0)
    {
        command = new CommandMove();
    }
    else if(input.compare(LEFT) == 0)
    {
        command = new CommandLeft();
    }
    else if(input.compare(RIGHT) == 0)
    {
        command = new CommandRight();
    }
    else if(input.compare(REPORT) == 0)
    {
        command = new CommandReport();
    }
    else if(input.compare(EXIT) == 0)
    {
        result = kExit;
        kLoopFlag = false;
    }
    else
    {
        result = kError1;     
    }

    *output_command = command;
    return result;
}

/// @brief Parses the user input string to acquire the command and arguments
/// @param input The user input string
/// @param output_command The output command object
/// @param output_argument The output argument list
/// @return 
int Parse::ParseInput (string input, Command** output_command, list<string>* output_argument)
{
    int result = kOk;
    
    SetInput(input);
    GetArguments(output_argument);
    result = CreateCommand(output_command);
    
    return result;
}
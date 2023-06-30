#include "command_move.h"

/// @brief Validates if the MOVE command arguments are valid.
/// @param input MOVE command arguments
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandMove :: ValidateArgument (list<string> input)
{
    int result = kOk;
    if (!input.empty())
    {
        result = kError2;
    }

    return result;
}

/// @brief Executes the MOVE command
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandMove :: Execute()
{
    int result;
    
    if(this->place_initialized_)
    {
        result = Robot::Instance().Move();
    }
    else
    {
        result = kError3;
    }

    return result;
}
#include "command_left.h"

/// @brief Validates if the LEFT command arguments are valid.
/// @param input LEFT command arguments
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandLeft :: ValidateArgument (list<string> input)
{
    int result = kOk;
    if (!input.empty())
    {
        result = kError2;
    }

    return result;
}

/// @brief Executes the LEFT command
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandLeft :: Execute()
{
    int result;

    if(this->place_initialized_)
    {
        result = Robot::Instance().RotateLeft();
    }
    else
    {
        result = kError3;
    }

    return result;
}
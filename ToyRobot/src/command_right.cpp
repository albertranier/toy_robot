#include "command_right.h"

/// @brief Validates if the RIGHT command arguments are valid.
/// @param input RIGHT command arguments
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandRight :: ValidateArgument (list<string> input)
{
    int result = kOk;
    if (!input.empty())
    {
        result = kError2;
    }

    return result;
}

/// @brief Executes the RIGHT command
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandRight :: Execute()
{
    int result;

    if(this->place_initialized_)
    {
        result = Robot::Instance().RotateRight();
    }
    else
    {
        result = kError3;
    }

    return result;
}
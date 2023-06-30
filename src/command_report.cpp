#include "command_report.h"

/// @brief Validates if the REPORT command arguments are valid.
/// @param input REPORT command arguments
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandReport :: ValidateArgument (list<string> input)
{
    int result = kOk;
    if (!input.empty())
    {
        result = kError2;
    }

    return result;
}

/// @brief Executes the REPORT command
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandReport :: Execute()
{
    int result;
    int position_x;
    int position_y;
    pair<string,int> position_f;
    
    if(this->place_initialized_)
    {
        result = Robot::Instance().GetPosition(&position_x, &position_y, &position_f);
        printf("Output: %d,%d,%s\n",position_x,position_y,position_f.first.data());
    }
    else
    {
        result = kError3;
    }

    return result;
}
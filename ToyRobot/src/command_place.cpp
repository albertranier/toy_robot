#include "command_place.h"

/// @brief Validates if the PLACE command arguments are valid.
/// @param input PLACE command arguments
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandPlace :: ValidateArgument  (list<string> input)
{
    int result = kError2;

    if (input.size() == 3)
    {
        list<string>::iterator iterator = input.begin();
        string posX = *iterator;

        advance(iterator,1);
        string posY = *iterator;

        advance(iterator,1);
        string posF = *iterator;

        try
        {
            this->position_x_ = stoi(posX);
            this->position_y_ = stoi(posY);

            for(auto f: kHeading)
            {
                if(posF.compare(f.first) == 0)
                {
                    this->position_f_.first=f.first;
                    this->position_f_.second=f.second;
                    result = kOk;
                }
            }
        }
        catch(const exception& e)
        {
            //Do Nothing
        }
    }

    return result;
}

/// @brief Executes the PLACE command
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int CommandPlace :: Execute()
{
    int result;
    
    result = Robot::Instance().SetPosition(this->position_x_, this->position_y_, this->position_f_);
    if(result == kOk)
    {
        this->place_initialized_ = true;
    }                    

    return result;
}
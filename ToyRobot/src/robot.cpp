#include "robot.h"

/// @brief Singleton instance
/// @return The single instance of Robot class
Robot &Robot::Instance()
{
    static Robot instance;
    return instance;
}

/// @brief Sets the position of the robot
/// @param position_x The X position
/// @param position_y The Y position
/// @param position_f The heading position
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int Robot::SetPosition(int position_x, int position_y, pair<string, int> position_f)
{
    int result = kError4;
    
    if(Table::Instance().IsValidPosition(position_x, position_y))
    {
        this->position_x_ = position_x;
        this->position_y_ = position_y;
        this->position_f_.first = position_f.first;
        this->position_f_.second = position_f.second;

        result = kOk;
    }
    else
    {
        result = kError4;
    }

    return result;
}

/// @brief Moves the robot forwards the heading
/// @return Returns 0 if OK. Otherwise, returns a negative value.
int Robot::Move()
{
    int result = kError4;
    int target_x = this->position_x_;
    int target_y = this->position_y_;
    
    switch (this->position_f_.second)
    {
        case kDegreeNorth:
            target_y++;
            break;
        case kDegreeEast:
            target_x++;
            break;
        case kDegreeSouth:
            target_y--;
            break;
        case kDegreeWest:
            target_x--;
            break;
        default:
            // Not possible
            result = kError4;
            break;
    }

    if(Table::Instance().IsValidPosition(target_x, target_y))
    {
        this->position_x_ = target_x;
        this->position_y_ = target_y;

        result = kOk;
    }
    else
    {
        result = kError4;
    }

    return result;
}

/// @brief Rotates the heading of the robot to the left
/// @return Returns 0.
int Robot::RotateLeft()
{
    int result = kOk;

    int target_f = this->position_f_.second + 360;
    target_f = (target_f + ROTATE_LEFT) % 360;

    for(auto f: kHeading)
    {
        if(f.second == target_f)
        {
            this->position_f_.first = f.first;
            this->position_f_.second = f.second;
        }
    }

    return result;
}

/// @brief Rotates the heading of the robot to the right
/// @return Returns 0.
int Robot::RotateRight()
{
    int result = kOk;

    int target_f = this->position_f_.second;
    target_f = (target_f + ROTATE_RIGHT) % 360;

    for(auto f: kHeading)
    {
        if(f.second == target_f)
        {
            this->position_f_.first=f.first;
            this->position_f_.second=f.second;
        }
    }

    return result;
}

/// @brief Acquires the position of the robot
/// @param position_x The output position x of the robot
/// @param position_y The output position y of the robot
/// @param position_f The output heading of the robot
/// @return Returns 0
int Robot::GetPosition(int *position_x, int *position_y, pair<string, int> *position_f)
{
    int result = kOk;

    *position_x = this->position_x_;
    *position_y = this->position_y_;
    position_f->first = this->position_f_.first;
    position_f->second = this->position_f_.second;

    return result;
}

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

#include "common.h"
#include "table.h"

class Robot
{
private:
    int position_x_;
    int position_y_;
    pair<string,int> position_f_;
    Robot(){};

public:
    static Robot& Instance();
    Robot(Robot const&) = delete;
    void operator=(Robot const&)  = delete;
    int SetPosition(int, int, pair<string,int>);
    int Move();
    int RotateLeft();
    int RotateRight();
    int GetPosition(int*, int*, pair<string,int>*);
};

#endif  // INC_ROBOT_H_
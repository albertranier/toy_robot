#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include "common.h"
#include "robot.h"

class Command
{
public:
    static bool place_initialized_;
    virtual ~Command(){};
    virtual int ValidateArgument(list<string>) {return 0;};
    virtual int Execute() {return 0;};
};

#endif  // INC_COMMAND_H_
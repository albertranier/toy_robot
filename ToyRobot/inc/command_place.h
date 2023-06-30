#ifndef INC_COMMANDPLACE_H_
#define INC_COMMANDPLACE_H_

#include "common.h"
#include "command.h"

class CommandPlace : public Command
{
    private:
        int position_x_;
        int position_y_;
        pair<string,int> position_f_;
    public:
        int ValidateArgument(list<string>);
        int Execute();
};

#endif  // INC_COMMANDPLACE_H_
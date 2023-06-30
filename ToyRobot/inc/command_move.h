#ifndef INC_COMMANDMOVE_H_
#define INC_COMMANDMOVE_H_

#include "common.h"
#include "command.h"

class CommandMove : public Command
{
    public:
        int ValidateArgument(list<string>);
        int Execute();
};

#endif  // INC_COMMANDMOVE_H_
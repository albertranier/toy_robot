#ifndef INC_COMMANDLEFT_H_
#define INC_COMMANDLEFT_H_

#include "common.h"
#include "command.h"

class CommandLeft : public Command
{
    public:
        int ValidateArgument(list<string>);
        int Execute();
};

#endif  // INC_COMMANDLEFT_H_
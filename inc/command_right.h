#ifndef INC_COMMANDRIGHT_H_
#define INC_COMMANDRIGHT_H_

#include "common.h"
#include "command.h"

class CommandRight : public Command
{
    public:
        int ValidateArgument(list<string>);
        int Execute();
};

#endif  // INC_COMMANDRIGHT_H_
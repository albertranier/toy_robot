#ifndef INC_COMMANDREPORT_H_
#define INC_COMMANDREPORT_H_

#include "common.h"
#include "command.h"

class CommandReport : public Command
{
    public:
        int ValidateArgument(list<string>);
        int Execute();
};

#endif  // INC_COMMANDREPORT_H_
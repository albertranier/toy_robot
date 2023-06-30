#ifndef INC_PARSE_H_
#define INC_PARSE_H_

#include "common.h"
#include "command.h"
#include "command_place.h"
#include "command_move.h"
#include "command_left.h"
#include "command_right.h"
#include "command_report.h"

class Parse
{
private:
    string parsed_command_;
    string parsed_argument_;
    void SetInput(string);
    void GetArguments(list<string>*);
    int CreateCommand(Command**);
public:
    int ParseInput (string, Command**, list<string>*);
};

#endif  // INC_PARSE_H_
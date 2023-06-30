#ifndef INC_TABLE_H_
#define INC_TABLE_H_

#include "common.h"

class Table
{
private:
    Table(){};
public:
    static Table& Instance();
    Table(Table const&) = delete;
    void operator=(Table const&)  = delete;
    bool IsValidPosition(int, int);
};

#endif  // INC_TABLE_H_
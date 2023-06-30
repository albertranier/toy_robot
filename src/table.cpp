#include "table.h"

/// @brief Singleton instance
/// @return The single instance of Table class
Table &Table::Instance()
{
    static Table instance;
    return instance;
}

/// @brief Checks if the position is within the scope of the table
/// @param position_x The position x
/// @param position_y The position y
/// @return Returns true if within scope. Otherwise, returns false.
bool Table::IsValidPosition(int position_x, int position_y)
{
    bool result = false;

    if(position_x >= TABLE_MIN_X && position_x <= TABLE_MAX_X &&
        position_y >= TABLE_MIN_Y && position_y <= TABLE_MAX_Y)
    {
        result = true;
    }

    return result;
}

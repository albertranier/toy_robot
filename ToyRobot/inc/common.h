#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>

// Valid input commands
#define PLACE "PLACE"
#define MOVE "MOVE"
#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define REPORT "REPORT"
#define EXIT "EXIT"

// Valid headings
#define NORTH "NORTH"
#define SOUTH "SOUTH"
#define EAST "EAST"
#define WEST "WEST"

// Table minimum and maximum x,y positions
#define TABLE_MAX_X 4
#define TABLE_MAX_Y 4
#define TABLE_MIN_X 0
#define TABLE_MIN_Y 0

// Error details
#define ERROR_1 "\t[Error] Invalid input command"
#define ERROR_2 "\t[Error] Invalid input argument"
#define ERROR_3 "\t[Error] Invalid command sequence"
#define ERROR_4 "\t[Error] Invalid target location"

// Left and Right degree calculation
#define ROTATE_LEFT -90
#define ROTATE_RIGHT +90

using namespace std;

enum ResultCode
{
    kOk = 0,        // Process is OK
    kError1 = -1,   // Invalid command
    kError2 = -2,   // Invalid arguments
    kError3 = -3,   // Invalid command sequence
    kError4 = -4,   // Invalid target location
    kExit = -99,
};

enum HeadingDegree
{
    kDegreeNorth    = 0,    // North heading
    kDegreeEast     = 90,   // East heading
    kDegreeSouth    = 180,  // South heading
    kDegreeWest     = 270,  // West heading
};

// Mapping between heading and its corresponding degree
const map<string, int> kHeading = {
    {NORTH  ,kDegreeNorth   },  
    {EAST   ,kDegreeEast    },
    {SOUTH  ,kDegreeSouth   },
    {WEST   ,kDegreeWest    },
};

// Mapping between error code and its details
const map<int, string> kError = {
    {kError1  ,ERROR_1  },
    {kError2  ,ERROR_2  },
    {kError3  ,ERROR_3  },
    {kError4  ,ERROR_4  },
};

extern bool kLoopFlag; // flag to control the main loop

#endif  // INC_COMMON_H_
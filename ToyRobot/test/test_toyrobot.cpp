#include <assert.h>

#include "../inc/parse.h"
#include "../inc/command_place.h"
#include "../inc/command_move.h"
#include "../inc/command_left.h"
#include "../inc/command_right.h"
#include "../inc/command_report.h"
#include "../inc/robot.h"
#include "../inc/table.h"

bool Command::place_initialized_ = false;
bool kLoopFlag = true;

void TestParse()
{
    Parse parser;
    Command* output_command;
    list<string> output_argument;
    
    cout << "---------- Start Parse Unit Testing -------------" << endl;
    cout << "Testing .................................... ";
    // OK - PLACE command is all caps
    assert(parser.ParseInput("PLACE 0,0,NORTH", &output_command, &output_argument) == kOk);

    // NG - PLACE command is mixed caps
    assert(parser.ParseInput("pLACE 0,0,NORTH", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("PlACE 0,0,NORTH", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("PLaCE 0,0,NORTH", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("PLAcE 0,0,NORTH", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("PLACe 0,0,NORTH", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("place 0,0,NORTH", &output_command, &output_argument) == kError1);

    // OK - LEFT command is all caps
    assert(parser.ParseInput("LEFT", &output_command, &output_argument) == kOk);

    // NG - LEFT command is mixed caps
    assert(parser.ParseInput("lEFT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("LeFT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("LEfT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("LEFt", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("left", &output_command, &output_argument) == kError1);

    // OK - RIGHT command is all caps
    assert(parser.ParseInput("RIGHT", &output_command, &output_argument) == kOk);

    // NG - RIGHT command is mixed caps
    assert(parser.ParseInput("rIGHT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("RiGHT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("RIgHT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("RIGhT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("RIGHt", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("right", &output_command, &output_argument) == kError1);

    // OK - MOVE command is all caps
    assert(parser.ParseInput("MOVE", &output_command, &output_argument) == kOk);

    // NG - MOVE command is mixed caps
    assert(parser.ParseInput("mOVE", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("MoVE", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("MOvE", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("MOVe", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("move", &output_command, &output_argument) == kError1);

    // OK - REPORT command is all caps
    assert(parser.ParseInput("REPORT", &output_command, &output_argument) == kOk);

    // NG - REPORT command is mixed caps
    assert(parser.ParseInput("rEPORT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("RePORT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("REpORT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("REPoRT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("REPOrT", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("REPORt", &output_command, &output_argument) == kError1);
    assert(parser.ParseInput("report", &output_command, &output_argument) == kError1);
    
    cout << "[OK]" << endl;
    cout << "---------- End Parse Unit Testing ---------------" << endl << endl;
}

void TestCommandPlace()
{
    CommandPlace command_place;
    
    cout << "---------- Start Command_Place Unit Testing -----" << endl;
    cout << "Testing .................................... ";
    // OK - PLACE argument is valid
    assert(command_place.ValidateArgument({"0","0","NORTH"}) == kOk);
    assert(command_place.ValidateArgument({"0","0","EAST"}) == kOk);
    assert(command_place.ValidateArgument({"0","0","WEST"}) == kOk);
    assert(command_place.ValidateArgument({"0","0","SOUTH"}) == kOk);

    // NG - PLACE argument is missing
    assert(command_place.ValidateArgument({}) == kError2);
    assert(command_place.ValidateArgument({""}) == kError2);
    assert(command_place.ValidateArgument({"0"}) == kError2);
    assert(command_place.ValidateArgument({"0","0"}) == kError2);
    assert(command_place.ValidateArgument({"NORTH"}) == kError2);

    // NG - PLACE argument is incorrect types
    assert(command_place.ValidateArgument({"a","a","NORTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","a","NORTH"}) == kError2);
    assert(command_place.ValidateArgument({"a","0","NORTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","0"}) == kError2);

    // NG - PLACE argument is mixed caps
    assert(command_place.ValidateArgument({"0","0","nORTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","NoRTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","NOrTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","NORtH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","NORTh"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","north"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","sOUTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","SoUTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","SOuTH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","SOUtH"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","SOUTh"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","south"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","eAST"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","EaST"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","EAsT"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","EASt"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","east"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","wEST"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","WeST"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","WEsT"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","WESt"}) == kError2);
    assert(command_place.ValidateArgument({"0","0","west"}) == kError2);
    
    // OK - PLACE execution with PLACE initialized
    Command::place_initialized_ = true;
    command_place.ValidateArgument({"0","0","NORTH"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = true;
    command_place.ValidateArgument({"0","0","EAST"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = true;
    command_place.ValidateArgument({"0","0","WEST"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = true;
    command_place.ValidateArgument({"0","0","SOUTH"});
    assert(command_place.Execute() == kOk);

    // OK - PLACE execution with PLACE not initialized
    Command::place_initialized_ = false;
    command_place.ValidateArgument({"0","0","NORTH"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = false;
    command_place.ValidateArgument({"0","0","EAST"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = false;
    command_place.ValidateArgument({"0","0","WEST"});
    assert(command_place.Execute() == kOk);
    Command::place_initialized_ = false;
    command_place.ValidateArgument({"0","0","SOUTH"});
    assert(command_place.Execute() == kOk);  

    cout << "[OK]" << endl;
    cout << "---------- End Command_Place Unit Testing -------" << endl << endl;
}

void TestCommandLeft()
{
    CommandLeft command_left;
    CommandPlace command_place;
    
    cout << "---------- Start Command_Left Unit Testing ------" << endl;
    cout << "Testing .................................... ";
    // OK - LEFT argument is empty
    assert(command_left.ValidateArgument({}) == kOk);

    // NG - LEFT argument is not empty
    assert(command_left.ValidateArgument({"0"}) == kError2);
    assert(command_left.ValidateArgument({"NORTH"}) == kError2);
    assert(command_left.ValidateArgument({"0","0","NORTH"}) == kError2);

    // OK - LEFT execution with PLACE initialized
    command_place.ValidateArgument({"0","0","NORTH"});
    command_place.Execute();
    command_left.ValidateArgument({});
    assert(command_left.Execute() == kOk);

    // NG - LEFT execution with PLACE not initialized
    Command::place_initialized_ = false;
    command_left.ValidateArgument({});
    assert(command_left.Execute() == kError3);    

    cout << "[OK]" << endl;
    cout << "---------- End Command_Left Unit Testing --------" << endl << endl;
}

void TestCommandRight()
{
    CommandRight command_right;
    CommandPlace command_place;
    
    cout << "---------- Start Command_Right Unit Testing -----" << endl;
    cout << "Testing .................................... ";
    // OK - RIGHT argument is empty
    assert(command_right.ValidateArgument({}) == kOk);

    // NG - RIGHT argument is not empty
    assert(command_right.ValidateArgument({"0"}) == kError2);
    assert(command_right.ValidateArgument({"NORTH"}) == kError2);
    assert(command_right.ValidateArgument({"0","0","NORTH"}) == kError2);

    // OK - RIGHT execution with PLACE initialized
    command_place.ValidateArgument({"0","0","NORTH"});
    command_place.Execute();
    command_right.ValidateArgument({});
    assert(command_right.Execute() == kOk);

    // NG - RIGHT execution with PLACE not initialized
    Command::place_initialized_ = false;
    command_right.ValidateArgument({});
    assert(command_right.Execute() == kError3);    

    cout << "[OK]" << endl;
    cout << "---------- End Command_Right Unit Testing -------" << endl << endl;
}

void TestCommandMove()
{
    CommandMove command_move;
    CommandPlace command_place;
    
    cout << "---------- Start Command_Move Unit Testing ------" << endl;
    cout << "Testing .................................... ";
    // OK - MOVE argument is empty
    assert(command_move.ValidateArgument({}) == kOk);

    // NG - MOVE argument is not empty
    assert(command_move.ValidateArgument({"0"}) == kError2);
    assert(command_move.ValidateArgument({"NORTH"}) == kError2);
    assert(command_move.ValidateArgument({"0","0","NORTH"}) == kError2);

    // OK - MOVE execution with PLACE initialized
    command_place.ValidateArgument({"0","0","NORTH"});
    command_place.Execute();
    command_move.ValidateArgument({});
    assert(command_move.Execute() == kOk);

    // NG - MOVE execution with PLACE not initialized
    Command::place_initialized_ = false;
    command_move.ValidateArgument({});
    assert(command_move.Execute() == kError3);    

    cout << "[OK]" << endl;
    cout << "---------- End Command_Move Unit Testing --------" << endl << endl;
}

void TestCommandReport()
{
    CommandReport command_report;
    CommandPlace command_place;
    
    cout << "---------- Start Command_Report Unit Testing ----" << endl;
    cout << "Testing .................................... ";
    // OK - REPORT argument is empty
    assert(command_report.ValidateArgument({}) == kOk);

    // NG - REPORT argument is not empty
    assert(command_report.ValidateArgument({"0"}) == kError2);
    assert(command_report.ValidateArgument({"NORTH"}) == kError2);
    assert(command_report.ValidateArgument({"0","0","NORTH"}) == kError2);

    // OK - REPORT execution with PLACE initialized
    command_place.ValidateArgument({"0","0","NORTH"});
    command_place.Execute();
    command_report.ValidateArgument({});
    assert(command_report.Execute() == kOk);

    // NG - REPORT execution with PLACE not initialized
    Command::place_initialized_ = false;
    command_report.ValidateArgument({});
    assert(command_report.Execute() == kError3);    

    cout << "[OK]" << endl;
    cout << "---------- End Command_Report Unit Testing ------" << endl << endl;
}

void TestRobot()
{
    pair<string, int> head_north = {NORTH, kDegreeNorth};
    pair<string, int> head_east = {EAST, kDegreeEast};
    pair<string, int> head_south = {SOUTH, kDegreeSouth};
    pair<string, int> head_west = {WEST, kDegreeWest};

    cout << "---------- Start Robot Unit Testing -------------" << endl;
    cout << "Testing .................................... ";
    // OK - Set Position is within the 5x5 table
    assert(Robot::Instance().SetPosition(0,0,head_north) == kOk);
    assert(Robot::Instance().SetPosition(1,0,head_north) == kOk);
    assert(Robot::Instance().SetPosition(2,0,head_north) == kOk);
    assert(Robot::Instance().SetPosition(3,0,head_north) == kOk);
    assert(Robot::Instance().SetPosition(4,0,head_north) == kOk);
    assert(Robot::Instance().SetPosition(0,1,head_north) == kOk);
    assert(Robot::Instance().SetPosition(0,2,head_north) == kOk);
    assert(Robot::Instance().SetPosition(0,3,head_north) == kOk);
    assert(Robot::Instance().SetPosition(0,4,head_north) == kOk);

    // NG - Set Position is outside the 5x5 table
    assert(Robot::Instance().SetPosition(-1,0,head_north) == kError4);
    assert(Robot::Instance().SetPosition(0,-1,head_north) == kError4);
    assert(Robot::Instance().SetPosition(-1,-1,head_north) == kError4);
    assert(Robot::Instance().SetPosition(5,0,head_north) == kError4);
    assert(Robot::Instance().SetPosition(0,5,head_north) == kError4);
    assert(Robot::Instance().SetPosition(5,5,head_north) == kError4);

    // OK - Move North is within the 5x5 table
    Robot::Instance().SetPosition(0,0,head_north);
    assert(Robot::Instance().Move() == kOk);

    // NG - Move North is outside the 5x5 table
    Robot::Instance().SetPosition(0,4,head_north);
    assert(Robot::Instance().Move() == kError4);

    // OK - Move South is within the 5x5 table
    Robot::Instance().SetPosition(0,4,head_south);
    assert(Robot::Instance().Move() == kOk);

    // NG - Move South is outside the 5x5 table
    Robot::Instance().SetPosition(0,0,head_south);
    assert(Robot::Instance().Move() == kError4);

    // OK - Move East is within the 5x5 table
    Robot::Instance().SetPosition(0,0,head_east);
    assert(Robot::Instance().Move() == kOk);

    // NG - Move East is outside the 5x5 table
    Robot::Instance().SetPosition(4,0,head_east);
    assert(Robot::Instance().Move() == kError4);

    // OK - Move West is within the 5x5 table
    Robot::Instance().SetPosition(4,0,head_west);
    assert(Robot::Instance().Move() == kOk);

    // NG - Move West is outside the 5x5 table
    Robot::Instance().SetPosition(0,0,head_west);
    assert(Robot::Instance().Move() == kError4);

    int position_x;
    int position_y;
    pair<string, int> position_f;

    // OK - Get Position is valid
    Robot::Instance().SetPosition(0,0,head_north);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == NORTH);
    assert(position_f.second == kDegreeNorth);

    // OK - Rotate Right is valid
    Robot::Instance().SetPosition(0,0,head_north);
    assert(Robot::Instance().RotateRight() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == EAST);
    assert(position_f.second == kDegreeEast);

    assert(Robot::Instance().RotateRight() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == SOUTH);
    assert(position_f.second == kDegreeSouth);

    assert(Robot::Instance().RotateRight() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == WEST);
    assert(position_f.second == kDegreeWest);

    assert(Robot::Instance().RotateRight() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == NORTH);
    assert(position_f.second == kDegreeNorth);

    // OK - Rotate Left is valid
    Robot::Instance().SetPosition(0,0,head_north);
    assert(Robot::Instance().RotateLeft() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == WEST);
    assert(position_f.second == kDegreeWest);

    assert(Robot::Instance().RotateLeft() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == SOUTH);
    assert(position_f.second == kDegreeSouth);

    assert(Robot::Instance().RotateLeft() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == EAST);
    assert(position_f.second == kDegreeEast);

    assert(Robot::Instance().RotateLeft() == kOk);
    assert(Robot::Instance().GetPosition(&position_x, &position_y, &position_f) == kOk);
    assert(position_x == 0);
    assert(position_y == 0);
    assert(position_f.first == NORTH);
    assert(position_f.second == kDegreeNorth);

    cout << "[OK]" << endl;
    cout << "---------- End Robot Unit Testing ---------------" << endl << endl;
}

void TestTable()
{
    cout << "---------- Start Table Unit Testing -------------" << endl;
    cout << "Testing .................................... ";
    // OK - Table position is valid
    assert(Table::Instance().IsValidPosition(0,0)== true);
    assert(Table::Instance().IsValidPosition(0,1)== true);
    assert(Table::Instance().IsValidPosition(1,0)== true);
    assert(Table::Instance().IsValidPosition(4,4)== true);
    assert(Table::Instance().IsValidPosition(1,4)== true);
    assert(Table::Instance().IsValidPosition(4,1)== true);

    // NG - Table position is valid
    assert(Table::Instance().IsValidPosition(-1,-1)== false);
    assert(Table::Instance().IsValidPosition(0,-1)== false);
    assert(Table::Instance().IsValidPosition(-1,0)== false);
    assert(Table::Instance().IsValidPosition(5,5)== false);
    assert(Table::Instance().IsValidPosition(0,5)== false);
    assert(Table::Instance().IsValidPosition(5,0)== false);

    cout << "[OK]" << endl;
    cout << "---------- End Table Unit Testing ---------------" << endl << endl;
}

int main()
{
    cout << "========== Start Unit Testing ===================" << endl << endl;

    TestParse();
    TestCommandPlace();
    TestCommandLeft();
    TestCommandRight();
    TestCommandMove();
    TestCommandReport();
    TestRobot();
    TestTable();

    cout << "========== End Unit Testing =====================" << endl << endl;
    return 0;
}
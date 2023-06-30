CC := g++
CFLAGS := -std=c++11 -Wall
INCDIR := inc
SRCDIR := src
BINDIR := bin
OBJDIR := obj
TESTDIR:= test

BINOUT := ToyRobot.exe
TESTOUT := ToyRobotTest.exe

# BINARY OUTPUT
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE := $(BINDIR)/$(BINOUT)

# TEST OUTPUT
TESTSRCS := $(wildcard $(TESTDIR)/*.cpp $(SRCDIR)/parse.cpp $(SRCDIR)/robot.cpp $(SRCDIR)/table.cpp $(SRCDIR)/command_*.cpp)
TESTOBJS := $(TESTSRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TESTEXECUTABLE := $(BINDIR)/$(TESTOUT)

VPATH := $(SRCDIR)

bin: $(EXECUTABLE)
	@echo "======================== BUILDING TOYROBOT DONE ====================" 
	
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@


test: $(TESTEXECUTABLE)
	@echo "======================== BUILDING TEST DONE ========================"

$(TESTEXECUTABLE): $(TESTOBJS)
	$(CC) $(CFLAGS) $(TESTOBJS) -o $(TESTEXECUTABLE)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@


all: $(EXECUTABLE) $(TESTEXECUTABLE)
	@echo "============== BUILDING TOYROBOT and TEST DONE ====================="


clean:
	rm -f $(OBJS) $(EXECUTABLE) $(TESTEXECUTABLE)
	@echo "======================== CLEANING DONE ============================="
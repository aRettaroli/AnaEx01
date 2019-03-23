#compiler
CXX	= g++

#flags
CXXFLAGS	= -Wall -g

#Root flags and libraries
ROOTCFLAGS 	= $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS	= $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS	= $(shell $(ROOTSYS)/bin/root-config --glibs)

LIBS		= $(ROOTLIBS)
LIBS		+= $(ROOTGLIBS)

FLAGS		= $(CXXFLAGS)
FLAGS		+= $(ROOTFLAGS)
FLAGS		+= -std=c++11

#include directories
INCLUDE		= -I./ -I$(ROOTSYS)/include

#----------------------------------------------------
#default target
default_target: main
.PHONY: default_target


#compiling rule
main: CloudChamber.C
	g++ $(FLAGS) $(INCLUDE) CloudChamber.C $(LIBS) -o mainChamb 


#clean rule
.PHONY: clean
clean:
	rm -f mainChamb

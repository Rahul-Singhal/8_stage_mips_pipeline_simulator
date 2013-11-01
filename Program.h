#ifndef PROG_H
#define PROG_H

#include <iostream>
#include <vector>
#include "Instruction.h"
#include "Register.h"
#include "Stage.h"
#include "Parser.h"
#include "System.h"
#include "Add.h"
#include <list>
#include <vector>

using namespace std;


class Program: public System{
public:
	// Parser parser;
	vector <Add> code;
	list <Add> currInstructions;
	Program(string filename);
	void execute();

private:
	void runOneClockCycle(); // enough said
	int instrId;
	vector <vector <Add*> > sepInstructions;
};

#endif
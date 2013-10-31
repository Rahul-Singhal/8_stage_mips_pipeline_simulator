#ifndef PROG_H
#define PROG_H

#include <iostream>
#include <vector>
#include "Instruction.h"
#include "Register.h"
#include "Stage.h"
#include "Parser.h"
#include "System.h"
#include <list>
#include <vector>

using namespace std;


class Program: public System{

	Parser parser;
	vector <Instruction> code;
	list <Instruction> currInstructions;
	Program(string filename);
	void execute();

private:
	void runOneClockCycle(); // enough said
	int instrId;
	vector <vector <Instruction*> > sepInstructions;
};

#endif
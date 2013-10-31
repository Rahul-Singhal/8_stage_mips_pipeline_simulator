#ifndef PROG_H
#define PROG_H

#include <iostream>
#include <vector>
#include "Instruction.h"
#include "Register.h"
#include "Stage.h"
#include "Parser.h"
#include <list>

using namespace std;

extern vector <Register> registers; /* Declaration of register file common to all files */

extern vector <Stage> stages; /* Declaration of stages common to all files */

class Program{
	Parser parser;
	list <Instruction> currInstructions;
	Program(string filename);
	void execute();
};

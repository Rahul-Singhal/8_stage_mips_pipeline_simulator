#ifndef PROG_H
#define PROG_H

#include <iostream>
#include <vector>
#include "Instruction.h"
#include "Register.h"
#include "Stage.h"
#include "Parser.h"
#include <list>
#include <vector>

using namespace std;


class Program: public System{
	Parser parser;
	vector <Instruction> code;
	list <Instruction> currInstructions;
	Program(string filename);
	void execute();
};

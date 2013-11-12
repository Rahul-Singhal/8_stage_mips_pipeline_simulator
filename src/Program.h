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
// #include "Addi.h"
// #include "Sub.h"
#include "Mult.h"
#include "Instruction.h"
#include <list>
#include <map>
#include <string>
#include <vector>
#include <iterator>
#include <cstring>

/*

CURRENT STAGES:
0: 	stage before any stage(completely abstract)
1: 	IF1
2:	IF2
3:	ID
4:	EX 			: \
5:	MULT 		: - - > these three are parallel(independent). Order between them doesn't matter
6:	DIV 		: /
7:	MEM1
8:	MEM2
9:	MEM3
10:	WB

Because of this the next stage for each instruction at any stage wouldn't just be currentStage++
rather it would depend on the instruction as well as which stage is it in right now

*/

using namespace std;


class Program: public System{
public:
	Parser parser;
	vector <Instruction *> code;
	vector <Instruction *> codeSnippet;
	list <Instruction *> currInstructions;
	Program(string filename);
	vector <Instruction> execute();
	void executeAll();
	void init();
private:
	void runOneClockCycle(); // enough said
	int instrId;
	vector <vector <Instruction *> > sepInstructions;
	int prevPc;
	int nextPc;
};

#endif
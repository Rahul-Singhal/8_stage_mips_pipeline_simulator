#ifndef STAGE_H
#define STAGE_H

#include <list>

using namespace std;

class Instruction;

class Stage{

public:

	//Stage Number (eight stage)
	int number;

	// Address of the instruction being executed. -1 if no instruction
	list <Instruction> instructionQ;

	// whether stage if free or not
	bool isFree();

	// Constructors
	void setInstruction(int instructionAddress);
	
	Stage(int number);

	Stage(int number, int address);
};

#endif
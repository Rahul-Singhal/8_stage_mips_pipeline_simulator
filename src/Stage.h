#ifndef STAGE_H
#define STAGE_H

#include <list>

using namespace std;

class Instruction;

class Stage{

public:

	//Stage Number (eight stage)
	int number;

	// Id of the instruction being executed. -1 if no instruction
	int instructionId;

	// whether stage if free or not
	bool isFree();

	// Constructors
	void setInstruction(int instructionId);
	
	Stage(int number);

	Stage(int number, int Id);

	void setFree();
};

#endif
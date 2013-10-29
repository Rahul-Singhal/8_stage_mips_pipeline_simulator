#ifndef STAGE_H
#define STAGE_H

using namespace std;

class Stage{

public:

	//Stage Number (eight stage)
	int number;

	// Address of the instruction being executed. -1 if no instruction
	int instructionAddress;

	// whether stage if free or not
	bool isFree();

	// Constructors
	void setInstruction(int instructionAddress);
	
	Stage(int number);

	Stage(int number, int address);
};

#endif
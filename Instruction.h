#ifndef INSTR_H
#define INSTR_H


#include "Register.h"
#include "Stage.h"
#include <vector>


using namespace std;

class Instruction{
public:
	Instruction();
	static vector <Register> registers;
	static vector <Stage> stages;
	// eigth stage
	int stageNumber;
	int address;
};

#endif
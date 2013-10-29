#include "Instruction.h"
using namespace std;
//	Defining the initial set of Stages
vector<Stage> Instruction::stages(9, Stage(0));

// Defining the initial set of Registers
vector<Register> Instruction::registers(32, Register(0, 0));

Instruction::Instruction(){
	for(int i=0 ; i < 9 ; i++)
		stages[i].number = i;
	for (int i = 0; i < 32; ++i)
	{
		registers[i].id = i;
	}

}


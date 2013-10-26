#include "Instruction.h"

//	Defining the initial set of Stages
Instruction::stages.assign(8, Stage(0));
for(int i = 0 ; i <= 8 ; i++ )
	Instruction::stages[i].id = i;


// Defining the initial set of Registers
Instruction::registers.assign(32, Register(0, 0));
for(int i = 0 ; i < 32 ; i++)
	Instruction::registers[i].id = i;

Instruction::Instruction(){}


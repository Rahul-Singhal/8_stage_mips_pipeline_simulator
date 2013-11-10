#ifndef JAL_H
#define JAL_H

#include "Instruction.h"

class Jal: public Instruction{
private:
	// int rsIndex;
	// int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	// int a, b;
public:
	Jal(string label, int id);
	Jal(Jal &b);
	Jal(const Jal &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Jal * clone();
};

#endif
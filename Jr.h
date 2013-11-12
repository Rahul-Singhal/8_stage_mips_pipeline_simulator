#ifndef JR_H
#define JR_H

#include "Instruction.h"

class Jr: public Instruction{
private:
	int rsIndex;
	// int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	string label;
	// int a, b;
public:
	Jr(int rsIndex, int id);
	Jr(Jr &b);
	Jr(const Jr &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Jr * clone();
};

#endif
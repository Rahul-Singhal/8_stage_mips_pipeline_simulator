#ifndef B_H
#define B_H

#include "Instruction.h"

class B: public Instruction{
private:
	// int rsIndex;
	// int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	// int a, b;
public:
	B(string label, int id);
	B(B &b);
	B(const B &i);
	bool execute(int pc);
	void unstall(int instructionId);
	B * clone();
};

#endif
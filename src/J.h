#ifndef J_H
#define J_H

#include "Instruction.h"

class J: public Instruction{
private:
	// int rsIndex;
	// int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	// int a, b;
public:
	J(string label, int id);
	J(J &b);
	J(const J &i);
	bool execute(int pc);
	void unstall(int instructionId);
	J * clone();
};

#endif
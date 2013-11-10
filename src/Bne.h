#ifndef BNE_H
#define BNE_H

#include "Instruction.h"

class Bne: public Instruction{
private:
	int rsIndex;
	int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	int a, b;
public:
	Bne(int rsIndex, int rtIndex, string label, int id);
	Bne(Bne &b);
	Bne(const Bne &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Bne * clone();
};

#endif
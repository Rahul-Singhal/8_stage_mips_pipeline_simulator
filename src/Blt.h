#ifndef BLT_H
#define BLT_H

#include "Instruction.h"

class Blt: public Instruction{
private:
	int rsIndex;
	int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	int a, b;
public:
	Blt(int rsIndex, int rtIndex, int destPc, int id);
	Blt(Blt &b);
	Blt(const Blt &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Blt * clone();
};

#endif
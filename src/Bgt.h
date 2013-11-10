#ifndef BGT_H
#define BGT_H

#include "Instruction.h"

class Bgt: public Instruction{
private:
	int rsIndex;
	int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	int a, b;
public:
	Bgt(int rsIndex, int rtIndex, int destPc, int id);
	Bgt(Bgt &b);
	Bgt(const Bgt &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Bgt * clone();
};

#endif
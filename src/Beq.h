#ifndef BEQ_H
#define BEQ_H

#include "Instruction.h"

class Beq: public Instruction{
private:
	int rsIndex;
	int rtIndex;
	// I assume the following variable will hold the address to the next instruction
	// if the branch is taken
	int destPc;
	int a, b;
	string label;
public:
	Beq(int rsIndex, int rtIndex, string label, int id);
	Beq(Beq &b);
	Beq(const Beq &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Beq * clone();
};

#endif
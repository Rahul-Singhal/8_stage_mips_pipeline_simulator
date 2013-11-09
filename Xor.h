#ifndef XOR_H
#define XOR_H

#include "Instruction.h"

class Xor: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Xor(int rdIndex, int rsIndex, int rtIndex, int id);
	bool execute(int pc);
	void unstall();
};

#endif
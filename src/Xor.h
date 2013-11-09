#ifndef XXor_H
#define XXor_H

#include "Instruction.h"

class Xor: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Xor(int rdIndex, int rsIndex, int rtIndex, int id);
	Xor(Xor &a);
	Xor(const Xor &i);
	Xor * clone();
	bool execute(int pc);
	void unstall();
};

#endif
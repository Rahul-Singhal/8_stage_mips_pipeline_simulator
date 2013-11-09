#ifndef SRLV_H
#define SRLV_H

#include "Instruction.h"

class Srlv: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Srlv(int rdIndex, int rsIndex, int rtIndex, int id);
	Srlv(Srlv &a);
	Srlv(const Srlv &i);
	Srlv * clone();
	bool execute(int pc);
	void unstall();
};

#endif
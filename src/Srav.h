#ifndef SRAV_H
#define SRAV_H

#include "Instruction.h"

class Srav: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Srav(int rdIndex, int rsIndex, int rtIndex, int id);
	Srav(Srav &a);
	Srav(const Srav &i);
	Srav * clone();
	bool execute(int pc);
	void unstall();
};

#endif
#ifndef SLLV_H
#define SLLV_H

#include "Instruction.h"

class Sllv: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Sllv(int rdIndex, int rsIndex, int rtIndex, int id);
	Sllv(Sllv &a);
	Sllv(const Sllv &i);
	Sllv * clone();
	bool execute(int pc);
	void unstall();
};

#endif
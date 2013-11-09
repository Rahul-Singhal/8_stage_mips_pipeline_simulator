#ifndef OR_H
#define OR_H

#include "Instruction.h"

class Or: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Or(int rdIndex, int rsIndex, int rtIndex, int id);
	Or(Or &a);
	Or(const Or &i);
	Or * clone();
	bool execute(int pc);
	void unstall();
};

#endif
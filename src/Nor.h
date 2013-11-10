#ifndef NOR_H
#define NOR_H

#include "Instruction.h"

class Nor: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Nor(int rdIndex, int rsIndex, int rtIndex, int id);
	Nor(Nor &a);
	Nor(const Nor &i);
	Nor * clone();
	bool execute(int pc);
	void unstall();
};

#endif
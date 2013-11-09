#ifndef AND_H
#define AND_H

#include "Instruction.h"

class And: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	And(int rdIndex, int rsIndex, int rtIndex, int id);
	And(And &a);
	And(const And &i);
	And * clone();
	bool execute(int pc);
	void unstall();
};

#endif
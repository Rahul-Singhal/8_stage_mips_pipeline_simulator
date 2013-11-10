#ifndef SUB_H
#define SUB_H

#include "Instruction.h"

class Sub: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Sub(int rdIndex, int rsIndex, int rtIndex, int id);
	Sub(Sub &a);
	Sub(const Sub &i);
	Sub * clone();
	bool execute(int pc);
	void unstall();
};

#endif
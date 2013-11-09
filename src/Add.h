#ifndef ADD_H
#define ADD_H

#include "Instruction.h"

class Add: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int rtIndex;
	int sum;
	int a, b;
	Add(int rdIndex, int rsIndex, int rtIndex, int id);
	Add(Add &a);
	Add(const Add &i);
	Add * clone();
	bool execute(int pc);
	void unstall();
};

#endif
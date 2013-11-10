#ifndef NOT_H
#define NOT_H

#include "Instruction.h"

class Not: public Instruction{
public:
	int rdIndex;
	int rsIndex;
	int a, b;
	Not(int rdIndex, int rsIndex, int id);
	Not(Not &a);
	Not(const Not &i);
	Not * clone();
	bool execute(int pc);
	void unstall();
};

#endif
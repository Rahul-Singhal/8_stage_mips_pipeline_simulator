#ifndef LI_H
#define LI_H

/*
	Highlights
	-> MEM to ID forwarding happens at MEM3
	-> Memory is another global structure which holds valus at respective indeces
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "Instruction.h"

class Li: public Instruction{
private:
	int rdIndex;
	int immediate;
public:
	Li(int rdIndex, int immediate, int id);
	Li(const Li &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Li * clone();
	Li(Li &l);
};

#endif
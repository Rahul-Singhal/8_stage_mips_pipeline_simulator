#ifndef SW_H
#define SW_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Instruction.h"

class Sw: public Instruction{
	int rsIndex;  // Destination
	int rtIndex;  // Source
	int signExtImm;
	int a, b, sum;
	Sw(int rsIndex, int rtIndex, int signExtImm, int id);
	bool execute(int pc);
	void unstall();
};

#endif
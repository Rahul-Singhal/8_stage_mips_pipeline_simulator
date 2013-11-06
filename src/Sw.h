#ifndef SW_H
#define SW_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Instruction.h"
#include <string>

class Sw: public Instruction{
private:
	int rsIndex;  // Destination
	int rtIndex;  // Source
	int signExtImm;
	int a, b, sum;
public:
	Sw(int rsIndex, int rtIndex, int signExtImm, int id);
	Sw(int rsIndex, string address, int signExtImm, int id);
	bool execute(int pc);
	void unstall();
};

#endif
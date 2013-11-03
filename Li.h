#ifndef LI_H
#define LI_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Instruction.h"

using namespace std;

class Li: public Instruction{
	int rdIndex;
	int immediate;
	Li(int rdIndex, int immediate, int id);
	bool execute(int pc);
	void unstall();
};

#endif
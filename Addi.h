#ifndef ADDI_H
#define ADDI_H

#include "Instruction.h"

class Addi: public Instruction{
public:
	int rtIndex;
	int rsIndex;
	int immediate;
	int sum ;
	int a, b;

	Addi(int rtIndex, int rsIndex, int immediate);
	bool execute();
};

#endif
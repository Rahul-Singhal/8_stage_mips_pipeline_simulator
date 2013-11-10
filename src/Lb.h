#ifndef LB_H
#define LB_H

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

class Lb: public Instruction{
private:
	int rsIndex;  // Source
	int rtIndex;  // Destination
	int signExtImm;
	int a, b, sum;
	string address;
	bool label;
public:
	Lb(int rtIndex, int rsIndex, int signExtImm, int id);
	Lb(int rtIndex, string address, int signExtImm, int id);
	Lb(const Lb &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Lb * clone();
	Lb(Lb &l);
};

#endif
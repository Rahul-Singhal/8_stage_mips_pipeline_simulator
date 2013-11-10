#ifndef LA_H
#define LA_H

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

class La: public Instruction{
private:
	int rdIndex;
	// int rsIndex;  // Source
	// int rtIndex;  // Destination
	string address;
	// int a, b, sum;
public:
	La(int rdIndex, string address, int id);
	// La(int rsIndex, string address, int signExtImm, int id);
	La(const La &i);
	bool execute(int pc);
	void unstall(int instructionId);
	La * clone();
	La(La &l);
};

#endif
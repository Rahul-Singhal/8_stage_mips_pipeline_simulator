#ifndef SB_H
#define SB_H

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

class Sb: public Instruction{
private:
	int rsIndex;  // Source
	int rtIndex;  // Destination
	int signExtImm;
	int a, b, sum;
	bool label;
	string address;
public:
	Sb(int rtIndex, int rsIndex, int signExtImm, int id);
	Sb(int rtIndex, string address, int signExtImm, int id);
	Sb(const Sb &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Sb * clone();
	Sb(Sb &l);
};

#endif
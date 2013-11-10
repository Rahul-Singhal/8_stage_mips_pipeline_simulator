#ifndef SW_H
#define SW_H

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

class Sw: public Instruction{
private:
	int rsIndex;  // Source
	int rtIndex;  // Destination
	int signExtImm;
	int a, b, sum;
	bool label;
	string address;
public:
	Sw(int rtIndex, int rsIndex, int signExtImm, int id);
	Sw(int rtIndex, string address, int signExtImm, int id);
	Sw(const Sw &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Sw * clone();
	Sw(Sw &l);
};

#endif
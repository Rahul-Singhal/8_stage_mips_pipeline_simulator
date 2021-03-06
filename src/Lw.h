#ifndef LW_H
#define LW_H

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

class Lw: public Instruction{
private:
	int rsIndex;  // Source
	int rtIndex;  // Destination
	int signExtImm;
	string address;
	int a, b, sum;
	bool label;
public:
	Lw(int rtIndex, int rsIndex, int signExtImm, int id);
	Lw(int rtIndex, string address, int signExtImm, int id);
	Lw(const Lw &i);
	bool execute(int pc);
	void unstall(int instructionId);
	Lw * clone();
	Lw(Lw &l);
};

#endif
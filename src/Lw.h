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
	int a, b, sum;
public:
	Lw(int rsIndex, int rtIndex, int signExtImm, int id);
	Lw(int rsIndex, string address, int signExtImm, int id);
	bool execute(int pc);
	void unstall();

};

#endif
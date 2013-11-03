#ifndef REG_H
#define REG_H

#include <utility>
#include <iostream>

//Status index
/*
	0: 	ready to be read ( no forwarding, value stored in register )
	1:	waiting to be written
	2:	forwarded value available
*/
using namespace std;

class Register{
public:
	int id;

	int value; // stores the value in register
	bool valid; // true if the value written is valid
	int instructionId; // if value is not valid, it stores which instruction has stalled the register, 
										 //else stores which instruction wrote into the register last
	int instructionStage; // which instruction stage wrote into the register, if not WB (stage 8) then we can get insights about forwarding

	// Constructor, sets the initial value of register with id = id as value.
	Register(int id, int value);

	//  Should be called at every stage of the instruction which needs to writes to that particular instruction
	void stallRegister(int instructionId);

	// 	called to write back at the WB stage, returns true if value could be written, else false
	bool write(int value, int instructionId, int instructionStage);

	//	returns a pair <status, value>
	//pair <bool, int> read();

};

#endif
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
	
	// Constructor, sets the initial value of register with id = id as value.
	Register(int id, int value);

	//  Should be called at every stage of the instruction which needs to writes to that particular instruction
	void stallRegister();

	//	this function is called when the value of a particular register is forwarded from the EX/MEM latch to 
	// 	ID/EX latch
	void setForwardedValue(int value);

	// 	called to write back at the WB stage, returns true if value could be written, else false
	bool writeBack(int value);

	//	returns a pair <status, value>
	pair <int, int> read();

private:
	int value;
	int status;

};

#endif
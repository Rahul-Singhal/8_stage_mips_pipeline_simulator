#include "Addi.h"

Addi::Addi(int rtIndex, int rsIndex, int immediate){
	this->rtIndex = rtIndex;
	this->rsIndex = rsIndex;
	this->immediate = immediate;
}


// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions.
bool Addi::execute(){
	// setting the status of register which is to be written as 1 for 1<=stageNumber<5 (if any, assuming no forwarding)
	switch(stageNumber){
		case 1:
		{
			if(stages[0].isFree()){
				registers[rtIndex].stallRegister();
				stages[0].instructionAddress = address;
				return true;
			}
			return false;
		}
		case 2:
		{
			registers[rdIndex].stallRegister();
			// Assuming no forwarding and that the registers to be read must be free as of now.
			if(stages[1].isFree()){
				pair <int, int> p = registers[rsIndex].read();
				if(p.first==0){
					a = p.second;
					p = registers[rtIndex].read();
					if(p.first == 0){
						b = p.second;
						return true;
					}
					else
						return false;
				}
				else
					return false;
			}
			else
				return false;
		}
		case 3:
		{
			registers[rdIndex].stallRegister();
			if(stages[2].isFree()){
				sum = a+b;
				return true;
			}
			return false;
		}
		case 4:
		{
			registers[rdIndex].stallRegister();
			if(stages[3].isFree())
				return true;
			return false;
		}
		case 5:
		{
			if(stages[4].isFree()){
				registers[rtIndex].writeBack(sum);
			}
		}
	}
}
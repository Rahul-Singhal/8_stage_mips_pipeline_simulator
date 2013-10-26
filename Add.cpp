#include "Add.h"

Add::Add(int rdIndex, int rsIndex, int rtIndex){
	this->rdIndex = rdIndex;
	this->rsIndex = rsIndex;
	this->rtIndex = rtIndex;
	this->address = address;
}


// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 
bool Add::execute(){
	// setting the status of register which is to be written as 1 for 1<=stageNumber<5 (if any, assuming no forwarding)
	switch(stageNumber){
		case 1: 
		{
			// IF 1 Stage
			if(stages[stageNumber].isFree()){
				//registers[rdIndex].stallRegister();
				stages[stageNumber-1].setInstruction(-1);
				stageNumber++;
				stages[stageNumber].setInstruction(address);
				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 2:
		{
			// IF 2 Stage
			if(stages[stageNumber].isFree()){
				//registers[rdIndex].stallRegister();

				stageNumber++;
				stages[stageNumber].setInstruction(address);
				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 3:
		{
			// ID Stage
			// Assuming no forwarding and that the registers to be read must be free as of now.
			if(stages[stageNumber].isFree()){
				registers[rdIndex].stallRegister(); // TODO: should this be outside or inside the if statement??

				pair <int, int> p = registers[rsIndex].read();
				pair <int, int> q = registers[rtIndex].read();
				if(p.first==0 && q.first==0) {
					a = p.second;
					b = q.second;
					stageNumber++;
					stages[stageNumber].setInstruction(address);

					return true;
				}
				else
					return false;
			}
			else{
				stages[stageNumber-1].setInstruction(address);
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			//registers[rdIndex].stallRegister();
			if(stages[stageNumber].isFree()){
				sum = a+b;
				registers[rdIndex].setForwardedValue(sum);
				stageNumber++;
				stages[stageNumber].setInstruction(address);
				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 5:
		{
			// MEM 1 Stage
			//registers[rdIndex].stallRegister();
			if(stages[stageNumber].isFree()){
				stageNumber++;
				stages[stageNumber].setInstruction(address);

				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 6:
		{
			// MEM 2 Stage
			if(stages[stageNumber].isFree()){
				stageNumber++;
				stages[stageNumber].setInstruction(address);

				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 7:
		{
			// MEM 3 Stage
			if(stages[stageNumber].isFree()){
				stageNumber++;
				stages[stageNumber].setInstruction(address);

				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
		case 8:
		{
			// WB Stage
			if(stages[stageNumber].isFree()){
				registers[rtIndex].writeBack(sum);
				stageNumber=-1;
				// Instruction completed, so stage number is now invalid.

				return true;
			}
			stages[stageNumber-1].setInstruction(address);
			return false;
		}
	}
}
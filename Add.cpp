#include "Add.h"

Add::Add(int rdIndex, int rsIndex, int rtIndex){
	this->rdIndex = rdIndex;
	this->rsIndex = rsIndex;
	this->rtIndex = rtIndex;
	this->id = id;
}


// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

bool Add::execute(){
	// setting the status of register which is to be written as 1 for 1<=stageToExecute<5 (if any, assuming no forwarding)
	switch(stageToExecute){
		case 1: 
		{
			// IF 1 Stage
			if(stages[stageToExecute].isFree()){
				//registers[rdIndex].stallRegister();
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				stalled = false;
				display = "IF1";
				return true;
			}
			else{
				stages.presentStage.setInstruction(id);
				stalled = true;
				display = "Waiting for IF1 to be free!";
				return false;
			}
		}
		case 2:
		{
			// IF 2 Stage
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				stalled = false;
				display = "IF2";
				return true;
			}
			else {
				stages.presentStage.setInstruction(id);
				stalled = true;
				display = "Waiting for IF2 to be free!";
				return false;
			}
		}
		case 3:
		{
			// ID Stage
			// Assuming no forwarding and that the registers to be read must be free as of now.
			if(stages[stageToExecute].isFree()){

				pair <int, int> p = registers[rsIndex].read();
				pair <int, int> q = registers[rtIndex].read();
				if(p.first==0 && q.first==0) {
					registers[rdIndex].stallRegister(); // TODO: should this be outside or inside the if statement??
					a = p.second;
					b = q.second;
					stageToExecute++;
					stages[stageToExecute].setInstruction(id);

					return true;
				}
				else{
					stages[stageToExecute-1].setInstruction(id);

					return false;
				}
			}
			else{
				stages[stageToExecute-1].setInstruction(id);
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			//registers[rdIndex].stallRegister();
			if(stages[stageToExecute].isFree()){
				sum = a+b;
				registers[rdIndex].setForwardedValue(sum);
				stageToExecute++;
				stages[stageToExecute].setInstruction(id);
				return true;
			}
			stages[stageToExecute-1].setInstruction(id);
			return false;
		}
		case 5:
		{
			// MEM 1 Stage
			//registers[rdIndex].stallRegister();
			if(stages[stageToExecute].isFree()){
				stageToExecute++;
				stages[stageToExecute].setInstruction(id);

				return true;
			}
			stages[stageToExecute-1].setInstruction(id);
			return false;
		}
		case 6:
		{
			// MEM 2 Stage
			if(stages[stageToExecute].isFree()){
				stageToExecute++;
				stages[stageToExecute].setInstruction(id);

				return true;
			}
			stages[stageToExecute-1].setInstruction(id);
			return false;
		}
		case 7:
		{
			// MEM 3 Stage
			if(stages[stageToExecute].isFree()){
				stageToExecute++;
				stages[stageToExecute].setInstruction(id);

				return true;
			}
			stages[stageToExecute-1].setInstruction(id);
			return false;
		}
		case 8:
		{
			// WB Stage
			if(stages[stageToExecute].isFree()){
				registers[rtIndex].writeBack(sum);
				stageToExecute=-1;
				// Instruction completed, so stage number is now invalid.

				return true;
			}
			stages[stageToExecute-1].setInstruction(id);
			return false;
		}
	}
}
#include "Lw.h"

Lw::Lw(int rsIndex, int rtIndex, int signExtImm, int id){
	this->rsIndex = rsIndex;
	this->rtIndex = rtIndex;
	this->signExtImm = signExtImm;
	this->id = id;
}

void Lw::unstall(){
	if(!registers[rtIndex].valid && registers[rtIndex].instructionId==id)
		registers[rtIndex].unstall();
}


// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

/*	lw $t0, 4($t1)
	In case of Lw forwarding will be from MEM3 to ID as total MEM access is required*/

bool Lw::execute(int pc){
	// //cout<<"LW"<<endl;
	// Default Values:
	forwarded = false;
	stalled = false;


	switch(stageToExecute){
		case 1: 
		{
			// IF 1 Stage
			if(stages[stageToExecute].isFree()){
				//registers[rdIndex].stallRegister(id)();
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				stalled = false;
				display = "IF1";
				//cout << "if1 -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting for IF1 to be free!";
				//cout << "if1 - wait -->" ;
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
				//cout << "if2 -->" ;
				return true;
			}
			else {
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting for IF2 to be free!";
				//cout << "if2 - wait -->" ;
				return false;
			}
		}
		case 3:
		{
			// ID Stage
			// Assuming no forwarding and that the register to be read must be free as of now.
			if(stages[stageToExecute].isFree()){
				if (forwardingEnabled) {

						// either values are forwarded, or normally stored
					if (!registers[rsIndex].valid){
							// forwarded value
						stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rsIndex;
						stallingInstructionId = registers[rsIndex].instructionId;
						//cout << "rs register not readable -->";

						return false;
					}
					else if (  registers[rsIndex].instructionStage==10 ) {
							// this is the most normal case, when all values are simply avaiable not forwarded.
						registers[rtIndex].stallRegister(id); 
						a = registers[rsIndex].value;
						b = signExtImm;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "id completed -->";

						return true;
					}
						// ASSUMING ONLY ONE FORWARDED VALUE
					else if (registers[rsIndex].instructionStage!=10){
						registers[rtIndex].stallRegister(id); 
						forwarded = true;
						forwardedFromInstructionId = registers[rsIndex].instructionId;
						forwardedFromInstructionStage = registers[rsIndex].instructionStage;
						a = registers[rsIndex].value;
						b = signExtImm;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "rs value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" ;

						return true;
					}
				}
				else {
					// forwarding disabled
					
						// either values are forwarded, or normally stored
					if (!registers[rsIndex].valid || registers[rsIndex].instructionStage!=10){
							// forwarded value
						stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rsIndex;
						stallingInstructionId = registers[rsIndex].instructionId;
						//cout << "ID stalls due to rs -->";
						return false;
					}
					else {
							// this is the most normal case, when all values are simply avaiable not forwarded.
						registers[rtIndex].stallRegister(id); 
						a = registers[rsIndex].value;
						b = signExtImm;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "no stall ID -->" ;
						return true;
					}
				}	
			}
			else {
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "ID not free -->" ;
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			registers[rtIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				sum = a+b;
				// registers[rdIndex].write(sum,id,stageToExecute); // TODO : Will it ever return false?
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				/*Stage to execute will be MEM1 which is stage 7*/
          		stageToExecute+=3;
				//cout << "EX stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "EX stage not free -->";

				return false;
			}
		}
		case 7:
		{
			// MEM 1 Stage
			registers[rtIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM1 stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM1 stage not free -->";

				return false;
			}
		}
		case 8:
		{
			// MEM 2 Stage
			registers[rtIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM2 stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM2 stage not free -->";

				return false;
			}
		}
		case 9:
		{
			// MEM 3 Stage
			/*If register is not writable, i am stalling the register*/
			registers[rtIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				if (registers[rtIndex].write(memory[sum],id,stageToExecute)){
					stages[presentStage].setFree();
					presentStage = stageToExecute;
					stages[presentStage].setInstruction(id);
					stageToExecute++;
					//cout << "MEM3 completed -->";

						// Instruction completed, so stage number is now invalid.
					return true;
				}
				else {
					stalled = true;
					stages[presentStage].setInstruction(id);
					stallingRegister = rtIndex;
					stallingInstructionId = registers[rtIndex].instructionId;
					//cout << "Register not writable -->";

					return false;
				}
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM3 stage not free -->";

				return false;

			}
		}
		case 10:
		{
			// WB Stage
			if(stages[stageToExecute].isFree()){
				if (registers[rtIndex].write(sum,id,stageToExecute)){
					stages[presentStage].setFree();
					presentStage = stageToExecute;
					stages[presentStage].setInstruction(id);
					stageToExecute=-1;
					//cout << "WB completed -->";

						// Instruction completed, so stage number is now invalid.
					return true;
				}
				else {
					stalled = true;
					stages[presentStage].setInstruction(id);
					stallingRegister = rtIndex;
					stallingInstructionId = registers[rtIndex].instructionId;
					//cout << "Register not writable -->";

					return false;
				}
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "WB not free ->";

				return false;
			}
		}
	}
}
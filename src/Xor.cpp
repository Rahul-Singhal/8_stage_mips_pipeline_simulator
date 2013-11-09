#include "Xor.h"

Xor::Xor(int rdIndex, int rsIndex, int rtIndex, int id){
	this->rdIndex = rdIndex;
	this->rsIndex = rsIndex;
	this->rtIndex = rtIndex;
	this->id = id;
}

Xor* Xor::clone(){
	return new Xor (*this);
}

Xor::Xor(const Xor &i){
	this->stageToExecute = i.stageToExecute;
	this->presentStage = i.presentStage;
	this->stalled = i.stalled;
	this->stallingInstructionId = i.stallingInstructionId;
	this->stallingRegister = i.stallingRegister;
	this->fXorwarded =i.fXorwarded;
	this->fXorwardedFromInstructionId = i.fXorwardedFromInstructionId;
	this->fXorwardedFromInstructionStage = i.fXorwardedFromInstructionStage;
	this->display = i.display;
	this->id = i.id;
	this->rdIndex = i.rdIndex;
	this->rsIndex = i.rsIndex;
	this->rtIndex = i.rtIndex;
	this->sum = i.sum;
	this->a = i.a;
	this->b = i.b;
}


Xor::Xor(Xor &i){
	this->stageToExecute = i.stageToExecute;
	this->presentStage = i.presentStage;
	this->stalled = i.stalled;
	this->stallingInstructionId = i.stallingInstructionId;
	this->stallingRegister = i.stallingRegister;
	this->fXorwarded =i.fXorwarded;
	this->fXorwardedFromInstructionId = i.fXorwardedFromInstructionId;
	this->fXorwardedFromInstructionStage = i.fXorwardedFromInstructionStage;
	this->display = i.display;
	this->id = i.id;
	this->rdIndex = i.rdIndex;
	this->rsIndex = i.rsIndex;
	this->rtIndex = i.rtIndex;
	this->sum = i.sum;
	this->a = i.a;
	this->b = i.b;
}

void Xor::unstall(){
	registers[rdIndex].unstall(id);	
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may Xor may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free Xor because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

bool Xor::execute(int pc){
	// ////cout<<"###Xor####"<<endl;
	// ////cout<<"MAIN CALL HUWA"<<endl;
	// Default Values:
	fXorwarded = false;
	stalled = false;

	// setting the status of register which is to be written as 1 fXor 1<=stageToExecute<5 (if any, assuming no fXorwarding)
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
				//cout << "if1 -->" <<endl;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting fXor IF1 to be free!";
				//cout << "if1 - wait -->"<<endl ;
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
				//cout << "if2 -->" <<endl;
				return true;
			}
			else {
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting fXor IF2 to be free!";
				//cout << "if2 - wait -->" <<endl;
				return false;
			}
		}
		case 3:
		{
			// ID Stage
			// Assuming no fXorwarding Xor that the registers to be read must be free as of now.
			if(stages[stageToExecute].isFree()){
				/*if (fXorwardingEnabled) {*/
					stages[presentStage].setFree();
					presentStage = stageToExecute;
					stages[presentStage].setInstruction(id);
						// either values are fXorwarded, Xor nXormally stXored
					if (!registers[rsIndex].isValid()){
							// fXorwarded value
						// stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rsIndex;
						// stallingInstructionId = registers[rsIndex].instructionId;
						//cout << "rs register not readable -->"<<endl;

						return false;
					}
					else if (!registers[rtIndex].isValid()){
							// when rtIndex is not available without fXorwarding
						// stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rtIndex;
						// stallingInstructionId = registers[rtIndex].instructionId;    
						//cout << "rt register not readable -->"<<endl;

						return false;
					}

					else {
						registers[rdIndex].stallRegister(id); 
						a = registers[rsIndex].value;
						b = registers[rtIndex].value;
						// stages[presentStage].setFree();
						// presentStage = stageToExecute;
						// stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "id completed -->"<<endl;

						return true;
					}/*if (  registers[rsIndex].instructionStage==10 && registers[rtIndex].instructionStage==10) {
							// this is the most nXormal case, when all values are simply avaiable not fXorwarded.
						registers[rdIndex].stallRegister(id); 
						a = registers[rsIndex].value;
						b = registers[rtIndex].value;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "id completed -->"<<endl;

						return true;
					}
						// ASSUMING ONLY ONE FXorWARDED VALUE
					else if (registers[rsIndex].instructionStage!=10){
						registers[rdIndex].stallRegister(id); 
						fXorwarded = true;
						fXorwardedFromInstructionId = registers[rsIndex].instructionId;
						fXorwardedFromInstructionStage = registers[rsIndex].instructionStage;
						a = registers[rsIndex].value;
						b = registers[rtIndex].value;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "rs value fXorwarded from id = " << fXorwardedFromInstructionId << " stage = " << fXorwardedFromInstructionStage << "-->" <<endl;

						return true;
					}
					else if (registers[rtIndex].instructionStage!=10){
						registers[rdIndex].stallRegister(id); 
						fXorwarded = true;
						fXorwardedFromInstructionId = registers[rtIndex].instructionId;
						fXorwardedFromInstructionStage = registers[rtIndex].instructionStage;
						a = registers[rsIndex].value;
						b = registers[rtIndex].value;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "rt value fXorwarded from id = " << fXorwardedFromInstructionId << " stage = " << fXorwardedFromInstructionStage << "-->" <<endl;

						return true;
					}*/

				/*}
				else {
					// fXorwarding disabled
					
						// either values are fXorwarded, Xor nXormally stXored
					if (!registers[rsIndex].valid || registers[rsIndex].instructionStage!=10){
						////cout<<registers[rsIndex].valid<<endl;
						////cout<<registers[rsIndex].instructionStage<<endl;
							// fXorwarded value
						stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rsIndex;
						stallingInstructionId = registers[rsIndex].instructionId;
						//cout << "Xor ID stalls due to rs -->"<<endl;
						return false;
					}
					else if (!registers[rtIndex].valid || registers[rtIndex].instructionStage!=10){
							// when rtIndex is not available without fXorwarding
						stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rtIndex;
						stallingInstructionId = registers[rtIndex].instructionId;
						//cout << "ID stalls due to rt -->"<<endl; 
						return false;
					}
					else {
							// this is the most nXormal case, when all values are simply avaiable not fXorwarded.
						registers[rdIndex].stallRegister(id); 
						a = registers[rsIndex].value;
						b = registers[rtIndex].value;
						stages[presentStage].setFree();
						presentStage = stageToExecute;
						stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						//cout << "no stall ID -->" <<endl;
						return true;
					}
				}*/	
			}
			else {
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "ID not free -->"<<endl ;
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				sum = a^b;
				if(fXorwardingEnabled)
					registers[rdIndex].unstallRegister(sum, id); // TODO : Will it ever return false?
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				/*Stage to execute will be MEM1 which is stage 7*/
				stageToExecute+=3;
				//cout << "EX stage done -->" <<endl;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "EX stage not free -->"<<endl;

				return false;
			}
		}
		case 7:
		{
			// MEM 1 Stage
			// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM1 stage done -->" <<endl;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM1 stage not free -->"<<endl;

				return false;
			}
		}
		case 8:
		{
			// MEM 2 Stage
			// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM2 stage done -->" <<endl;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM2 stage not free -->"<<endl;

				return false;
			}
		}
		case 9:
		{
			// MEM 3 Stage
			// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM3 stage done -->" <<endl;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "MEM3 stage not free -->"<<endl;

				return false;

			}
		}
		case 10:
		{
			// WB Stage
			// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				if(!fXorwardingEnabled)
					registers[rdIndex].unstallRegister(sum, id); // TODO : Will it ever return false?
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute=-1;
				//cout << "WB completed -->"<<endl;

					// Instruction completed, so stage number is now invalid.
				return true;
				/*if (registers[rdIndex].write(sum,id,stageToExecute)){
					stages[presentStage].setFree();
					presentStage = stageToExecute;
					stages[presentStage].setInstruction(id);
					stageToExecute=-1;
					//cout << "WB completed -->"<<endl;

						// Instruction completed, so stage number is now invalid.
					return true;
				}
				else {
					stalled = true;
					stages[presentStage].setInstruction(id);
					stallingRegister = rdIndex;
					stallingInstructionId = registers[rdIndex].instructionId;
					//cout << "Register not writable -->"<<endl;
					return false;
				}*/
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				//cout << "WB not free ->"<<endl;

				return false;
			}
		}
	}
	return false;
}
#include "Jal.h"

Jal::Jal(string label, int id){
	// this->rsIndex = rsIndex;
	// this->rtIndex = rtIndex;
	this->destPc = labelMap[label];
	this->id = id;
}

Jal::Jal(const Jal &i){
	this->stageToExecute = i.stageToExecute;
	this->presentStage = i.presentStage;
	this->stalled = i.stalled;
	this->stallingInstructionId = i.stallingInstructionId;
	this->stallingRegister = i.stallingRegister;
	this->forwarded =i.forwarded;
	this->forwardedFromInstructionId = i.forwardedFromInstructionId;
	this->forwardedFromInstructionStage = i.forwardedFromInstructionStage;
	this->display = i.display;
	this->id = i.id;
	// this->rtIndex = i.rtIndex;
	// this->rsIndex = i.rsIndex;
	this->destPc = i.destPc;
	// this->a = i.a;
	// this->b = i.b;
}

Jal::Jal(Jal &i){
	this->stageToExecute = i.stageToExecute;
	this->presentStage = i.presentStage;
	this->stalled = i.stalled;
	this->stallingInstructionId = i.stallingInstructionId;
	this->stallingRegister = i.stallingRegister;
	this->forwarded =i.forwarded;
	this->forwardedFromInstructionId = i.forwardedFromInstructionId;
	this->forwardedFromInstructionStage = i.forwardedFromInstructionStage;
	this->display = i.display;
	this->id = i.id;
	// this->rtIndex = gtpooniwala@gmail.com i.rtIndex;
	// this->rsIndex = i.rsIndex;
	this->destPc = i.destPc;
	// this->a = i.a;
	// this->b = i.b;
}

void Jal::unstall(int instructionId){
	registers[31].unstall(instructionId);
 	return;
}

Jal * Jal::clone(){
	return new Jal(*this);
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

/*
	the following execute will modify the program counter which is passed as parameter
	in case the branch is taken. This change in branch will be detected in the program
	and the the subsequent pipeline instructions will be flushed 

	The functionality of calculating the branch predicate in ID itself is also provided
	This is governed by a global bool variable "fastJalranching"
*/

bool Jal::execute(int pc){
	int prevPc = programCounter;
	// ////cout<<"Jal"<<endl;
	forwarded = false;
	stalled = false;

	switch(stageToExecute){
		case 1: 
		{
			// IF 1 Stage
			if(stages[stageToExecute].isFree()){
				//registers[rdIndex].stallRegister(id)();
				stages[presentStage].setFree(); /*Set stage 0 free so that next instruction come*/
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				stalled = false;
				//display = "IF1";
				////cout << "if1 -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting for IF1 to be free!";
				////cout << "if1 - wait -->" ;
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
				//display = "IF2";
				////cout << "if2 -->" ;
				return true;
			}
			else {
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting for IF2 to be free!";
				////cout << "if2 - wait -->" ;
				return false;
			}
		}
		case 3:
		{
			// ID Stage
			// Assuming no forwarding and that the registers to be read must be free as of now.

			if(stages[stageToExecute].isFree()){
					/*if (forwardingEnabled) {*/

					stages[presentStage].setFree();
					presentStage = stageToExecute;
					stages[presentStage].setInstruction(id);
						// either values are forwarded, or normally stored
					/*if (!registers[rsIndex].isValid()){
							// forwarded value
						// stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rsIndex;
						// stallingInstructionId = registers[rsIndex].instructionId;
						////cout << "rs register not readable -->";

						return false;
					}
					else if (!registers[rtIndex].isValid()){
							// when rtIndex is not available without forwarding
						// stages[presentStage].setInstruction(id);
						stalled = true;
						stallingRegister = rtIndex;
						// stallingInstructionId = registers[rtIndex].instructionId;    
						////cout << "rt register not readable -->";

						return false;
					}
					else{*/
						registers[31].stallRegister(id); 
						// a = registers[rsIndex].value;
						// b = registers[rtIndex].value;
						// stages[presentStage].setFree();
						// presentStage = stageToExecute;
						// stages[presentStage].setInstruction(id);
						stageToExecute++;
						stalled = false;
						// destPc = registers[rsIndex].value;
						if(fastBranching){
							// cout<<a<<"::::::::::::::::::"<<b<<endl;
							if(true){
								programCounter = destPc-1;
							}
						}
						////cout << "id completed -->";

						return true;
					// }
				// 	else if (  registers[rsIndex].instructionStage==10 && registers[rtIndex].instructionStage==10) {
				// 			// this is the most normal case, when all values are simply avaiable not forwarded.
				// 		/*Branch Instruction, no stalling of rdIndex as there is none*/
				// 		// registers[rdIndex].stallRegister(id); 
				// 		a = registers[rsIndex].value;
				// 		b = registers[rtIndex].value;
				// 		stages[presentStage].setFree();
				// 		presentStage = stageToExecute;
				// 		stages[presentStage].setInstruction(id);
				// 		stageToExecute++;
				// 		stalled = false;
				// 		if(fastBranching){
				// 			if(a==b)
				// 				pc = destPc-1;
				// 		}
				// 		////cout << "id completed -->";

				// 		return true;
				// 	}
				// 		// ASSUMING ONLY ONE FORWARDED VALUE
				// 	else if (registers[rsIndex].instructionStage!=10){
				// 		/*Branch Instruction, no stalling of rdIndex as there is none*/
				// 		// registers[rdIndex].stallRegister(id);
				// 		forwarded = true;
				// 		forwardedFromInstructionId = registers[rsIndex].instructionId;
				// 		forwardedFromInstructionStage = registers[rsIndex].instructionStage;
				// 		a = registers[rsIndex].value;
				// 		b = registers[rtIndex].value;
				// 		stages[presentStage].setFree();
				// 		presentStage = stageToExecute;
				// 		stages[presentStage].setInstruction(id);
				// 		stageToExecute++;
				// 		stalled = false;
				// 		if(fastBranching){
				// 			if(a==b)
				// 				pc = destPc-1;
				// 		}
				// 		////cout << "rs value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" ;

				// 		return true;
				// 	}
				// 	else if (registers[rtIndex].instructionStage!=10){
				// 		/*Branch Instruction, no stalling of rdIndex as there is none*/
				// 		// registers[rdIndex].stallRegister(id);
				// 		forwarded = true;
				// 		forwardedFromInstructionId = registers[rtIndex].instructionId;
				// 		forwardedFromInstructionStage = registers[rtIndex].instructionStage;
				// 		a = registers[rsIndex].value;
				// 		b = registers[rtIndex].value;
				// 		stages[presentStage].setFree();
				// 		presentStage = stageToExecute;
				// 		stages[presentStage].setInstruction(id);
				// 		stageToExecute++;
				// 		stalled = false;
				// 		if(fastBranching){
				// 			if(a==b)
				// 				pc = destPc-1;
				// 		}
				// 		////cout << "rt value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" ;

				// 		return true;
				// 	}

				// }
				// else {
				// 	// forwarding disabled
					
				// 		// either values are forwarded, or normally stored
				// 	if (!registers[rsIndex].valid || registers[rsIndex].instructionStage!=10){
				// 			// forwarded value
				// 		stages[presentStage].setInstruction(id);
				// 		stalled = true;
				// 		stallingRegister = rsIndex;
				// 		stallingInstructionId = registers[rsIndex].instructionId;
				// 		////cout << "ID stalls due to rs -->";
				// 		return false;
				// 	}
				// 	else if (!registers[rtIndex].valid || registers[rtIndex].instructionStage!=10){
				// 			// when rtIndex is not available without forwarding
				// 		stages[presentStage].setInstruction(id);
				// 		stalled = true;
				// 		stallingRegister = rtIndex;
				// 		stallingInstructionId = registers[rtIndex].instructionId;
				// 		////cout << "ID stalls due to rt -->"; 
				// 		return false;
				// 	}
				// 	else {
				// 			// this is the most normal case, when all values are simply avaiable not forwarded.
				// 		/*Branch Instruction, no stalling of rdIndex as there is none*/
				// 		// registers[rdIndex].stallRegister(id);
				// 		a = registers[rsIndex].value;
				// 		b = registers[rtIndex].value;
				// 		stages[presentStage].setFree();
				// 		presentStage = stageToExecute;
				// 		stages[presentStage].setInstruction(id);
				// 		stageToExecute++;
				// 		stalled = false;
				// 		if(fastBranching){
				// 			if(a==b)
				// 				pc = destPc-1;
				// 		}
				// 		////cout << "no stall ID -->" ;
				// 		return true;
				// 	}
				// }	
			}
			else {
				// cout<<"Yes its coming here"<<endl;
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "ID not free -->" ;
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			/*Branch Instruction, no stalling of rdIndex as there is none*/
						// registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				if(forwardingEnabled)
					registers[31].unstallRegister(prevPc+1, id); // TODO : Will it ever return false?
				if(!fastBranching){
					// cout<<a<<"::::::::::::::::::"<<b<<endl;
					if(true)
						programCounter = destPc-1;
				}
				/*No rdIndex to write*/
				// registers[rdIndex].write(sum,id,stageToExecute); // TODO : Will it ever return false?
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				/*Stage to execute will be MEM1 which is stage 7*/
          		stageToExecute+=3;
				////cout << "EX stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "EX stage not free -->";

				return false;
			}
		}
		case 7:
		{
			// MEM 1 Stage
			//registers[rdIndex].stallRegister(id)();
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				////cout << "MEM1 stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "MEM1 stage not free -->";

				return false;
			}
		}
		case 8:
		{
			// MEM 2 Stage
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				////cout << "MEM2 stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "MEM2 stage not free -->";

				return false;
			}
		}
		case 9:
		{
			// MEM 3 Stage
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				////cout << "MEM3 stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "MEM3 stage not free -->";

				return false;

			}
		}
		case 10:
		{
			// WB Stage Simple ! Nothing to write back
			if(stages[stageToExecute].isFree()){
				if(!forwardingEnabled)
					registers[31].unstallRegister(prevPc+1, id); // TODO : Will it ever return false?
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute=-1;
				////cout << "WB stage done -->" ;
				return true;
			}
			else{
				stages[presentStage].setInstruction(id);
				stallingInstructionId = stages[stageToExecute].instructionId;
				stalled = true;
				////cout << "WB stage not free -->";

				return false;

			}
		}
	}
	return false;
}
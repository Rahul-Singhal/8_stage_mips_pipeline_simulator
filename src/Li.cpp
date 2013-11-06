#include "Li.h"

Li::Li(int rdIndex, int immediate, int id){
	this->rdIndex = rdIndex;
	this->immediate = immediate;
	this->id = id;
}

void Li::unstall(){
	if(!registers[rdIndex].valid && registers[rdIndex].instructionId==id)
		registers[rdIndex].unstall();
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

/*In case of Li forwarding will be from EX to ID as no MEM access is required*/

bool Li::execute(int pc){
	// //cout<<"LI"<<endl;
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
			/*Almost nothing happens in this stage as no register is to be read*/
			if(stages[stageToExecute].isFree()){
				registers[rdIndex].stallRegister(id); 
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				stalled = false;
				display = "ID";
				//cout << "id -->" ;
				return true;
			}
			else {
				stages[presentStage].setInstruction(id);
				stalled = true;
				stallingInstructionId = stages[stageToExecute].instructionId;
				display = "Waiting for id to be free!";
				//cout << "id - wait -->" ;
				return false;
			}
		}
		case 4:
		{
			// EX Stage
			registers[rdIndex].stallRegister(id);
			if(stages[stageToExecute].isFree()){
				/*Forwarding done from ex to id*/
				registers[rdIndex].write(immediate,id,stageToExecute); // TODO : Will it ever return false?
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
			//registers[rdIndex].stallRegister(id)();
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
			if(stages[stageToExecute].isFree()){
				stages[presentStage].setFree();
				presentStage = stageToExecute;
				stages[presentStage].setInstruction(id);
				stageToExecute++;
				//cout << "MEM3 stage done -->" ;
				return true;
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
				if (registers[rdIndex].write(immediate,id,stageToExecute)){
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
					stallingRegister = rdIndex;
					stallingInstructionId = registers[rdIndex].instructionId;
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
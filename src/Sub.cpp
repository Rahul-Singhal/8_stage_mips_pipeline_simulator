#include "Sub.h"

Sub::Sub(int rdIndex, int rsIndex, int rtIndex, int id){
  this->rdIndex = rdIndex;
  this->rsIndex = rsIndex;
  this->rtIndex = rtIndex;
  this->id = id;
}

void Sub::unstall(){
  if(!registers[rdIndex].valid && registers[rdIndex].instructionId==id)
    registers[rdIndex].unstall();
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

bool Sub::execute(int pc){
  // ////cout<<"SUB"<<endl;
  // ////cout<<"MAIN CALL HUWA"<<endl;
  // Default Values:
  forwarded = false;
  stalled = false;

  // setting the status of register which is to be written as 1 for 1<=stageToExecute<5 (if any, assuming no forwarding)
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
        //cout << "sub if1 -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stalled = true;
        stallingInstructionId = stages[stageToExecute].instructionId;
        display = "Waiting for IF1 to be free!";
        //cout << "sub if1 - wait -->" <<endl;
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
        //cout << " sub if2 -->" <<endl;
        return true;
      }
      else {
        stages[presentStage].setInstruction(id);
        stalled = true;
        stallingInstructionId = stages[stageToExecute].instructionId;
        display = "Waiting for IF2 to be free!";
        //cout << "sub if2 - wait -->" <<endl;
        return false;
      }
    }
    case 3:
    {
      // ID Stage
      // Assuming no forwarding and that the registers to be read must be free as of now.
      if(stages[stageToExecute].isFree()){
        if (forwardingEnabled) {

            // either values are forwarded, or normally stored
          if (!registers[rsIndex].valid){
              // forwarded value
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rsIndex;
            stallingInstructionId = registers[rsIndex].instructionId;
            //cout << "sub id rs register not readable -->"<<endl;
            return false;
          }
          else if (!registers[rtIndex].valid){
              // when rtIndex is not available without forwarding
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rtIndex;
            stallingInstructionId = registers[rtIndex].instructionId;
            //cout << "sub id rt register not readable -->"<<endl;
            return false;
          }

          else if (  registers[rsIndex].instructionStage==10 && registers[rtIndex].instructionStage==10) {
            ////cout<<"CUMS"<<endl;
              // this is the most normal case, when all values are simply avaiable not forwarded.
            registers[rdIndex].stallRegister(id); 
            a = registers[rsIndex].value;
            b = registers[rtIndex].value;
            stages[presentStage].setFree();
            presentStage = stageToExecute;
            stages[presentStage].setInstruction(id);
            stageToExecute++;
            stalled = false;
            //cout << "sub id completed forwarded-->"<<endl;

            return true;
          }
            // ASSUMING ONLY ONE FORWARDED VALUE
          else if (registers[rsIndex].instructionStage!=10){
            registers[rdIndex].stallRegister(id); 
            forwarded = true;
            forwardedFromInstructionId = registers[rsIndex].instructionId;
            forwardedFromInstructionStage = registers[rsIndex].instructionStage;
            a = registers[rsIndex].value;
            b = registers[rtIndex].value;
            stages[presentStage].setFree();
            presentStage = stageToExecute;
            stages[presentStage].setInstruction(id);
            stageToExecute++;
            stalled = false;
            //cout << "rs value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" <<endl;
            return true;
          }
          else if (registers[rtIndex].instructionStage!=10){
            registers[rdIndex].stallRegister(id); 
            forwarded = true;
            forwardedFromInstructionId = registers[rtIndex].instructionId;
            forwardedFromInstructionStage = registers[rtIndex].instructionStage;
            a = registers[rsIndex].value;
            b = registers[rtIndex].value;
            stages[presentStage].setFree();
            presentStage = stageToExecute;
            stages[presentStage].setInstruction(id);
            stageToExecute++;
            stalled = false;
            //cout << "rt value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" <<endl;
            return true;
          }

        }
        else {
          // forwarding disabled

            // either values are forwarded, or normally stored
          if (!registers[rsIndex].valid || registers[rsIndex].instructionStage!=10){
            ////cout<<registers[rsIndex].instructionStage<<endl;
              // forwarded value
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rsIndex;
            stallingInstructionId = registers[rsIndex].instructionId;
            //cout << "sub ID stalls due to rs -->"<<endl;
            return false;
          }
          else if (!registers[rtIndex].valid || registers[rtIndex].instructionStage!=10){
              // when rtIndex is not available without forwarding
            /*//cout<<registers[rtIndex].valid<<endl;
            //cout<<registers[rtIndex].instructionStage<<endl;*/
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rtIndex;
            stallingInstructionId = registers[rtIndex].instructionId;
            //cout << "sub ID stalls due to rt -->"<<endl;
            return false;
          }
          else {
              // this is the most normal case, when all values are simply avaiable not forwarded.
            registers[rdIndex].stallRegister(id); 
            a = registers[rsIndex].value;
            b = registers[rtIndex].value;
            stages[presentStage].setFree();
            presentStage = stageToExecute;
            stages[presentStage].setInstruction(id);
            stageToExecute++;
            stalled = false;
            //cout << "sub no stall ID -->" <<endl;
            return true;
          }
        } 
      }
      else {
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "sub ID not free-->" <<endl;
        return false;
      }
    }
    case 4:
    {
      // EX Stage
      registers[rdIndex].stallRegister(id);
      if(stages[stageToExecute].isFree()){
        diff = a-b;
        registers[rdIndex].write(diff,id,stageToExecute); // TODO : Will it ever return false?
        stages[presentStage].setFree();
        presentStage = stageToExecute;
        stages[presentStage].setInstruction(id);
        /*Stage to execute will be MEM1 which is stage 7*/
        stageToExecute+=3;
        //cout << "sub EX stage done -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "sub EX stage not free -->"<<endl;
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
        //cout << "sub MEM1 done -->"<<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "sub MEM1 not free -->"<<endl;
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
        //cout << "sub MEM2 done -->"<<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "sub MEM2 not free -->"<<endl;
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
        //cout << "sub MEM3 done -->"<<endl;

        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "sub MEM3 not free -->"<<endl;
        return false;
      }
    }
    case 10:
    {
      // WB Stage
      if(stages[stageToExecute].isFree()){
        if (registers[rdIndex].write(diff,id,stageToExecute)){
          stages[presentStage].setFree();
          presentStage = stageToExecute;
          stages[presentStage].setInstruction(id);
          stageToExecute=-1;
          ////cout << "WB completed -->";
            // Instruction completed, so stage number is now invalid.
          return true;
        }
        else {
          stalled = true;
          stages[presentStage].setInstruction(id);
          stallingRegister = rdIndex;
          stallingInstructionId = registers[rdIndex].instructionId;
          ////cout << "Register not writable -->";
          return false;
        }
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        ////cout << "WB not free ->";
        return false;
      }
    }
  }
  return false;
}

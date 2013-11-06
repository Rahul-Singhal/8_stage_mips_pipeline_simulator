#include "Mult.h"

Mult::Mult(int rdIndex, int rsIndex, int rtIndex, int id){
  this->rdIndex = rdIndex;
  this->rsIndex = rsIndex;
  this->rtIndex = rtIndex;
  this->id = id;
  this->presentSubStage = 0;
}

void Mult::unstall(){
  if(!registers[rdIndex].valid && registers[rdIndex].instructionId==id)
    registers[rdIndex].unstall();
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

bool Mult::execute(int pc){
  // //cout<<"MULT"<<endl;
  // //cout<<"MAIN CALL HUWA"<<endl;
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
            //cout << "rs register not readable -->";

            return false;
          }
          else if (!registers[rtIndex].valid){
              // when rtIndex is not available without forwarding
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rtIndex;
            stallingInstructionId = registers[rtIndex].instructionId;    
            //cout << "rt register not readable -->";

            return false;
          }

          else if (  registers[rsIndex].instructionStage==10 && registers[rtIndex].instructionStage==10) {
              // this is the most normal case, when all values are simply avaiable not forwarded.
            registers[rdIndex].stallRegister(id); 
            a = registers[rsIndex].value;
            b = registers[rtIndex].value;
            stages[presentStage].setFree();
            presentStage = stageToExecute;
            stages[presentStage].setInstruction(id);
            /*Next stage would be mult which is stage 5*/
            stageToExecute += 2;
            stalled = false;
            //cout << "id completed -->";

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
            /*Next stage would be mult which is stage 5*/
            stageToExecute += 2;
            stalled = false;
            //cout << "rs value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" ;

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
            /*Next stage would be mult which is stage 5*/
            stageToExecute += 2;
            stalled = false;
            //cout << "rt value forwarded from id = " << forwardedFromInstructionId << " stage = " << forwardedFromInstructionStage << "-->" ;

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
            //cout << "mult ID stalls due to rs -->";
            return false;
          }
          else if (!registers[rtIndex].valid || registers[rtIndex].instructionStage!=10){
              // when rtIndex is not available without forwarding
            stages[presentStage].setInstruction(id);
            stalled = true;
            stallingRegister = rtIndex;
            stallingInstructionId = registers[rtIndex].instructionId;
            //cout << "ID stalls due to rt -->"; 
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
            /*Next stage would be mult which is stage 5*/
            stageToExecute += 2;
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
    case 5:
    {
      // Mult Stage
      registers[rdIndex].stallRegister(id);
      if(stages[stageToExecute].isFree()){
        product = a*b;
        stages[presentStage].setFree();
        presentStage = stageToExecute;
        stages[presentStage].setInstruction(id);
        presentSubStage++;
        if (presentSubStage == multSubStages){
          /*Next stage is MEM1 which is stage 7*/
          registers[rdIndex].write(product,id,stageToExecute); // TODO : Will it ever return false?
          stageToExecute += 2;
          //cout << "MULT stage done -->" ;
        }
        else {
          //cout << "MULT substage = " << presentSubStage  << "-->"; 
        }
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = stages[stageToExecute].instructionId;
        stalled = true;
        //cout << "MULT stage not free -->";

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
        if (registers[rdIndex].write(product,id,stageToExecute)){
          //cout<<"write true aaya "<<endl;
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
  return false;
}

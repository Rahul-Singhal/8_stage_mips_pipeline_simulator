#include "Slt.h"

Slt::Slt(int rdIndex, int rsIndex, int rtIndex, int id){
  this->rdIndex = rdIndex;
  this->rsIndex = rsIndex;
  this->rtIndex = rtIndex;
  this->id = id;
}

Slt* Slt::clone(){
  return new Slt (*this);
}

Slt::Slt(const Slt &i){
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
  this->rdIndex = i.rdIndex;
  this->rsIndex = i.rsIndex;
  this->rtIndex = i.rtIndex;
  this->sum = i.sum;
  this->a = i.a;
  this->b = i.b;
}


Slt::Slt(Slt &i){
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
  this->rdIndex = i.rdIndex;
  this->rsIndex = i.rsIndex;
  this->rtIndex = i.rtIndex;
  this->sum = i.sum;
  this->a = i.a;
  this->b = i.b;
}

void Slt::unstall(){
  registers[rdIndex].unstall(id); 
}

// depending on the return value of this bool, the program manager will put the appropriate stage of this instruction
// in the next queue of instructions. if return value is false  =>  instruction is still in the old stage.
// return value = ture => instruction may or may not have completed the stage, example in multiply. 

// If an instruction does not execute because the stage is not free or because registers are being written, then we 
// set the stage where it already is to busy. So that no other further instruction try to access the stage.

bool Slt::execute(int pc){
  // //////cout<<"###Slt####"<<endl;
  // //////cout<<"MAIN CALL HUWA"<<endl;
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
        //display = "IF1";
        ////cout << "if1 -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stalled = true;
        stallingInstructionId = -1;
        sStalls++;
//display = "Waiting for IF1 to be free!";
        ////cout << "if1 - wait -->"<<endl ;
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
        ////cout << "if2 -->" <<endl;
        return true;
      }
      else {
        stages[presentStage].setInstruction(id);
        stalled = true;
        stallingInstructionId = -1;
        sStalls++;
//display = "Waiting for IF2 to be free!";
        ////cout << "if2 - wait -->" <<endl;
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
        if (!registers[rsIndex].isValid()){
              // forwarded value
            // stages[presentStage].setInstruction(id);
          stalled = true;
          stallingRegister = rsIndex;
          stallingInstructionId = registers[rsIndex].instructionId;
          rStalls++;
            ////cout << "rs register not readable -->"<<endl;

          return false;
        }
        else if (!registers[rtIndex].isValid()){
              // when rtIndex is not available without forwarding
            // stages[presentStage].setInstruction(id);
          stalled = true;
          stallingRegister = rtIndex;
          stallingInstructionId = registers[rtIndex].instructionId; 
          rStalls++;   
            ////cout << "rt register not readable -->"<<endl;

          return false;
        }

        else {
          registers[rdIndex].stallRegister(id); 
          a = registers[rsIndex].value;
          b = registers[rtIndex].value;
          int lastTime;
          if(registers[rsIndex].isForwarded()){
            forwarded = true;           
            lastTime = registers[rsIndex].lastForwarderTime;
            forwardedFromInstructionId = registers[rsIndex].lastForwarder;
          }
          if(registers[rtIndex].isForwarded()){
            forwarded = true;
            if(registers[rtIndex].lastForwarderTime > lastTime)
              forwardedFromInstructionId = registers[rtIndex].lastForwarder;
          }
            // stages[presentStage].setFree();
            // presentStage = stageToExecute;
            // stages[presentStage].setInstruction(id);
          stageToExecute++;
          stalled = false;
            ////cout << "id completed -->"<<endl;

          return true;
        }
      }
      else {
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "ID not free -->"<<endl ;
        return false;
      }
    }
    case 4:
    {
      // EX Stage
      // registers[rdIndex].stallRegister(id);
      if(stages[stageToExecute].isFree()){
        if (a<b) sum = 1;
        else sum = 0;
        if(forwardingEnabled){
          registers[rdIndex].forwardIt(id, clockCycle);
          registers[rdIndex].unstallRegister(sum, id); // TODO : Will it ever return false?
        }
        stages[presentStage].setFree();
        presentStage = stageToExecute;
        stages[presentStage].setInstruction(id);
        /*Stage to execute will be MEM1 which is stage 7*/
        stageToExecute+=3;
        ////cout << "EX stage done -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "EX stage not free -->"<<endl;

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
        ////cout << "MEM1 stage done -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "MEM1 stage not free -->"<<endl;

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
        ////cout << "MEM2 stage done -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "MEM2 stage not free -->"<<endl;

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
        ////cout << "MEM3 stage done -->" <<endl;
        return true;
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "MEM3 stage not free -->"<<endl;

        return false;

      }
    }
    case 10:
    {
      // WB Stage
      // registers[rdIndex].stallRegister(id);
      if(stages[stageToExecute].isFree()){
        registers[rdIndex].unforwardIt(id);
        if(!forwardingEnabled)
          registers[rdIndex].unstallRegister(sum, id); // TODO : Will it ever return false?
        stages[presentStage].setFree();
        presentStage = stageToExecute;
        stages[presentStage].setInstruction(id);
        stageToExecute=-1;
        ////cout << "WB completed -->"<<endl;

          // Instruction completed, so stage number is now invalid.
        return true;
        
      }
      else{
        stages[presentStage].setInstruction(id);
        stallingInstructionId = -1;
        sStalls++;
        stalled = true;
        ////cout << "WB not free ->"<<endl;

        return false;
      }
    }
  }
  return false;
}

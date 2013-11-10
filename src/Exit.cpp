#include "Exit.h"


Exit::Exit(){

}

Exit::Exit(const Exit& i){
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
}

Exit * Exit::clone(){
	return new Exit(*this);
}

bool Exit::execute(int pc){
	programOver = true;
	return true;
}
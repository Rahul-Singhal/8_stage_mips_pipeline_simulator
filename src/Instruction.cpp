#include "Instruction.h"
using namespace std;

Instruction::Instruction(){
	//cout<<"Instruction"<<endl;
	stageToExecute = 1;
	presentStage = 0;
	stalled = false;
	stallingInstructionId = 0;
	stallingRegister = 0;
	forwarded =false;
	forwardedFromInstructionId = 0;
	forwardedFromInstructionStage = 0;
	display = "default";
	id = 0;
}

Instruction::Instruction(int s2ex, int ps, bool stall, int stallInstId, int stallReg, bool forw, int forwfromInstId, int forwStage, string disp, int i){
	stageToExecute = s2ex;
	presentStage = ps;
	stalled = stall;
	stallingInstructionId = stallInstId;
	stallingRegister = stallReg;
	forwarded =forw;
	forwardedFromInstructionId = forwfromInstId;
	forwardedFromInstructionStage = forwStage;
	display = disp;
	id = i;
}

void Instruction::init(){
  stageToExecute = 1;
  presentStage = 0;
  stalled = false;
  display = "";
}

bool Instruction::execute(int pc){
  //cout<<"FUCKED"<<endl;
  return false;
}

void Instruction::unstall(){
	//cout<<"FUCKED AGAIN"<<endl;
	return;
}

int Instruction::getStageToExecute(){
	return stageToExecute;
}

int Instruction::getPresentStage(){
	return presentStage;
}

bool Instruction::getStalled(){
	return stalled;
}

int Instruction::getStallingInstructionId(){
	return stallingInstructionId;
}

int Instruction::getStallingRegister(){
	return stallingRegister;
}

bool Instruction::getForwarded(){
	return forwarded;
}


int Instruction::getForwardedFromInstructionId(){
	return forwardedFromInstructionId;
}

int Instruction::getForwardedFromInstructionStage(){
	return forwardedFromInstructionStage;
}

string Instruction::getDisplayString(){
	return display;
}

int Instruction::getId(){
	return id;
}
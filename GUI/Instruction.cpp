#include "Instruction.h"
using namespace std;



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
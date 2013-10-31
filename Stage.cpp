#include "Stage.h"

Stage::Stage(int number){
	this->number= number;
	this->instructionId = -1;
}

Stage::Stage(int number , int Id){
	this->number = number;
	this->instructionId = Id;
}

bool Stage::isFree(){
	if(instructionId==-1)
		return true;
	return false;
}

void Stage::setInstruction(int instructionId){
	this->instructionId = instructionId;
}

void Stage::setFree(){
  instructionId = -1;
}
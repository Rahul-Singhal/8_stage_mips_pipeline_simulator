#include "Stage.h"

Stage::Stage(int number){
	this->number= number;
	this->instructionAddress = -1;
}

Stage::Stage(int number , int address){
	this->number = number;
	this->instructionAddress = address;
}

bool Stage::isFree(){
	if(instructionAddress==-1)
		return true;
	return false;
}
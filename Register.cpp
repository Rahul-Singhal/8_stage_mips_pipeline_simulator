#include "Register.h"

Register::Register(int id, int value){
	this->id = id;
	this->value = value;
	this->valid = true;  // ready to be read
}

void Register::stallRegister(int instructionId){
	if (valid) {
		valid = false;
		this->instructionId = instructionId;
	}
}


bool Register::write(int value, int instructionId, int instructionStage){
	if (valid) {
		valid = true;
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		return true;
	}
	else if (instructionId == this->instructionId){
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		valid = true;
		return true;
	}
	else {
		return false;
	}
}


#include "Register.h"

Register::Register(int id, int value){
	this->id = id;
	this->value = value;
	this->valid = true;  // ready to be read
}

void Register::stallRegister(int instructionId){
	if (valid && instructionStage==10) {
		valid = false;
		this->instructionId = instructionId;
	}
}


bool Register::write(int value, int instructionId, int instructionStage){
	cout<<value<<":"<<instructionId<<":"<<instructionStage<<endl;
	if (valid) {
		valid = true;
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		cout<<"valid"<<" "<<valid<<":"<<value<<"return true"<<endl;
		return true;
	}
	else if (instructionId == this->instructionId){
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		valid = true;
		cout<<"not valid but my own instruction"<<" "<<valid<<":"<<value<<"return true"<<endl;
		return true;
	}
	else {
		cout<<"invalid return false"<<endl;
		return false;
	}
}

void Register::unstall(){
	valid = true;
}

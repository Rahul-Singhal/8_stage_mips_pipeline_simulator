#include "Register.h"

Register::Register(int id, int value){
	this->id = id;
	this->value = value;
	this->blockingInstructions = list <int> (0,0);
}

void Register::stallRegister(int instructionId){
	//cout<<"add "<<instructionId<<" to "<<id<<endl;
	blockingInstructions.push_back(instructionId);
}

void Register::unstallRegister(int value, int instructionId){
	//cout<<"remove "<<instructionId<<"  from "<<id<<endl;
	//cout<<"size before "<<blockingInstructions.size()<<endl;
	blockingInstructions.remove(instructionId);
	this->value = value;
	//cout<<"size after "<<blockingInstructions.size()<<endl;
}

bool Register::isValid(){
	if(blockingInstructions.size()==0){
		//cout<<"validity for "<<id<<" return true"<<endl;
		return true;
	}
	//cout<<"validity for "<<id<<" return false"<<endl;
	return false;
}
/*
bool Register::write(int value, int instructionId, int instructionStage){
	////cout<<value<<":"<<instructionId<<":"<<instructionStage<<endl;
	if (valid) {
		valid = true;
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		////cout<<"valid"<<" "<<valid<<":"<<value<<"return true"<<endl;
		return true;
	}
	else if (instructionId == this->instructionId){
		this->instructionId = instructionId;
		this->instructionStage = instructionStage;
		this->value = value; 
		valid = true;
		////cout<<"not valid but my own instruction"<<" "<<valid<<":"<<value<<"return true"<<endl;
		return true;
	}
	else {
		////cout<<"invalid return false"<<endl;
		return false;
	}
}
*/
void Register::unstall(int instructionId){
	// instructionId = 10;
	// cout<<instructionId<<" unstalls "<<id<<". size= "<<blockingInstructions.size()<<endl;
	// cout<<blockingInstructions.front()<<":"<<blockingInstructions.back()<<endl;
	blockingInstructions.remove(instructionId);
	// cout<<"size= "<<blockingInstructions.size()<<endl;

}
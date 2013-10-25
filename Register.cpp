#include "Register.h"

Register::Register(int id, int value){
	this->id = id;
	this->value = value;
	this->status = 0;  // ready to be read
}

void Register::stallRegister(){
	status = 1;
}

void Register::setForwardedValue(int value){
	this->value = value;
	status = 2;
}

bool Register::writeBack(int value){
	this->value = value;
	status = 0;
	return true;
}

pair <int, int> Register::read(){
	return make_pair(status, value);
}
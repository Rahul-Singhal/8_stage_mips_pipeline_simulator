#include "Instruction.h"
using namespace std;

Instruction::Instruction(){
	cout<<"Instruction"<<endl;
}


void Instruction::init(){
  stageToExecute = 1;
  presentStage = 0;
  stalled = false;
  display = "";
}

bool Instruction::execute(int pc){
  cout<<"FUCKED"<<endl;
  return false;
}

void Instruction::unstall(){
	cout<<"FUCKED AGAIN"<<endl;
	return;
}
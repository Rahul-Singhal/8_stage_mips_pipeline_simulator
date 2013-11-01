#include "Instruction.h"
using namespace std;

Instruction::Instruction(){

}


void Instruction::init(){
  stageToExecute = 1;
  presentStage = 0;
  stalled = false;
  display = "";
}

bool Instruction::execute(){
	// cout<<"FUCKED"<<endl;
}
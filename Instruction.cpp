#include "Instruction.h"
using namespace std;

Instruction::Instruction(){

}


Instruction::init(){
  stageToExecute = 1;
  presentStage = 0;
  stalled = false;
  display = "";
}



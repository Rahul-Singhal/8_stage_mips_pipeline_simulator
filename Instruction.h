#ifndef INSTR_H
#define INSTR_H


#include "Register.h"
#include "Stage.h"
#include <vector>
#include <cstring>

using namespace std;

class Instruction: public System{
public:
	Instruction();
	static vector <Register> registers;
	static vector <Stage> stages;
	// eigth stage
	int stageToExecute;
  int presentStage;
  bool stalled;
  int stallingInstructionId;
  int stallingRegister;
  bool forwarded;
  int forwardedFromInstructionId;
  int forwardedFromInstructionStage;
  string display;
	int address;
  int id;
};

#endif
#ifndef INSTR_H
#define INSTR_H


#include "Register.h"
#include "System.h"
#include "Stage.h"
#include <vector>
#include <cstring>

using namespace std;

class Instruction: public System{
public:
	Instruction();
	Instruction(int s2ex, int ps, bool stall, int stallInstId, int stallReg, bool forw, int forwfromInstId, int forwStage, string disp, int i);
	void init();
	virtual bool execute(int pc);
	virtual void unstall();
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


	int getStageToExecute();
	int getPresentStage();
	bool getStalled();
	int getStallingInstructionId();
	int getStallingRegister();
	bool getForwarded();
	int getForwardedFromInstructionId();
	int getForwardedFromInstructionStage();
	string getDisplayString();
	int getId();
};

#endif
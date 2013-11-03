#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
using namespace std;

class Instruction{
private:
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
public:
	Instruction(int s2ex, int ps, bool stall, int stallInstId, int stallReg, bool forw, int forwfromInstId, int forwStage, string disp, int i);
	
	//get functions

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
#ifndef SYS_H
#define SYS_H

/*
	This system class is the base class which is inherited by Program
	and Instruction class so that they all have the same static variables
*/

#include <vector>
#include "Register.h"
#include "Stage.h"
#include "Memory.h"

using namespace std;

class System{
public:
	static bool programOver;
	static vector <Register> registers;
	static vector <Stage> stages;
	static int programCounter; // holds the index of the instruction which will be inserted 
	static bool forwardingEnabled;
  	static int multSubStages;
  	static bool fastBranching;
  	static Memory memory;
  	static map<string, int> labelMap;
  	static int rStalls;
  	static int sStalls;
};

#endif
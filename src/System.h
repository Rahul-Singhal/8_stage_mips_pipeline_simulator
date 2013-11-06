#ifndef SYS_H
#define SYS_H

/*
	This system class is the base class which is inherited by Program
	and Instruction class so that they all have the same static variables
*/

#include <vector>
#include "Register.h"
#include "Stage.h"

using namespace std;

class System{
public:
	static vector <Register> registers;
	static vector <Stage> stages;
	/*memory as of now is an integer array of size 10000*/
	static vector <int> memory;
	static int programCounter; // holds the index of the instruction which will be inserted 
	static bool forwardingEnabled;
  	static int multSubStages;
  	static bool fastBranching;
};

#endif
#ifndef EXIT_H
#define EXIT_H

#include "Instruction.h"

class Exit: public Instruction{
public:
	Exit();
	bool execute(int pc);
};

#endif
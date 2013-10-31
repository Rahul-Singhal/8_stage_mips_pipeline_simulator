#include "System.h"

vector<Stage> System::stages(9, Stage(0));

vector<Register> System::registers(32, Register(0, 0));

bool System::forwardingEnabled = false;

int System::programCounter = 1;

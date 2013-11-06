#include "System.h"

vector<Stage> System::stages(11, Stage(0));

vector<Register> System::registers(32, Register(0, 0));

vector<int> System::memory(10000, 0);

bool System::forwardingEnabled = false;

int System::programCounter = 1;

int System::multSubStages = 4;

bool System::fastBranching = false;

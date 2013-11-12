#include "System.h"

vector<Stage> System::stages(11, Stage(0));

vector<Register> System::registers(32, Register(0, 0));

bool System::forwardingEnabled = true;

int System::programCounter = 1;

int System::rStalls = 0;

int System::sStalls = 0;

int System::multSubStages = 4;

bool System::fastBranching = false;

Memory System::memory=Memory();

map<string, int> System::labelMap = *(new map<string , int>);

bool System::programOver = false;

int System::clockCycle = 0;

bool System::branchChanged = false;

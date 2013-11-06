#ifndef SUB_H
#define SUB_H

#include "Instruction.h"

class Sub: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int rtIndex;
  int diff;
  int a, b;
  Sub(int rdIndex, int rsIndex, int rtIndex, int id);
  bool execute(int pc);
  void unstall();
};

#endif
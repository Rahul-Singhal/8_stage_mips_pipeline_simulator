#ifndef ORI_H
#define ORI_H

#include "Instruction.h"

class Ori: public Instruction{
public:
  int immediate;
  int rsIndex;
  int rtIndex;
  int sum;
  int a, b;
  Ori(int rtIndex, int rsIndex, int immediate, int id);
  bool execute(int pc);
};

#endif
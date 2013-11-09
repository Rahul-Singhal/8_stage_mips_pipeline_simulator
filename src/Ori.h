#ifndef ORI_H
#define ORI_H

#include "Instruction.h"

class Ori: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int immediate;
  int sum;
  int a, b;
  Ori(int rdIndex, int rsIndex, int immediate, int id);
  Ori(Ori &a);
  Ori(const Ori &i);
  Ori * clone();
  bool execute(int pc);
  void unstall();
};

#endif
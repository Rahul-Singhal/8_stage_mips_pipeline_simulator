#ifndef SLT_H
#define SLT_H

#include "Instruction.h"

class Slt: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int rtIndex;
  int sum;
  int a, b;
  Slt(int rdIndex, int rsIndex, int rtIndex, int id);
  Slt(Slt &a);
  Slt(const Slt &i);
  Slt * clone();
  bool execute(int pc);
  void unstall();
};

#endif
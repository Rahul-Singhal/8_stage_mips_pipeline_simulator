#ifndef SLTI_H
#define SLTI_H

#include "Instruction.h"

class Slti: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int immediate;
  int sum;
  int a, b;
  Slti(int rdIndex, int rsIndex, int immediate, int id);
  Slti(Slti &a);
  Slti(const Slti &i);
  Slti * clone();
  bool execute(int pc);
  void unstall();
};

#endif
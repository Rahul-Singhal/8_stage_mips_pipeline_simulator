#ifndef ANDI_H
#define ANDI_H

#include "Instruction.h"

class Andi: public Instruction{
public:
  int immediate;
  int rsIndex;
  int rtIndex;
  int sum;
  int a, b;
  Andi(int rtIndex, int rsIndex, int immediate, int id);
  bool execute(int pc);
};

#endif
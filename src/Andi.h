#ifndef ANDI_H
#define ANDI_H

#include "Instruction.h"

class Andi: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int immediate;
  int sum;
  int a, b;
  Andi(int rdIndex, int rsIndex, int immediate, int id);
  Andi(Andi &a);
  Andi(const Andi &i);
  Andi * clone();
  bool execute(int pc);
  void unstall();
};

#endif
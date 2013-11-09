#ifndef XORI_H
#define XORI_H

#include "Instruction.h"

class Xori: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int immediate;
  int sum;
  int a, b;
  Xori(int rdIndex, int rsIndex, int immediate, int id);
  Xori(Xori &a);
  Xori(const Xori &i);
  Xori * clone();
  bool execute(int pc);
  void unstall();
};

#endif
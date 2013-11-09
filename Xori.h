#ifndef XORI_H
#define XORI_H

#include "Instruction.h"

class Xori: public Instruction{
public:
  int immediate;
  int rsIndex;
  int rtIndex;
  int sum;
  int a, b;
  Xori(int rtIndex, int rsIndex, int immediate, int id);
  bool execute(int pc);
};

#endif
#ifndef MULT_H
#define MULT_H

#include "Instruction.h"

class Mult: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int rtIndex;
  int product;
  int presentSubStage;
  int a, b;
  Mult(int rdIndex, int rsIndex, int rtIndex, int id);
  //implement this and store the result in registers hi and lo
  Mult(int rdIndex, int rsIndex, int id);
  bool execute(int pc);
  void unstall();
};

#endif
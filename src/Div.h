#ifndef DIV_H
#define DIV_H

#include "Instruction.h"

class Div: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int rtIndex;
  int product;
  int presentSubStage;
  int a, b;
  Div(int rdIndex, int rsIndex, int rtIndex, int id);
  //implement this and store the result in registers hi and lo
  Div(int rdIndex, int rsIndex, int id);
  Div(const Div &m);
  Div * clone();
  Div(Div &m);
  bool execute(int pc);
  void unstall();
};

#endif
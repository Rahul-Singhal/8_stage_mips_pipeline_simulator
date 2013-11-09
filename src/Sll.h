#ifndef Sll_H
#define Sll_H

#include "Instruction.h"

class Sll: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int shamt;
  int sum;
  int a, b;
  Sll(int rdIndex, int rsIndex, int shamt, int id);
  Sll(Sll &a);
  Sll(const Sll &i);
  Sll * clone();
  bool execute(int pc);
  void unstall();
};

#endif
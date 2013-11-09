#ifndef SRL_H
#define SRL_H

#include "Instruction.h"

class Srl: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int shamt;
  int sum;
  int a, b;
  Srl(int rdIndex, int rsIndex, int shamt, int id);
  Srl(Srl &a);
  Srl(const Srl &i);
  Srl * clone();
  bool execute(int pc);
  void unstall();
};

#endif
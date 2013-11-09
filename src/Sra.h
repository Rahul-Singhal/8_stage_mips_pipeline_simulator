#ifndef Sra_H
#define Sra_H

#include "Instruction.h"

class Sra: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int shamt;
  int sum;
  int a, b;
  Sra(int rdIndex, int rsIndex, int shamt, int id);
  Sra(Sra &a);
  Sra(const Sra &i);
  Sra * clone();
  bool execute(int pc);
  void unstall();
};

#endif
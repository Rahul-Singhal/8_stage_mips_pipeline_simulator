#ifndef ADDI_H
#define ADDI_H

#include "Instruction.h"

class Addi: public Instruction{
public:
  int rdIndex;
  int rsIndex;
  int immediate;
  int sum;
  int a, b;
  Addi(int rdIndex, int rsIndex, int immediate, int id);
  Addi(Addi &a);
  Addi(const Addi &i);
  Addi * clone();
  bool execute(int pc);
  void unstall();
};

#endif
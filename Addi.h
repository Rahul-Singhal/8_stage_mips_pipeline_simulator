#ifndef ADDI_H
#define ADDI_H

#include "Instruction.h"

class Addi: public Instruction{
public:
  int immediate;
  int rsIndex;
  int rtIndex;
  int sum;
  int a, b;
  Addi(int rtIndex, int rsIndex, int immediate, int id);
  bool execute();
};

#endif
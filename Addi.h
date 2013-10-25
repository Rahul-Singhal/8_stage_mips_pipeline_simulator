#ifndef ADDI_H
#define ADDI_H

class Addi: public Instruction{
public:
	int rtIndex;
	int rsIndex;
	int immediate;
	int sum ;
	int a, b;

	Addi(int rtIndex, rsIndex, immediate);
	bool execute();
}
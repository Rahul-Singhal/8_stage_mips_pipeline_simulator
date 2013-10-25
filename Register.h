#ifndef REG_H
#define REG_H

class Register{
public:
	int id;
	int value;
	bool status;
	Register(int id, int value);
};

#endif
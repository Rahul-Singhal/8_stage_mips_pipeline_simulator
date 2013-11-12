#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include "Instruction.h"
#include "memory.h"
#include "System.h"
#include "Add.h"
#include "Addi.h"
#include "Sub.h"
#include "Mult.h"
#include "And.h"
#include "Andi.h"
#include "Or.h"
#include "Ori.h"
#include "Xor.h"
#include "Xori.h"
#include "Slti.h"
#include "Sll.h"
#include "Sra.h"
#include "Srl.h"
#include "Srav.h"
#include "Slt.h"
#include "Sllv.h"
#include "Srlv.h"
#include "Nor.h"
#include "Exit.h"
#include "Beq.h"
#include "Lw.h"
#include "Li.h"
#include "La.h"
#include "Not.h"
#include "Sw.h"
#include "Lb.h"
#include "Sb.h"
#include "J.h"
#include "Jal.h"
#include "Blt.h"
#include "Bgt.h"
#include "B.h"
#include "Bne.h"
#include "Jr.h"
using namespace std;

class Parser : public System{
private:
	string fileName;
	vector<string> v;
	vector<string> lineWords;
	int instructionNumber;
	int lineNumber;
	//label-map in the system class
	map<string, int> registerMap;
	map<string, int> instructionIntMap;

	void initMaps();
	void syntaxError();
	int convertToNumber(string str);
	bool text;
	bool data;
	vector<Instruction *> codeVector;
	//vector< char* > asciiTable;
	//vector< char* > asciizTable;
	//vector< vector<int> > wordTable;
public:
	Parser(string fileName , vector<Instruction *> & code);
	vector<Instruction *> getVector(string fileName);
	Parser();
	void printLabels();
	void parseLine(string str);
	void makeInstruction();
	// parse is assumed to take an empty vector of Instructions and fill it with the correct
	// Intructions of the correct type (sub classes) in the correct order
	//void parse(vector <Instruction> & code);
};

#endif

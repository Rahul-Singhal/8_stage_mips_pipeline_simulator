#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include "Instruction.h"
using namespace std;



class Parser{
private:
	string fileName;
	vector<string> v;
	vector<string> lineWords;
	int instructionNumber;
	map<string, int> labelMap;
	map<string, int> registerMap;
	map<string, int> instructionIntMap;

	void initMaps();
	void syntaxError();
	int convertToNumber(string str);


public:
	Parser(string fileName);
	void printLabels();
	void parseLine(string str);
	void makeInstruction();
	// parse is assumed to take an empty vector of Instructions and fill it with the correct
	// Intructions of the correct type (sub classes) in the correct order
	void parse(vector <Instruction> & code);
};

#endif

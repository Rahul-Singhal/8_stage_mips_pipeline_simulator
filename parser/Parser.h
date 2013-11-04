#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include "memory.h"
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
	//dataMap is a map that maps labels to their index in memory vector
	map<string, int > dataMap;
	Memory mem;

	void initMaps();
	void syntaxError();
	int convertToNumber(string str);
	bool text;
	bool data;
	//vector< char* > asciiTable;
	//vector< char* > asciizTable;
	//vector< vector<int> > wordTable;
public:
	Parser(string fileName);
	void printLabels();
	void parseLine(string str);
	void makeInstruction();
	// parse is assumed to take an empty vector of Instructions and fill it with the correct
	// Intructions of the correct type (sub classes) in the correct order
	// void parse(vector <Instruction> & code);
};

#endif

#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<map>
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
};

#endif
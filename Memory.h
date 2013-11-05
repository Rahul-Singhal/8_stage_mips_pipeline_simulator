#ifndef MEM_H
#define MEM_H

#include <map>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Memory{

private:
  vector<char> store;
  int freePointer; 
  map<string, pair<int, int> > memoryMap;

public:
  Memory();

  void storeWord(int address, int word);
  int loadWord(int address);

  void storeByte(int address, char byte);
  char loadByte(int address);

  int loadAddress(string label);
  int storeAscii(string label, string ascii);
  int storeAsciiz(string label, string asciiz);
  string getString(int address) ;

  int storeWords(string label, vector<int> v);
  int allocateSpace(string label, int count);

  int storeBytes(string label, vector<char> v);

};
#endif
#include<cstdio>
#include<iostream>
#include "Memory.h"
#include "Parser.h"
#include "Program.h"
using namespace std;


int main(){

	 Parser myParser("gcd.asm");
	myParser.printLabels();
  
  Program program("gcd.asm");
  program.execute();
	cout<<endl;

  Memory mem;
  mem.storeWord (2,-80);
  cout << mem.loadWord(2) << endl;
  cout << (int)mem.loadByte(3) << endl;
  string t="test" ;
  string text = "text";
  cout << strlen(text.c_str()) << endl;
  mem.storeAsciiz(t,text);
  cout << mem.loadAddress(t) << endl;
  cout << mem.getString(mem.loadAddress(t)) << endl;

	return 0;
}
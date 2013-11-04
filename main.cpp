#include<cstdio>
#include<iostream>
#include "Parser.h"
#include "Program.h"
using namespace std;


int main(){
	Parser myParser("gcd.asm");
	// Program program("gcd.asm");
	// program.execute();
	// /*cout<<endl;
	myParser.printLabels();
	return 0;
}
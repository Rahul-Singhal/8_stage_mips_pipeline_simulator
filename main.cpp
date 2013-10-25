#include<cstdio>
#include<iostream>
#include "Parser.h"
using namespace std;


int main(){
	Parser myParser("gcd.asm");
	cout<<endl;
	myParser.printLabels();
}
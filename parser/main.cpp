#include <cstdio>
#include "Parser.h"
#include <iostream>
using namespace std;

int main(){
	Parser p("test.s");
	cout<<"\n\n"<<endl;
	p.printLabels();
	return 0;
}
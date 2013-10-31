#include "Program.h"

Program::Program(string filename){
	parser = Parser(filename);
	code = new vector();
	parser.parse(code);
}

void Program::execute(){
	
}
#include "Program.h"

Program::Program(string filename) : parser(filename){
	code.assign(0,Instruction());
	parser.parse(code);
	sepInstructions.assign(9, vector<Instruction*>());
}

void Program::execute(){

	for(int i = 0 ; i < 9 ; i++)
		stages[i].number = i;
	for(int i = 0 ; i < 32 ; i++)
		registers[i].id = i;


	programCounter = 0;
	instrId = 0;
	code[programCounter].id = instrId;
	code[programCounter].presentStage = 0;
	code[programCounter].stageToExecute = 1;
	currInstructions.push_back(code[programCounter]);
	while(!currInstructions.empty()){
		list<Instruction>::iterator it;
		for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
			sepInstructions[it->stageToExecute].push_back(&(*it));
		}
		// the whole logic of running one clock cycle comes here
		for(int i = 8 ; i >= 1 ; i--){
			for(int j = 0 ; j < sepInstructions[i].size() ; j++){
				sepInstructions[i][j]->execute();
			}
		}
		
		it = currInstructions.begin() ;
		while(it != currInstructions.end()){
			if(it->stageToExecute==-1)
				currInstructions.erase(it++);
			else
				it++;
		}		

		if(stages[1].isFree()){
			programCounter++;
			if(programCounter <= code.size()){
				instrId++;		
				code[programCounter].id = instrId;
				code[programCounter].presentStage = 0;
				code[programCounter].stageToExecute = 1;
				currInstructions.push_back(code[programCounter]);
			}
			else
				return;
		}
// Setting the stages free
		for(int i = 0 ; i < stages.size() ; i++)
			stages[i].setFree();
	}
}
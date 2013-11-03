#include "Program.h"
 // : parser(filename)
Program::Program(string filename){
	code.assign(0,Mult(1,1,1,1));
	// parser.parse(code);
	Mult a(12, 10, 12, 1);
	code.push_back(a);
	code.push_back(a);
	code.push_back(a);
	code.push_back(a);
	sepInstructions.assign(10, vector<Mult*>());
}

void Program::execute(){

	for(int i = 0 ; i <= 9 ; i++)
		stages[i].number = i;
	for(int i = 0 ; i < 32 ; i++){
		registers[i].id = i;
		registers[i].value = 0;
		registers[i].valid = true;
		registers[i].instructionStage = 8;
	}


	programCounter = 0;
	instrId = 0;
	code[programCounter].id = instrId;
	code[programCounter].presentStage = 0;
	code[programCounter].stageToExecute = 1;
	currInstructions.push_back(code[programCounter]);
	while(!currInstructions.empty()){
		// cout<<currInstructions.front().id<<":"<<currInstructions.front().presentStage<<":"<<currInstructions.front().stageToExecute<<endl;
		list<Mult>::iterator it;
		for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
			sepInstructions[it->stageToExecute].push_back(&(*it));
		}
		// the whole logic of running one clock cycle comes here
		for(int i = 9 ; i >= 1 ; i--){
			for(int j = 0 ; j < sepInstructions[i].size() ; j++){
				cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
				sepInstructions[i][j]->execute1();
				cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
			}
		}
		
		it = currInstructions.begin() ;
		while(it != currInstructions.end()){
			if(it->stageToExecute==-1)
				currInstructions.erase(it++);
			else
				it++;
		}		

		if(stages[0].isFree()){
			programCounter++;
			if(programCounter < code.size()){
				instrId++;		
				code[programCounter].id = instrId;
				code[programCounter].presentStage = 0;
				code[programCounter].stageToExecute = 1;
				currInstructions.push_back(code[programCounter]);
			}
		}
// Setting the stages free
		for(int i = 0 ; i < stages.size() ; i++)
			stages[i].setFree();
		for(int i = 1 ; i <= 9 ; i++ )
			sepInstructions[i].clear();

		cout<<"cycle"<< endl;
	}
}
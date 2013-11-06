#include "Program.h"
 // : parser(filename)


Program::Program(string filename){
	code.assign(0, new Instruction());
	// parser.parse(code);
	Add * i1 = new Add(1,2,3,0);
	Mult * i2 = new Mult(1,2,3,0);
	Sub * i3 = new Sub(1,2,3,0);
	code.push_back(i1);
	code.push_back(i2);
	code.push_back(i3);
	sepInstructions.assign(11, vector<Instruction*>(0, new Instruction()));
}

void Program::init(){
	//Initialising
	// setting the stages
	for(int i = 0 ; i <= 10 ; i++){
		cout<<i<<endl;
		stages[i].number = i;
	}
	// initialising the registers once and for all
	for(int i = 0 ; i < 32 ; i++){
		registers[i].id = i;
		registers[i].value = 0;
		registers[i].valid = true;
		registers[i].instructionStage = 8;
	}

	programCounter = 0;
	instrId = 0;
	code[programCounter]->id = instrId;
	code[programCounter]->presentStage = 0;
	code[programCounter]->stageToExecute = 1;
	currInstructions.push_back(code[programCounter]);
}

list <Instruction *> Program::execute(){
	list<Instruction *>::iterator it;
		//STABLE SORT
	for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
		sepInstructions[(*it)->stageToExecute].push_back(*it);
	}
		// the whole logic of running one clock cycle comes here
	for(int i = 10 ; i >= 1 ; i--){
		for(int j = 0 ; j < sepInstructions[i].size() ; j++){
			cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
			prevPc = programCounter;
			sepInstructions[i][j]->execute(programCounter);
			nextPc = programCounter;
			if(nextPc != prevPc){
				cout<<"Branch taken and destination other than next instruction!"<<endl;
				cout<<"Flush needed!"<<endl;
					/*setting stages free*/
				stages[0].setFree();
				stages[1].setFree();
				stages[2].setFree();
				if(!fastBranching){
					/*complications!
					if predicate is calculated in EX then there is a chance
					that some register was stalled due to the next instruction in the ID stage
					we need to set that register free*/
					/*solution
					The only instruction which can do this is the next instruction(addr), so we need
					to unstall its destination register, this destination register's name could
					vary depending on the instruction, so we'll have to add this functionality
					of unstalling in the individual classes where the dest reg is known
					*/
					stages[3].setFree();
					for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
						if((*it)->id == sepInstructions[i][j]->id){
							it++;
							(*it)->unstall(); /*unstalling the register*/
							break;
						}
					}
					/*removing elements after the branch instructions from the queue*/
					while(it != currInstructions.end())
						currInstructions.erase(it++);
				}
			}
			cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
		}
	}
	list <Instruction *> returnInstructions(currInstructions);
	it = currInstructions.begin() ;
	while(it != currInstructions.end()){
		if((*it)->stageToExecute==-1)
			currInstructions.erase(it++);
		else
			it++;
	}		

	if(stages[0].isFree()){
		programCounter++;
		if(programCounter < code.size()){
			instrId++;		
			code[programCounter]->id = instrId;
			code[programCounter]->presentStage = 0;
			code[programCounter]->stageToExecute = 1;
			currInstructions.push_back(code[programCounter]);
		}
	}
// Setting the stages free
	for(int i = 0 ; i < stages.size() ; i++)
		stages[i].setFree();
// clearing the sorted buckets for the next cycle
	for(int i = 1 ; i <= 9 ; i++ )
		sepInstructions[i].clear();

	cout<<"cycle"<< endl;
	return returnInstructions;
}
	

void Program::executeAll(){

	while(!currInstructions.empty()){
		// cout<<currInstructions.front().id<<":"<<currInstructions.front().presentStage<<":"<<currInstructions.front().stageToExecute<<endl;
		list<Instruction *>::iterator it;
		//STABLE SORT
		for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
			sepInstructions[(*it)->stageToExecute].push_back(*it);
		}
		// the whole logic of running one clock cycle comes here
		for(int i = 10 ; i >= 1 ; i--){
			for(int j = 0 ; j < sepInstructions[i].size() ; j++){
				cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
				prevPc = programCounter;
				sepInstructions[i][j]->execute(programCounter);
				nextPc = programCounter;
				if(nextPc != prevPc){
					cout<<"Branch taken and destination other than next instruction!"<<endl;
					cout<<"Flush needed!"<<endl;
					/*setting stages free*/
					stages[0].setFree();
					stages[1].setFree();
					stages[2].setFree();
					if(!fastBranching){
						/*complications!
						if predicate is calculated in EX then there is a chance
						that some register was stalled due to the next instruction in the ID stage
						we need to set that register free*/
						/*solution
						The only instruction which can do this is the next instruction(addr), so we need
						to unstall its destination register, this destination register's name could
						vary depending on the instruction, so we'll have to add this functionality
						of unstalling in the individual classes where the dest reg is known
						*/
						stages[3].setFree();
						for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
							if((*it)->id == sepInstructions[i][j]->id){
								it++;
								(*it)->unstall(); /*unstalling the register*/
								break;
							}
						}
						/*removing elements after the branch instructions from the queue*/
						while(it != currInstructions.end())
							currInstructions.erase(it++);
					}
				}
				cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
			}
		}
		
		it = currInstructions.begin() ;
		while(it != currInstructions.end()){
			if((*it)->stageToExecute==-1)
				currInstructions.erase(it++);
			else
				it++;
		}		

		if(stages[0].isFree()){
			programCounter++;
			if(programCounter < code.size()){
				instrId++;		
				code[programCounter]->id = instrId;
				code[programCounter]->presentStage = 0;
				code[programCounter]->stageToExecute = 1;
				currInstructions.push_back(code[programCounter]);
			}
		}
// Setting the stages free
		for(int i = 0 ; i < stages.size() ; i++)
			stages[i].setFree();
// clearing the sorted buckets for the next cycle
		for(int i = 1 ; i <= 9 ; i++ )
			sepInstructions[i].clear();

		cout<<"cycle"<< endl;
	}
}
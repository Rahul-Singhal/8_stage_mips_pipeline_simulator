#include "Program.h"
 // : parser(filename)


Program::Program(string filename){
	code.assign(0, new Instruction());
	// parser.parse(code);
	Add * i1 = new Add(1,2,3,0);
	Mult * i2 = new Mult(1,2,1,0);
	Beq * i3 = new Beq(1,2,0,0);
	Add * i4 = new Add(1,2,3,0);
	Mult * i5 = new Mult(1,2,1,0);
	Mult * i6 = new Mult(1,2,3,0);
	code.push_back(i1);
	code.push_back(i2);
	code.push_back(i3);
	code.push_back(i4);
	code.push_back(i5);
	code.push_back(i6);
	/*Mult * i1 = new Mult(1,2,3,0);
	Mult * i2 = new Mult(1,2,3,0);
	Add * i3 = new Add(1,2,1,0);
	Mult * i4 = new Mult(1,2,1,0);
	Add * i5 = new Add(1,2,1,0);
	Mult * i6 = new Mult(1,2,1,0);
	Add * i7 = new Add(1,2,1,0);
	code.push_back(i1);
	code.push_back(i2);
	code.push_back(i3);
	code.push_back(i4);
	code.push_back(i5);
	code.push_back(i6);
	code.push_back(i7);*/

	sepInstructions.assign(11, vector<Instruction*>(0, new Instruction()));
}

void Program::init(){
	//Initialising
	// setting the stages
	for(int i = 0 ; i <= 10 ; i++){
		// ////cout<<i<<endl;
		stages[i].number = i;
	}
	// initialising the registers once and for all
	for(int i = 0 ; i < 32 ; i++){
		registers[i].id = i;
		registers[i].value = 0;
		// registers[i].valid = true;
		// registers[i].instructionStage = 10;
	}

	programCounter = 0;
	instrId = 0;
	code[programCounter]->id = instrId;
	code[programCounter]->presentStage = 0;
	code[programCounter]->stageToExecute = 1;
	currInstructions.push_back(code[programCounter]);
}

vector <Instruction> Program::execute(){

	// cout<<currInstructions.size()<<endl;
	list<Instruction *>::iterator it;
		//STABLE SORT
	// cout<<"starts with ";
	for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
		// cout<<(*it)->id<<", "<<(*it)->presentStage<<", "<<(*it)->stageToExecute<<" :: ";
		sepInstructions[(*it)->stageToExecute].push_back(*it);
	}
	// cout<<endl;
		// the whole logic of running one clock cycle comes here
	prevPc = programCounter;
	for(int i = 10 ; i >= 1 ; i--){
		for(int j = 0 ; j < sepInstructions[i].size() ; j++){
			// cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
			sepInstructions[i][j]->execute(programCounter);
			// cout << "pc = " << programCounter << endl;
			// cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
		}
	}
	vector <Instruction> returnInstructions(0, Instruction());
	it = currInstructions.begin() ;
	while(it != currInstructions.end()){
		returnInstructions.push_back(**it);
		it++;
	}
	nextPc = programCounter;
	if(nextPc != prevPc){
		// cout<<"yahan bhi aaya pc != prevpc"<<endl;
				// ////cout<<"Branch taken and destination other than next instruction!"<<endl;
				// ////cout<<"Flush needed!"<<endl;
					/*setting stages free*/
		stages[0].setFree();
		stages[1].setFree();
		stages[2].setFree();
		// cout<<"yo1"<<endl;
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
				if((*it)->presentStage == 3){
					if(!fastBranching)
						(*it)->unstall();
					else
						it++;
					break;
				}
			}
			/*removing elements after the branch instructions from the queue*/
			while(it != currInstructions.end()){
				// cout<<(*it)->id<<"::::::"<<(*it)->presentStage<<endl;
				currInstructions.erase(it++);
			}
		// cout<<"yo4"<<endl;
	}
	// cout<<"yahan se bahar aaya pc != prevpc"<<endl;
	it = currInstructions.begin() ;
	while(it != currInstructions.end()){
		if((*it)->stageToExecute==-1)
			currInstructions.erase(it++);
		else
			it++;
	}		
	it = currInstructions.begin();
	// cout<<"ends up with ";
	/*while(it != currInstructions.end()){
		cout<<(*it)->id<<", "<<(*it)->presentStage<<", "<<(*it)->stageToExecute<<" :: ";
		it++;
	}
	cout<<endl;*/
	if(stages[0].isFree()){
		// cout<<"is ke ander aaya "<<endl;
		programCounter++;
		// cout<<programCounter<<" <-- pc ab ye hai"<<endl;
		if(programCounter < code.size()){
			instrId++;		
			/*code[programCounter]->id = instrId;
			code[programCounter]->presentStage = 0;
			code[programCounter]->stageToExecute = 1;*/
			currInstructions.push_back(code[programCounter]->clone());
			currInstructions.back()->id = instrId;
			currInstructions.back()->presentStage = 0;
			currInstructions.back()->stageToExecute = 1;
			/*(*code[programCounter])
			currInstructions.push_back(;*/
		}
	}
// Setting the stages free
	for(int i = 0 ; i < stages.size() ; i++)
		stages[i].setFree();
// clearing the sorted buckets for the next cycle
	for(int i = 1 ; i <= 9 ; i++ )
		sepInstructions[i].clear();
	// ////cout<<"cycle"<< endl;
	return returnInstructions;
}


void Program::executeAll(){

	while(!currInstructions.empty()){
		// ////cout<<currInstructions.front().id<<":"<<currInstructions.front().presentStage<<":"<<currInstructions.front().stageToExecute<<endl;
		list<Instruction *>::iterator it;
		//STABLE SORT
		for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
			sepInstructions[(*it)->stageToExecute].push_back(*it);
		}
		// the whole logic of running one clock cycle comes here
		for(int i = 10 ; i >= 1 ; i--){
			for(int j = 0 ; j < sepInstructions[i].size() ; j++){
				// ////cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
				prevPc = programCounter;
				sepInstructions[i][j]->execute(programCounter);
				nextPc = programCounter;
				if(nextPc != prevPc){
					////cout<<"Branch taken and destination other than next instruction!"<<endl;
					////cout<<"Flush needed!"<<endl;
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
				// ////cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
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

		////cout<<"cycle"<< endl;
	}
}
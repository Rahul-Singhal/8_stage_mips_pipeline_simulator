#include "Program.h"
#include <cstdlib>
 // : parser(filename)


Program::Program(string filename) {
	// code.assign(0, new Instruction());
	// Parser parser(filename, code);
	// parser.parse(code);
	// Add * i1 = new Add(1,2,3,0);
	// Lw * i2 = new Lw(1,2,0,0);
	// Beq * i3 = new Beq(4,4,0,0);
	// Mult * i4 = new Mult(1,2,1,0);
	// Add * i5 = new Add(1,2,3,0);
	// Add * i6 = new Add(1,2,3,0);
	// code.push_back(i1);
	// code.push_back(i2);
	// code.push_back(i3);
	// code.push_back(i3);
	// code.push_back(i4);
	// code.push_back(i5);
	// code.push_back(i6);
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
	
	// //cout << &code << endl;
	// //cout << "HERE1" <<endl;
	// //codeut << code.size() << endl;
// UNCOMMENT THIS TO USE THE PARSER
	codeSnippet = parser.getVector(filename);
	vector <Instruction *>::iterator it;
	for(it = codeSnippet.begin(); it != codeSnippet.end(); it++){
		code.push_back((*it)->clone());
		code.back()->id = 0;
		code.back()->presentStage = 0;
		code.back()->stageToExecute = 1;
	}

	// cout<<"the size of vector is "<<code.size()<<endl;
	// exit(0);
	// //cout<<"Inside the Program object"<<endl;
	// cout<<"Prining the label map:"<<endl;
	// for (map<string,int>::iterator it=labelMap.begin(); it!=labelMap.end(); ++it)
 //    cout << it->first << " => " << it->second << '\n';
	// exit(0);
	
	sepInstructions.assign(11, vector<Instruction*>(0, new Instruction()));
}

void Program::init(){
	//Initialising
	// setting the stages
	for(int i = 0 ; i <= 10 ; i++){
		// //////cout<<i<<endl;
		stages[i].number = i;
	}
	// initialising the registers once and for all
	for(int i = 0 ; i < 32 ; i++){
		if(i == 29){
			registers[i].id = i;
			registers[i].value = 10485756;
		}
		else{
			registers[i].id = i;
			registers[i].value = 0;
		}
		// registers[i].valid = true;
		// registers[i].instructionStage = 10;
	}

	programCounter = 0;
	instrId = 0;
	clockCycle = 0;
	if(code.empty()){
		cout<<"Nothing to simulate!"<<endl;
		exit(0);
	}
	code[programCounter]->id = instrId;
	code[programCounter]->presentStage = 0;
	code[programCounter]->stageToExecute = 1;
	currInstructions.push_back(code[programCounter]);
}

void Program::reset(){
	code.clear();
	this->init();
}

vector <Instruction> Program::execute(){
	clockCycle++;
	flush = false;
	// //cout<<currInstructions.size()<<endl;
	list<Instruction *>::iterator it;
		//STABLE SORT
	// //cout<<"starts with ";
	for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
		// //cout<<(*it)->id<<", "<<(*it)->presentStage<<", "<<(*it)->stageToExecute<<" :: ";
		sepInstructions[(*it)->stageToExecute].push_back(*it);
	}
	// //cout<<endl;
		// the whole logic of running one clock cycle comes here
	prevPc = programCounter;
	for(int i = 10 ; i >= 1 ; i--){
		for(int j = 0 ; j < sepInstructions[i].size() ; j++){
			// //cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
			branchChanged = false;
			sepInstructions[i][j]->execute(programCounter);
			if(branchChanged){
				/*It means that some branch chenge instruction has been executed*/
				if(programCounter!=sepInstructions[i][j]->address)
					flush=true;
			}
			// //cout << "pc = " << programCounter << endl;
			// //cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
		}
	}
	vector <Instruction> returnInstructions(0, Instruction());
	it = currInstructions.begin() ;
	while(it != currInstructions.end()){
		returnInstructions.push_back(**it);
		it++;
	}
	nextPc = programCounter;
	if(flush){
		// //cout<<"yahan bhi aaya pc != prevpc"<<endl;
				// //////cout<<"Branch taken and destination other than next instruction!"<<endl;
				// //////cout<<"Flush needed!"<<endl;
					/*setting stages free*/
		stages[0].setFree();
		stages[1].setFree();
		stages[2].setFree();
		// //cout<<"yo1"<<endl;
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
					if(!fastBranching){
						//cout<<"unstalling instruction id "<<(*it)->id<<endl;
						(*it)->unstall((*it)->id);
					}
					else
						it++;
					break;
				}
			}
			/*removing elements after the branch instructions from the queue*/
			while(it != currInstructions.end()){
				// //cout<<(*it)->id<<"::::::"<<(*it)->presentStage<<endl;
				currInstructions.erase(it++);
			}
		// //cout<<"yo4"<<endl;
		}
	// //cout<<"yahan se bahar aaya pc != prevpc"<<endl;
		it = currInstructions.begin() ;
		while(it != currInstructions.end()){
			if((*it)->stageToExecute==-1)
				currInstructions.erase(it++);
			else
				it++;
		}		
		it = currInstructions.begin();
	// //cout<<"ends up with ";
	/*while(it != currInstructions.end()){
		//cout<<(*it)->id<<", "<<(*it)->presentStage<<", "<<(*it)->stageToExecute<<" :: ";
		it++;
	}
	//cout<<endl;*/

	if(!programOver){

		if(stages[0].isFree()){
			// //cout<<"is ke ander aaya "<<endl;
			programCounter++;
			// //cout<<programCounter<<" <-- pc ab ye hai"<<endl;
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
	}
// Setting the stages free
	for(int i = 0 ; i < stages.size() ; i++)
		stages[i].setFree();
// clearing the sorted buckets for the next cycle
	for(int i = 1 ; i <= 9 ; i++ )
		sepInstructions[i].clear();
	// //////cout<<"cycle"<< endl;
	return returnInstructions;
}


void Program::executeAll(){

	while(!currInstructions.empty()){
		// //////cout<<currInstructions.front().id<<":"<<currInstructions.front().presentStage<<":"<<currInstructions.front().stageToExecute<<endl;
		list<Instruction *>::iterator it;
		//STABLE SORT
		for(it = currInstructions.begin() ; it != currInstructions.end() ; it++){
			sepInstructions[(*it)->stageToExecute].push_back(*it);
		}
		// the whole logic of running one clock cycle comes here
		for(int i = 10 ; i >= 1 ; i--){
			for(int j = 0 ; j < sepInstructions[i].size() ; j++){
				// //////cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<"--->";
				prevPc = programCounter;
				sepInstructions[i][j]->execute(programCounter);
				nextPc = programCounter;
				if(nextPc != prevPc){
					//////cout<<"Branch taken and destination other than next instruction!"<<endl;
					//////cout<<"Flush needed!"<<endl;
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
								(*it)->unstall((*it)->id); /*unstalling the register*/
								break;
							}
						}
						/*removing elements after the branch instructions from the queue*/
						while(it != currInstructions.end())
							currInstructions.erase(it++);
					}
				}
				// //////cout<<sepInstructions[i][j]->id<<":"<<sepInstructions[i][j]->presentStage<<":"<<sepInstructions[i][j]->stageToExecute<<endl;
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

		//////cout<<"cycle"<< endl;
	}
}
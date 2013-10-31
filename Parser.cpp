#include "Parser.h"
#include<cstring>
#include<cstdlib>
using namespace std;


void Parser::initMaps(){

    registerMap["$zero"] = 0;
    registerMap["$at"] = 1;
    registerMap["$v0"] = 2;
    registerMap["$v1"] = 3;
    registerMap["$a0"] = 4;
    registerMap["$a1"] = 5;
    registerMap["$a2"] = 6;
    registerMap["$a3"] = 7;
    registerMap["$t0"] = 8;
    registerMap["$t1"] = 9;
    registerMap["$t2"] = 10;
    registerMap["$t3"] = 11;
    registerMap["$t4"] = 12;
    registerMap["$t5"] = 13;
    registerMap["$t6"] = 14;
    registerMap["$t7"] = 15;
    registerMap["$s0"] = 16;
    registerMap["$s1"] = 17;
    registerMap["$s2"] = 18;
    registerMap["$s3"] = 19;
    registerMap["$s4"] = 20;
    registerMap["$s5"] = 21;
    registerMap["$s6"] = 22;
    registerMap["$s7"] = 23;
    registerMap["$t8"] = 24;
    registerMap["$t9"] = 25;
    registerMap["$k0"] = 26;
    registerMap["$k1"] = 27;
    registerMap["$gp"] = 28;
    registerMap["$sp"] = 29;
    registerMap["$fp"] = 30;
    registerMap["$ra"] = 31;

    instructionIntMap["add"] = 0;
    instructionIntMap["addi"] = 1;
    instructionIntMap["and"] = 2;
    instructionIntMap["andi"] = 3;
    instructionIntMap["or"] = 4;
    instructionIntMap["ori"] = 5;
    instructionIntMap["sub"] = 6;
    instructionIntMap["xor"] = 7;
    instructionIntMap["xori"] = 8;
    instructionIntMap["la"] = 9;
    instructionIntMap["li"] = 10;
    instructionIntMap["not"] = 11;
    instructionIntMap["syscall"] = 12;
    instructionIntMap["move"] = 13;

}

int Parser::convertToNumber(string str){
    int i = 0;
    for(int i=0; i<str.length(); i++){
        if(str[i] >='0' && str[i]<='9') i = i*10 + (str[i]-'0');
        else return 2147483644;
    }
    //check before returning to handle overflow
    return i;
}


Parser::Parser(string fileName){

    instructionNumber = 0;

    string str;
    ifstream infile;
    initMaps();
    infile.open(fileName.c_str());
    //string str1 = "la $a0, prompt1      #read the numbers, s0 contains the first number and s1 contains the second number";
    //parseLine(str1);
    while(getline(infile,str)){
        parseLine(str);
        //v.push_back(str);  

    }

    infile.close();
}

void Parser::printLabels(){
    cout<<endl<<"LABEL MAPPING"<<endl;
    map<string,int>::iterator it;
    for(it = labelMap.begin(); it!= labelMap.end(); it++){
        cout<<it->first<<" maps to "<<it->second<<endl;
    }
}


void Parser::parseLine(string str){
    lineWords.clear();
    char codeLine[200];
    strcpy(codeLine, str.c_str());

    char * curWord, * lastWord;
    curWord = strtok(codeLine, " ,\t");

    bool flag = false;
    if(curWord == NULL) return;
    int curLeng = strlen(curWord);

    if(curWord[0] == '#'){
            return;
    }

    string strTemp;
    
    if(curLeng > 1 && curWord[curLeng-1] == ':'){
        strTemp = curWord;
        labelMap[strTemp] = instructionNumber;
        //label detected
        //cout<<curWord<<endl<<endl<<endl<<endl;
        lastWord = curWord;
        curWord = strtok(NULL, ", \t");
    }

    while(curWord != NULL){
        //cout<<curWord<<endl;
        flag = true;
        //detect comments
        if(curWord[0] == '#'){
            makeInstruction();
            return;
        }
        if(curWord[0] == ':'){
            //last word was label
            //cout<<curWord<<endl<<endl<<endl<<endl;
            string strTemp = lastWord;
            strTemp += ':';
            labelMap[strTemp] = instructionNumber;
            lineWords.pop_back();
        }
        else{
            //cout<<curWord<<" ";
            strTemp = curWord;
            lineWords.push_back(strTemp);
        }
        lastWord = curWord;
        curWord = strtok(NULL, ", \t");
    }
    if(flag) cout<<endl;

    makeInstruction();

}

void Parser::syntaxError(){
    cout<<"SYNTAX ERROR!!"<<endl;
    exit(0);
}


void Parser::makeInstruction(){
    //cout<<lineWords[0]<<endl;
    //cout<<"hy"<<lineWords[0]<<"jl"<<endl;


    if(lineWords.empty()) { return;}
    cout<<instructionNumber<<" ";
    //cout<<"inst "<<lineWords[0]<<" inst type "<<instructionIntMap["add"]<<endl;
    int reg1, reg2, reg3;
    switch(instructionIntMap[lineWords[0]]){
        case 0:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                if(registerMap.find(lineWords[3]) != registerMap.end()){
                    reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                    cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
                }
                else{
                    //make instruction object and push it into vector
                    if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ADDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                    else syntaxError();
                }
                
            }
            else syntaxError();
            break;
        case 1:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ADDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 2:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;

                if(registerMap.find(lineWords[3]) != registerMap.end()){
                    reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                    cout<<"INSTRUCTION: "<<"AND "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
                }
                else{
                    //make instruction object and push it into vector
                    if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ANDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                    else syntaxError();
                }
                
            }
            else syntaxError();
            break;
        case 3:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ANDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 4:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;

                if(registerMap.find(lineWords[3]) != registerMap.end()){
                    reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                    cout<<"INSTRUCTION: "<<"OR "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
                }
                else{
                    //make instruction object and push it into vector
                    if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                    else syntaxError();
                }
                
            }
            else syntaxError();
            break;
        case 5:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"ORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 6:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;

                if(registerMap.find(lineWords[3]) != registerMap.end()){
                    reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                    cout<<"INSTRUCTION: "<<"SUB "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
                }
                else{
                    //make instruction object and push it into vector
                    if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"SUBI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                    else syntaxError();
                }
                
            }
            else syntaxError();
            break;
        case 7:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;

                if(registerMap.find(lineWords[3]) != registerMap.end()){
                    reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                    cout<<"INSTRUCTION: "<<"XOR "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
                }
                else{
                    //make instruction object and push it into vector
                    if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"XORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                    else syntaxError();
                }
                
            }
            else syntaxError();
            break;
        case 8:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644)cout<<"INSTRUCTION: "<<"XORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 9:
            //as of now la is only used to load values in register v0
            if(registerMap.find(lineWords[1]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[2]) != 2147483644)cout<<"INSTRUCTION: "<<"LA "<<reg1<<" "<<lineWords[2]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 10:
            if(registerMap.find(lineWords[1]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                //make instruction object and push it into vector
                if(convertToNumber(lineWords[2]) != 2147483644)cout<<"INSTRUCTION: "<<"LI "<<reg1<<" "<<lineWords[2]<<endl;
                else syntaxError();
            }
            else syntaxError();
            break;
        case 11:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                cout<<"INSTRUCTION: "<<"NOT "<<reg1<<" "<<reg2<<" "<<endl;
            }
            else syntaxError();
            break;
        case 12:
            cout<<"INSTRUCTION: SYSCALL"<<endl;
            break;
        case 13:
            if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
                reg1 = registerMap.find(lineWords[1])->second;
                reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
                cout<<"INSTRUCTION: "<<"MOVE "<<reg1<<" "<<reg2<<" "<<endl;
            }
            else syntaxError();
            break;
        default:
            syntaxError();
            break;
    }


    //at the end
    instructionNumber++;


}


/*
	how to handle instructions: pseudo code

    make a queue of instructions yet to be completed.
    Add first instruction to the queue.

    while program does not finish:
    traverse all instructions in the queue, from the front.

    Make another queue, for the next cycle.

    for each instr in the first queue, call execute function on the instruction object.
    if stage of instruction after execution is >0 then push to new queue.

    adding to queue: check if stage 0 is free, if yes, add new instruction to queue
    
    now set all the stages to free, and continue the traversal with second queue.

*/

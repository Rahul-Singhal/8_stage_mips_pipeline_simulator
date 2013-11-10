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
    instructionIntMap["exit"] = 12;
    instructionIntMap["move"] = 13;
    instructionIntMap["beq"] = 14;
    instructionIntMap["sw"] = 15;
    instructionIntMap["lw"] = 16;
    instructionIntMap["mult"] = 17;
    instructionIntMap["j"] = 18;
    instructionIntMap["lb"] = 19;
    instructionIntMap["sb"] = 20;
    instructionIntMap["slt"] = 21;
    instructionIntMap["slti"] = 22;
    instructionIntMap["sll"] = 23;
    instructionIntMap["sllv"] = 24;
    instructionIntMap["sra"] = 25;
    instructionIntMap["srav"] = 26;
    instructionIntMap["srl"] = 27;
    instructionIntMap["srlv"] = 28;
    instructionIntMap["nor"] = 29;
    instructionIntMap["jal"] = 30;



}

int Parser::convertToNumber(string str){
    int num = 0;
    int j = 0;
    if(str[0]=='-') j++;
    for(int i=j; i<str.length(); i++){
        if(str[i] >='0' && str[i]<='9') num = num*10 + (str[i]-'0');
        else return 2147483644;
    }
    //check before returning to handle overflow
    if(j == 0) return num;
    else return (-1*num);
}


Parser::Parser(string fileName, vector<Instruction *> & code){

    // codeVector = code;

    instructionNumber = 0;
    text = true;
    data = false;
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

    code = codeVector;
    cout << &code << endl;
    cout << code.size() << endl;
    infile.close();
}

vector<Instruction *> Parser::getVector(string fileName){
    instructionNumber = 0;
    text = true;
    data = false;
    string str;
    ifstream infile;
    initMaps();
    infile.open(fileName.c_str());
    //string str1 = "la $a0, prompt1      #read the numbers, s0 contains the first number and s1 contains the second number";
    //parseLine(str1);
    while(getline(infile,str)){
        // cout<<"Parsing line "<<str<<endl;
        parseLine(str);
    //v.push_back(str);  
    }

    
    infile.close();
    // cout<<"The size of vector before returning is "<<codeVector.size()<<endl;
    // exit(0);
    return codeVector;
}

Parser::Parser(){}
void Parser::printLabels(){
    ////cout<<endl<<"LABEL MAPPING"<<endl;
    map<string,int>::iterator it;
    for(it = labelMap.begin(); it!= labelMap.end(); it++){
        ////cout<<it->first<<" maps to "<<it->second<<endl;
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
    if (curWord[0] == '.'){
        if (strcmp(curWord, ".data") == 0){
            data = true;
            text = false;
            return;
        }
        else if (strcmp (curWord, ".text") == 0){
            data = false;
            text = true;
            return;
        }
        else if(strcmp(curWord, ".align") == 0){
            return;
        }
    }

    string strTemp;
    
    if (text){
        if(curLeng > 1 && curWord[curLeng-1] == ':'){
            strTemp = curWord;
            labelMap[strTemp.substr(0,strTemp.length()-1)] = instructionNumber;
            cout<<"LABEL ADDED!! "<<strTemp<<endl;
        //label detected
        //////cout<<curWord<<endl<<endl<<endl<<endl;
            lastWord = curWord;
            curWord = strtok(NULL, ", \t");
        }

        while(curWord != NULL){
        //////cout<<curWord<<endl;
            flag = true;
        //detect comments
            if(curWord[0] == '#'){
                makeInstruction();
                return;
            }
            if(curWord[0] == ':'){
            //last word was label
            //////cout<<curWord<<endl<<endl<<endl<<endl;
                string strTemp = lastWord;
                strTemp += ':';
                labelMap[strTemp] = instructionNumber;
                cout<<"LABEL ADDED AGAIN!! "<<strTemp<<endl;
                lineWords.pop_back();
            }
            else{
            //////cout<<curWord<<" ";
                strTemp = curWord;
                lineWords.push_back(strTemp);
            }
            lastWord = curWord;
            curWord = strtok(NULL, ", \t");
        }
        if(flag) ////cout<<endl;

        makeInstruction();
    }
    if (data){
        string dataName;
        string dataType;
        if(curLeng > 1 && curWord[curLeng-1] == ':'){
            strTemp = curWord;
            dataName = curWord;
            lastWord = curWord;
            curWord = strtok(NULL, ", \t");
        }
        if (curWord == NULL) {
            ////cout << "SYNTAX ERROR IN DATA";
            return;
        }
        dataType = curWord;
        if (dataType == ".ascii"){
            char* newascii = strtok(NULL,  "\"");
            newascii = strtok(NULL,  "\"");
            // dataMap[dataName] = mem.storeAscii(newascii);
            memory.storeAscii(dataName, newascii);
            //cout<<dataName<<" .ascii "<<newascii<<endl<<endl;
        }
        else if (dataType == ".asciiz"){
            char* newasciiz = strtok(NULL,  "\"");
            newasciiz = strtok(NULL,  "\"");
            // dataMap[dataName] = memory.storeAsciiz(newasciiz);
            memory.storeAsciiz(dataName,newasciiz);
            //cout<<dataName<<" .asciiz "<<newasciiz<<endl<<endl;
        }
        else if (dataType == ".word"){
            char* newint = strtok(NULL,  ", \t");
            vector <int> intVector;
            while (newint!=NULL){
                int integerValue = convertToNumber(newint);
                intVector.push_back(integerValue);
                newint = strtok(NULL,  " , \t");
            }
            // dataMap[dataName] = mem.storeWords(intVector);
            memory.storeWords(dataName,intVector);
            //cout<<dataName<<" .word ";
            //vector<int>  checkNum= wordTable[dataMap[dataName].second];
            for (int k = 0 ; k<intVector.size(); k++){
                //cout << intVector[k] << " " ;
            } 
            //cout << endl<<endl;
        }
        else if (dataType == ".space"){
            char* newSpace = strtok(NULL,  " \t");
            if(newSpace != NULL){
                int spaceValue = convertToNumber(newSpace);
                // dataMap[dataName] = mem.allocateSpace(spaceValue);
                memory.allocateSpace(dataName,spaceValue);
                //cout<<dataName<<" .space "<<spaceValue<<endl<<endl;
            }
            else{
                //cout<<"SYNTAX ERROR IN DATA!\n";
                exit(0);
            }
        }
        else if(dataType == ".byte"){
            vector<char> byteString;
            char* newByte = strtok(NULL,  ",' \t");
            while(newByte != NULL){
                if(strlen(newByte) == 1){
                    byteString.push_back(newByte[0]);
                    newByte = strtok(NULL, ",' \t");
                }
                else{
                    //cout<<"SYNTAX ERROR IN DATA!\n";
                    exit(0);
                }
            }
            // dataMap[dataName] = mem.storeBytes(byteString);
            memory.storeBytes(dataName,byteString);
            ////cout<<dataName<<" .byte "<<byteString<<endl<<endl;

        }

    }
}

void Parser::syntaxError(){
    cout<<"SYNTAX ERROR!!"<<endl;
    exit(0);
}


void Parser::makeInstruction(){
    //cout<<lineWords[0]<<endl;
    //////cout<<"hy"<<lineWords[0]<<"jl"<<endl;
    char displayString[100];

    if(lineWords.empty()) { return;}
    ////cout<<instructionNumber<<" ";
    //////cout<<"inst "<<lineWords[0]<<" inst type "<<instructionIntMap["add"]<<endl;
    int reg1, reg2, reg3;
    switch(instructionIntMap[lineWords[0]]){
        case 0:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                //Add * ins = new Add(reg1, reg2, reg3,0);
                codeVector.push_back(new Add(reg1, reg2, reg3,0));
                sprintf(displayString, "ADD $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                if(convertToNumber(lineWords[3]) != 2147483644){
                    //make instruction object and push it into vector
                    codeVector.push_back(new Addi(reg1, reg2, convertToNumber(lineWords[3]),0));
                    sprintf(displayString, "ADD $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"ADDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                }
                else syntaxError();
            }

        }
        else syntaxError();
        break;
        case 1:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(convertToNumber(lineWords[3]) != 2147483644){
                //make instruction object and push it into vector
                codeVector.push_back(new Addi(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "ADDI $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;*/
            }
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
                //UNCOMMENT
                codeVector.push_back(new And(reg1, reg2, reg3,0));
                sprintf(displayString, "AND $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"AND "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                if(convertToNumber(lineWords[3]) != 2147483644){
                    //make instruction object and push it into vector
                    //UNCOMMENT
                    codeVector.push_back(new Andi(reg1, reg2, convertToNumber(lineWords[3]),0));
                    sprintf(displayString, "AND $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"ANDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                }
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
            if(convertToNumber(lineWords[3]) != 2147483644){
                // UNCOMMENT
                codeVector.push_back(new Andi(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "ANDI $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ANDI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
        }
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
                //UNCOMMENT
                codeVector.push_back(new Or(reg1, reg2, reg3,0));
                sprintf(displayString, "OR $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"OR "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                    //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644){
                    //UNCOMMENT
                    codeVector.push_back(new Ori(reg1, reg2, convertToNumber(lineWords[3]),0));
                    sprintf(displayString, "OR $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"ORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                }
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
            if(convertToNumber(lineWords[3]) != 2147483644){
                //UNCOMMENT
                codeVector.push_back(new Ori(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "ORI $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 6:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;

            if(registerMap.find(lineWords[3]) != registerMap.end()){
                /*reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector*/
                codeVector.push_back(new Sub(reg1, reg2, reg3,0));
                sprintf(displayString, "SUB $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"SUB "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                    //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644){
                    //UNCOMMENT
                    // codeVector.push_back(new Subi(reg1, reg2, convertToNumber(lineWords[3]),0));
                    //cout<<"INSTRUCTION: "<<"SUBI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                }
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
                // reg3 = registerMap.find(lineWords[3])->second;
                    //make instruction object and push it into vector
                //UNCOMMENT
                codeVector.push_back(new Xor(reg1, reg2, reg3,0));
                sprintf(displayString, "XOR $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"XOR "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                    //make instruction object and push it into vector
                if(convertToNumber(lineWords[3]) != 2147483644){
                    // UNCOMMENT
                    codeVector.push_back(new Xori(reg1, reg2, convertToNumber(lineWords[3]),0));
                    sprintf(displayString, "XOR $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"XORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
                }
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
            if(convertToNumber(lineWords[3]) != 2147483644){
                //UNCOMMENT
                codeVector.push_back(new Xori(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "XORI $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"XORI "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 9:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
                //make instruction object and push it into vector
                // UNCOMMENT
                codeVector.push_back(new La(reg1, lineWords[2],0));
                sprintf(displayString, "LA $%d %s", reg1, lineWords[2].c_str());
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"LA "<<reg1<<" "<<lineWords[2]<<endl;
        }
        else syntaxError();
        break;
        case 10:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
                //make instruction object and push it into vector
            if(convertToNumber(lineWords[2]) != 2147483644){
                codeVector.push_back(new Li(reg1, convertToNumber(lineWords[2]),0));
                sprintf(displayString, "LI $%d %d", reg1, convertToNumber(lineWords[2]));
                codeVector.back()->display = displayString;
                // cout<<"INSTRUCTION: "<<"LI "<<reg1<<" "<<convertToNumber(lineWords[2])<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 11:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
            //UNCOMMENT
            codeVector.push_back(new Not(reg1, reg2,0));
            sprintf(displayString, "NOT $%d $%d", reg1, reg2);
            codeVector.back()->display = displayString;
            //cout<<"INSTRUCTION: "<<"NOT "<<reg1<<" "<<reg2<<" "<<endl;
        }
        else syntaxError();
        break;
        case 12:
        //UNCOMMENT
        codeVector.push_back(new Exit());
        sprintf(displayString, "EXIT");
        codeVector.back()->display = displayString;
        //cout<<"INSTRUCTION: SYSCALL"<<endl;
        break;
        case 13:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
            //UNCOMMENT
            codeVector.push_back(new Addi(reg1, reg2,0,0));
            sprintf(displayString, "MOVE $%d $%d", reg1, reg2);
            codeVector.back()->display = displayString;
            //cout<<"INSTRUCTION: "<<"MOVE "<<reg1<<" "<<reg2<<" "<<endl;
        }
        else syntaxError();
        break;
        case 14:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
                //make instruction object and push it into vector
            codeVector.push_back(new Beq(reg1, reg2, lineWords[3],0));
            sprintf(displayString, "BEQ $%d $%d %s", reg1, reg2, lineWords[3].c_str());
            codeVector.back()->display = displayString;
            //cout<<"INSTRUCTION: "<<"BEQ "<<reg1<<" "<<reg2<<" "<<lineWords[3]<<endl;
        }
        else syntaxError();
        break;

        case 15:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            char lword[50];
            strcpy(lword, lineWords[2].c_str());
            char * offset;
            char * address;
            if(lineWords[2][0] == '('){
                //sprintf(offset, "0");
                address = strtok(lword,"( )\t");
                codeVector.push_back(new Sw(reg1,address, 0,0));
                sprintf(displayString, "SW $%d (%s)", reg1, address);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"SW "<<reg1<<" "<<0<<" "<<address<<endl;
            }
            else{
                offset = strtok(lword,"( ");
                address = strtok(NULL, "( )\t");
                if(convertToNumber(offset) != 2147483644){
                    codeVector.push_back(new Sw(reg1,address, convertToNumber(offset),0));
                    sprintf(displayString, "SW $%d %d(%s)", reg1, convertToNumber(offset), address);
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"SW "<<reg1<<" "<<offset<<" "<<address<<endl;
                }
                else syntaxError();
            }
                //make instruction object and push it into vector
            
        }
        else syntaxError();
        break;

        case 16:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            char lword[50];
            strcpy(lword, lineWords[2].c_str());
            char * offset;
            char * address;
            if(lineWords[2][0] == '('){
                //sprintf(offset, "0");
                address = strtok(lword, "( )\t");
                codeVector.push_back(new Lw(reg1,address,0,0));
                sprintf(displayString, "LW $%d (%s)", reg1, address);
                codeVector.back()->display = displayString;
                // cout<<"INSTRUCTION: "<<"LW "<<reg1<<" "<<0<<" "<<address<<endl;
            }
            else{
                offset = strtok(lword, "( ");
                address = strtok(NULL, "( )\t");
                if(convertToNumber(offset) != 2147483644){
                    codeVector.push_back(new Lw(reg1,address, convertToNumber(offset),0));
                    sprintf(displayString, "LW $%d %d(%s)", reg1, convertToNumber(offset), address);
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"LW "<<reg1<<" "<<offset<<" "<<address<<endl;
                }
                else syntaxError();
            }
                //make instruction object and push it into vector
        }
        else syntaxError();
        break;

        case 17:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                    //make instruction object and push it into vector
                codeVector.push_back(new Mult(reg1,reg2,reg3,0));
                sprintf(displayString, "MULT $%d $%d $%d", reg1, reg2, reg3);
                cout<<"set the "<<displayString<<endl;
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"MULT "<<reg1<<" "<<reg2<<" "<<endl;
            }
            else syntaxError();

        }
        else syntaxError();
        break;

        case 18:
                //make instruction object and push it into vector
        //UNCOMMENT
        // codeVector.push_back(new J(lineWords[1],0));
        
        //cout<<"INSTRUCTION: "<<"J "<<lineWords[1]<<endl;
        break;

        case 19:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            char lword[50];
            strcpy(lword, lineWords[2].c_str());
            char * offset;
            char * address;
            if(lineWords[2][0] == '('){
                //sprintf(offset, "0");
                address = strtok(lword,"( )\t");
                //UNCOMMENT
                codeVector.push_back(new Lb(reg1,address, 0,0));
                sprintf(displayString, "LB $%d (%s)", reg1, address);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"LB "<<reg1<<" "<<0<<" "<<address<<endl;
            }
            else{
                offset = strtok(lword,"( ");
                address = strtok(NULL, "( )\t");
                if(convertToNumber(offset) != 2147483644){
                    //UNCOMMENT
                    codeVector.push_back(new Lb(reg1,address,convertToNumber(offset),0));
                    sprintf(displayString, "Lb $%d %d(%s)", reg1, convertToNumber(offset), address);
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"LB "<<reg1<<" "<<offset<<" "<<address<<endl;
                }
                else syntaxError();
            }
                //make instruction object and push it into vector
            
        }
        else syntaxError();
        break;

        case 20:
        if(registerMap.find(lineWords[1]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            char lword[50];
            strcpy(lword, lineWords[2].c_str());
            char * offset;
            char * address;
            if(lineWords[2][0] == '('){
                //sprintf(offset, "0");
                address = strtok(lword, "( )\t");
                //UNCOMMENT
                codeVector.push_back(new Sb(reg1,address,0,0));
                sprintf(displayString, "SB $%d (%s)", reg1,address);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"SB "<<reg1<<" "<<0<<" "<<address<<endl;
            }
            else{
                offset = strtok(lword, "( ");
                address = strtok(NULL, "( )\t");
                if(convertToNumber(offset) != 2147483644){
                    // UNCOMMENT
                    codeVector.push_back(new Sb(reg1,address,convertToNumber(offset),0));
                    sprintf(displayString, "SB $%d %d(%s)", reg1, convertToNumber(offset), address);
                    codeVector.back()->display = displayString;
                    //cout<<"INSTRUCTION: "<<"SB "<<reg1<<" "<<offset<<" "<<address<<endl;
                }
                else syntaxError();
            }
                //make instruction object and push it into vector
        }
        else syntaxError();
        break;

        case 21:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                //Add * ins = new Add(reg1, reg2, reg3,0);
                codeVector.push_back(new Slt(reg1, reg2, reg3,0));
                sprintf(displayString, "SLT $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"SLT "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else{
                if(convertToNumber(lineWords[3]) != 2147483644){
                    //make instruction object and push it into vector
                    codeVector.push_back(new Slti(reg1, reg2, convertToNumber(lineWords[3]),0));
                    sprintf(displayString, "SLT $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                    codeVector.back()->display = displayString;
                }
                else syntaxError();
            }

        }
        else syntaxError();
        break;
        case 22:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(convertToNumber(lineWords[3]) != 2147483644){
                //make instruction object and push it into vector

                codeVector.push_back(new Slti(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "SLTI $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
            }
            else syntaxError();
        }
        else syntaxError();
        break;

        case 23:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(convertToNumber(lineWords[3]) != 2147483644){
                //make instruction object and push it into vector
                codeVector.push_back(new Sll(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "SLL $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 24:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                codeVector.push_back(new Sllv(reg1, reg2, reg3,0));
                sprintf(displayString, "SLLV $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;

        case 25:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(convertToNumber(lineWords[3]) != 2147483644){
                //make instruction object and push it into vector
                codeVector.push_back(new Sra(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "SRA $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 26:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                codeVector.push_back(new Srav(reg1, reg2, reg3,0));
                sprintf(displayString, "SRAV $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;

        case 27:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()){
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(convertToNumber(lineWords[3]) != 2147483644){
                //make instruction object and push it into vector
                codeVector.push_back(new Srl(reg1, reg2, convertToNumber(lineWords[3]),0));
                sprintf(displayString, "SRL $%d $%d %d", reg1, reg2, convertToNumber(lineWords[3]));
                codeVector.back()->display = displayString;
            }
            else syntaxError();
        }
        else syntaxError();
        break;
        case 28:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                codeVector.push_back(new Srlv(reg1, reg2, reg3,0));
                sprintf(displayString, "SRLV $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else syntaxError();
        }
        else syntaxError();
        break;

        case 29:
        if(registerMap.find(lineWords[1]) != registerMap.end() && registerMap.find(lineWords[2]) != registerMap.end()) {
            reg1 = registerMap.find(lineWords[1])->second;
            reg2 = registerMap.find(lineWords[2])->second;
            if(registerMap.find(lineWords[3]) != registerMap.end()){
                reg3 = registerMap.find(lineWords[3])->second;
                codeVector.push_back(new Nor(reg1, reg2, reg3,0));
                sprintf(displayString, "NOR $%d $%d $%d", reg1, reg2, reg3);
                codeVector.back()->display = displayString;
                //cout<<"INSTRUCTION: "<<"ADD "<<reg1<<" "<<reg2<<" "<<reg3<<endl;
            }
            else syntaxError();
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


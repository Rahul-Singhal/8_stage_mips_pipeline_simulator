#include "Memory.h"
using namespace std;

Memory::Memory(){
  store.assign(1024, 'a');
  freePointer = 0;
}

void Memory::storeWord(int address, int word){
  //cout<<"STORING THE WORD "<<word<<endl;
  // ////cout << strlen(store) << endl;
  if (address+4 < store.size()){
    store[address+3] = word & 0xFF;
    store[address+2] = word & 0xFF00;
    store[address+1] = word & 0xFF0000;
    store[address] = word & 0xFF000000;
    // ////cout << (int)store[address+3] << endl;
  }
  else {
    store.resize(store.size()*2);
    storeWord(address, word);
  }
}


int Memory::loadWord(int address){
  if (address+4 <= store.size()){
    int Int32 = 0;
    Int32 = (Int32 << 8) + store[address];
    Int32 = (Int32 << 8) + store[address+1];
    Int32 = (Int32 << 8) + store[address+2];
    Int32 = (Int32 << 8) + store[address+3];
    return Int32;
  }
  else {
    ////cout << "word Out of Memory Bounds!" << endl; 
    return 0;    
  }
}

void Memory::storeByte(int address, char byte){
  //cout<<"STORING THE BYTE "<<byte<<endl;
  if (address+1 < store.size()){
    store[address] = byte; 
  }
  else {
    store.resize(store.size()*2);
    storeByte(address, byte);
  }
}

char Memory::loadByte(int address){
  if (address+1 <= store.size()){
    return store[address];
  }
  else {
    ////cout << "byte Out of Memory Bounds!" << endl; 
    return (char)0;
  }
}

int Memory::loadAddress(string label){
  return memoryMap[label].second;
}

int Memory::storeAscii(string label, string ascii){
  //cout<<"STRING THE ASCII "<<ascii<<endl;
  int place = freePointer;
  //cout<<"Label = "<<label<<" ascii = "<<ascii<<endl;
  if (freePointer+strlen(ascii.c_str()) < store.size()){
    int i = 0 ;
    while (i<strlen(ascii.c_str())){
      store[freePointer] = ascii[i];
      i++;
      freePointer++;
    }
    memoryMap[label] = make_pair(1, place);
    return place;
  }
  else {
    store.resize(store.size()*2);
    place = storeAscii(label, ascii);
    return place; 
  }
}

int Memory::storeAsciiz(string label, string asciiz){
  int place = freePointer;
  if (freePointer+strlen(asciiz.c_str()) < store.size()){
    int i = 0 ;
    while (i<strlen(asciiz.c_str())){
      store[freePointer] = asciiz[i];
      i++;
      freePointer++;
    }
    store[freePointer] = '\0';
    freePointer++;
    memoryMap[label] = make_pair(2, place);
    return place;
  }
  else {
    store.resize(store.size()*2);
    place = storeAsciiz(label, asciiz);
    return place;
  }

}

int Memory::storeBytes(string label, vector<char> v){
  int place = freePointer;
  if (freePointer + v.size() < store.size()){
    int i = 0 ;
    while (i < v.size()){
      storeByte(freePointer , v[i]);
      freePointer += 1;
      i++;
    }
    memoryMap[label] = make_pair(3, place);
    return place;
  }
  else {
    store.resize(store.size()*2);
    place = storeBytes(label, v);
    return place;
  }
}

int Memory::storeWords(string label, vector<int> v){
  int place = freePointer;
  if (freePointer + v.size()*4 < store.size()){
    int i = 0 ;
    while (i < v.size()){
      storeWord(freePointer , v[i]);
      freePointer += 4;
      i++;
    }
    memoryMap[label] = make_pair(7, place);
    return place;
  }
  else {
    store.resize(store.size()*2);
    place = storeWords(label, v);
    return place;
  }
}

int Memory::allocateSpace(string label, int count){
  //cout<<"ALLOCATING SPACE  "<<count<<endl;
  int place = freePointer;
  if (freePointer + count < store.size()){
    freePointer += count;
    memoryMap[label] = make_pair(8, place);
    return place;
  }
  else {
    store.resize(store.size()*2);
    place = allocateSpace(label, count);
    return place;
  }
}

string Memory::getString(int address){
  if (address < store.size()){
    int k = address;
    while (k< store.size()-1  && store[k] != '\0'){
      k++;
    }
    string str(store.begin()+address, store.begin()+k);
    ////cout << strlen(str.c_str()) << endl;
    return str;
  }
  else return "";
}
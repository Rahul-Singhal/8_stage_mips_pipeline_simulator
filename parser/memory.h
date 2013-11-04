#ifndef MEMORY_H
#define MEMORY_H
#include <vector>
#include <string>
using namespace std;

class Memory{
private:
	vector<char> memoryVector;	//make it an array if you want, overflow can be handled in both. 
								//array will give automatic errors and in case of vector you might have to check for overflow
public:
	Memory();
	//return the starting index in vector from where the storage started in each of the following methods.
	int storeAscii(char * ch);
	int storeAsciiz(char * ch);
	//arg is a vector of ints to store, manipulate and store a characters in the vector
	int storeWords(vector<int> v);
	int allocateSpace(int s);
	//arg is a string. Start from index 0 and store the consecutive characters in the array.
	int storeBytes(string s);

	//make some get and set functions to read bytes and words from and to the memory, given the input as memory address(index in array)
};

#endif
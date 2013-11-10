#include "Exit.h"


Exit::Exit(){

}

bool Exit::execute(int pc){
	programOver = true;
	return true;
}
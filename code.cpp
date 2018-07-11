#include <string>
#include "load.hpp"
#include "command.hpp"
#include "registerSet.hpp"
#include "instructionFetch.hpp"
#include "instructionDecode.hpp"
#include "execution.hpp"
#include "memoryAccess.hpp"
#include "writeBack.hpp"
#define size_t unsigned int

int main(int argc, char** argv) {
    registerSet rst; 
    std::string fileName = argv[1]; 
    size_t data, _text; 
    char* text = load(fileName, rst, data, _text); 
    instructionFetch IF(rst, text); 
    instructionDecode ID(rst); 
    execution EX(text); 
    memoryAccess MA(text, data); 
    writeBack WB(rst); 
    while (true) {
	if ((int)MA.data <= 0) {
	    for (size_t i = 0; i < _text; i += sizeof(command*)) 
		delete *(command**)(text + i); 
	    delete[] text; 
	    return -((int)MA.data); 
	}
	WB.work(); 
	MA.work(); 
	EX.work(); 
	ID.work(); 
	if (!ID.lock)
	    IF.work(); 
	MA >> WB; 
	EX >> MA; 
	ID >> EX; 
	if (!ID.lock)
	    IF >> ID; 
    }
}

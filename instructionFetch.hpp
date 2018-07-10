#ifndef _instructionFetch_hpp
#define _instructionFetch_hpp

#include <iostream>
#include "command.hpp"
#include "registerSet.hpp"
#include "instructionDecode.hpp"

class instructionFetch {

    private:

    registerSet* rst; 
    char* text; 

    public:
    
    bool lock; 
    command opt; 

    instructionFetch(registerSet& _rst, char* const& _text) {
	rst = &_rst; 
	text = _text; 
	opt.cmd = -1; 
    }

    void work() {
	lock = false; 
	if ((*rst).access[34]) {
	    lock = true; 
	    return; 
	}
	opt = **(command**)(text + (*rst)[34]); 
	(*rst)[34] += sizeof(command*); 
    }

    void operator >> (instructionDecode& ID) {
	ID.opt = opt; 
	if (lock)
	    ID.opt.cmd = -1; 
    }

}; 

#endif

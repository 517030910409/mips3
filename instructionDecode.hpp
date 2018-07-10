#ifndef _instructionDecode_hpp
#define _instructionDecode_hpp

#include "registerSet.hpp"
#include "command.hpp"
#include "execution.hpp"

class instructionDecode {
    
    private:

    registerSet* rst; 
    
    public:

    command opt; 
    bool lock; 

    instructionDecode(registerSet& _rst) {
	rst = &_rst; 
	lock = false; 
	opt.cmd = -1; 
    }

    void work() {
	lock = false; 
	switch (opt.cmd) {
	    case 0: case 1: case 2: case 3: case 4: case 5: case 8: case 9: case 12: case 13: case 16: case 17: case 19: case 20: case 21: case 22: case 23: case 24:
	    if ((*rst).access[opt.arg[1]] || (opt.src && (*rst).access[opt.arg[2]])) {
		lock = true; 
		break; 
	    }
	    opt.arg[1] = (*rst)[opt.arg[1]]; 
	    if (opt.src)
		opt.arg[2] = (*rst)[opt.arg[2]]; 
	    (*rst).access[opt.arg[0]]++; 
	    break; 

	    case 18:
	    (*rst).access[opt.arg[0]]++; 
	    break; 

	    case 6: case 7: case 10: case 11: 
	    if ((*rst).access[opt.arg[0]] || (*rst).access[opt.arg[1]]) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[opt.arg[0]]; 
	    opt.arg[1] = (*rst)[opt.arg[1]]; 
	    (*rst).access[32]++; 
	    (*rst).access[33]++; 
	    break; 
	    
	    case 14: case 15: case 42:
	    if ((*rst).access[opt.arg[1]]) {
		lock = true; 
		break; 
	    }
	    opt.arg[1] = (*rst)[opt.arg[1]]; 
	    (*rst).access[opt.arg[0]]++; 
	    break; 

	    case 25:
	    (*rst).access[34]++; 
	    break; 

	    case 26: case 27: case 28: case 29: case 30: case 31:
	    if ((*rst).access[opt.arg[0]] || (opt.src && (*rst).access[opt.arg[1]])) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[opt.arg[0]]; 
	    if (opt.src)
		opt.arg[1] = (*rst)[opt.arg[1]]; 
	    (*rst).access[34]++; 
	    break; 

	    case 32:
	    if ((*rst).access[opt.arg[0]]) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[opt.arg[0]]; 
	    (*rst).access[34]++; 
	    break; 

	    case 33:
	    (*rst).access[34]++; 
	    (*rst).access[31]++; 
	    break; 

	    case 34:
	    if ((*rst).access[opt.arg[0]]) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[opt.arg[0]]; 
	    (*rst).access[34]++; 
	    (*rst).access[31]++; 
	    break; 

	    case 35: case 36: case 37: case 38:
	    if (opt.src && (*rst).access[opt.arg[2]]) {
		lock = true; 
		break; 
	    }
	    if (opt.src)
		opt.arg[2] = (*rst)[opt.arg[2]]; 
	    (*rst).access[opt.arg[0]]++; 
	    break; 

	    case 39: case 40: case 41:
	    if ((*rst).access[opt.arg[0]] || (opt.src && (*rst).access[opt.arg[2]])) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[opt.arg[0]]; 
	    if (opt.src)
		opt.arg[2] = (*rst)[opt.arg[2]]; 
	    break; 

	    case 43:
	    if ((*rst).access[2] || (*rst).access[4] || (*rst).access[5]) {
		lock = true; 
		break; 
	    }
	    opt.arg[0] = (*rst)[2]; 
	    opt.arg[1] = (*rst)[4]; 
	    opt.arg[2] = (*rst)[5]; 
	    if (opt.arg[0] == 5 || opt.arg[0] == 9)
		(*rst).access[2]++; 
	    break; 

	    default:
	    break; 
	}
    }

    void operator >> (execution& EX) {
	EX.opt = opt; 
	if (lock)
	    EX.opt.cmd = -1; 
    }

}; 

#endif

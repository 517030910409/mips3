#ifndef _execution_hpp
#define _execution_hpp

#include <iostream>
#include "command.hpp"
#include "memoryAccess.hpp"
#define size_t unsigned int

class execution {
    
    private:

    char* text; 

    public:

    command opt; 

    execution(char* const& _text) {
	text = _text; 
	opt.cmd = -1; 
    }

    void work() {
	switch (opt.cmd) {
	    case 0:
	    opt.arg[1] = (int)opt.arg[1] + (int)opt.arg[2]; 
	    break; 
	    case 1:
	    opt.arg[1] = (size_t)opt.arg[1] + (size_t)opt.arg[2]; 
	    break; 
	    case 2:
	    opt.arg[1] = (int)opt.arg[1] - (int)opt.arg[2]; 
	    break; 
	    case 3:
	    opt.arg[1] = (size_t)opt.arg[1] - (size_t)opt.arg[2]; 
	    break; 
	    case 4:
	    opt.arg[1] = (int)opt.arg[1] * (int)opt.arg[2]; 
	    break; 
	    case 5:
	    opt.arg[1] = (size_t)opt.arg[1] * (size_t)opt.arg[2]; 
	    break; 
	    case 6:{
	    long long res = (long long)opt.arg[0] * (long long)opt.arg[1]; 
	    opt.arg[0] = res >> 32; 
	    opt.arg[1] = res << 32 >> 32; 
	    break; 
	    }
	    case 7:{
	    unsigned long long res = (unsigned long long)opt.arg[0] * (unsigned long long)opt.arg[1]; 
	    opt.arg[0] = res >> 32; 
	    opt.arg[1] = res << 32 >> 32; 
	    break; 
	    }
	    case 8:
	    opt.arg[1] = (int)opt.arg[1] / (int)opt.arg[2]; 
	    break; 
	    case 9:
	    opt.arg[1] = (size_t)opt.arg[1] / (size_t)opt.arg[2]; 
	    break; 
	    case 10:{
	    int res = (int)opt.arg[0] / (int)opt.arg[1]; 
	    opt.arg[0] = (int)opt.arg[0] % (int)opt.arg[1]; 
	    opt.arg[1] = res; 
	    break; 
	    }
	    case 11:{
	    size_t res = (size_t)opt.arg[0] / (size_t)opt.arg[1]; 
	    opt.arg[0] = (size_t)opt.arg[0] % (size_t)opt.arg[1]; 
	    opt.arg[1] = res; 
	    break; 
	    }
	    case 12: case 13:
	    opt.arg[1] = opt.arg[1] ^ opt.arg[2]; 
	    break; 
	    case 14:
	    opt.arg[1] = -(int)opt.arg[1]; 
	    break; 
	    case 15:
	    opt.arg[1] = ~opt.arg[1]; 
	    break; 
	    case 16:
	    opt.arg[1] = (int)opt.arg[1] % (int)opt.arg[2]; 
	    break; 
	    case 17:
	    opt.arg[1] = (size_t)opt.arg[1] % (size_t)opt.arg[2]; 
	    break; 
	    case 19:
	    opt.arg[1] = opt.arg[1] == opt.arg[2]; 
	    break; 
	    case 20:
	    opt.arg[1] = (int)opt.arg[1] >= (int)opt.arg[2]; 
	    break; 
	    case 21:
	    opt.arg[1] = (int)opt.arg[1] > (int)opt.arg[2]; 
	    break; 
	    case 22:
	    opt.arg[1] = (int)opt.arg[1] <= (int)opt.arg[2]; 
	    break; 
	    case 23:
	    opt.arg[1] = (int)opt.arg[1] < (int)opt.arg[2]; 
	    break; 
	    case 24:
	    opt.arg[1] = opt.arg[1] != opt.arg[2]; 
	    break; 
	    case 26:
	    opt.arg[0] = opt.arg[0] == opt.arg[1]; 
	    break; 
	    case 27:
	    opt.arg[0] = opt.arg[0] != opt.arg[1]; 
	    break; 
	    case 28:
	    opt.arg[0] = (int)opt.arg[0] >= (int)opt.arg[1]; 
	    break; 
	    case 29:
	    opt.arg[0] = (int)opt.arg[0] <= (int)opt.arg[1]; 
	    break; 
	    case 30:
	    opt.arg[0] = (int)opt.arg[0] > (int)opt.arg[1]; 
	    break; 
	    case 31:
	    opt.arg[0] = (int)opt.arg[0] < (int)opt.arg[1]; 
	    break; 
	    case 35: case 36: case 37: case 38: case 39: case 40: case 41:
	    if (opt.src)
		opt.arg[1] += opt.arg[2]; 
	    break; 
	    default:
	    break; 
	}
    }

    void operator >> (memoryAccess& MA) {
	MA.opt = opt; 
    }

}; 

#endif

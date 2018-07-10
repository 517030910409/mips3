#ifndef _writeBack_hpp
#define _writeBack_hpp

#include "command.hpp"
#include "registerSet.hpp"

class writeBack {
    
    private:

    registerSet* rst; 

    public:

    command opt; 

    writeBack(registerSet& _rst) {
	rst = &_rst; 
	opt.cmd = -1; 
    }

    void work() {
	switch (opt.cmd) {
	    case 0: case 1: case 2: case 3: case 4: case 5: case 8: case 9: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 35: case 36: case 37: case 38: case 42:
	    (*rst)[opt.arg[0]] = opt.arg[1]; 
	    (*rst).access[opt.arg[0]]--; 
	    break; 
	    case 6: case 7: case 10: case 11:
	    (*rst)[32] = opt.arg[0]; 
	    (*rst)[33] = opt.arg[1]; 
	    (*rst).access[32]--; 
	    (*rst).access[33]--; 
	    break; 
	    case 25: case 32:
	    (*rst)[34] = opt.arg[0]; 
	    (*rst).access[34]--; 
	    break; 
	    case 26: case 27: case 28: case 29: case 30: case 31:
	    if (opt.arg[0])
		(*rst)[34] = opt.arg[2]; 
	    (*rst).access[34]--; 
	    break; 
	    case 33: case 34:
	    (*rst)[31] = (*rst)[34]; 
	    (*rst)[34] = opt.arg[0]; 
	    (*rst).access[31]--; 
	    (*rst).access[34]--; 
	    break; 
	    case 43:
	    if (opt.arg[0] == 5 || opt.arg[0] == 9) {
		(*rst)[2] = opt.arg[1]; 
		(*rst).access[2]--; 
	    }
	    break; 
	    default:
	    break; 
	}
    }

}; 

#endif

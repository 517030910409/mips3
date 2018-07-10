#ifndef _memoryAccess_hpp
#define _memoryAccess_hpp

#include "command.hpp"
#include "writeBack.hpp"
#define size_t unsigned int
#define byte char
#define half short int
#define word int

class memoryAccess {
   
    private:
   
    char* text; 

    public:

    command opt; 
    size_t data; 

    memoryAccess(char* const& _text, const size_t& _data) {
	text = _text; 
	data = _data; 
	opt.cmd = -1; 
    }

    void work() {
	switch (opt.cmd) {
	    case 36:	   
	    opt.arg[1] = *(byte*)(text + opt.arg[1]); 
	    break; 
	    case 37:
	    opt.arg[1] = *(half*)(text + opt.arg[1]); 
	    break; 
	    case 38:
	    opt.arg[1] = *(word*)(text + opt.arg[1]); 
	    break; 
	    case 39:
	    *(byte*)(text + opt.arg[1]) = opt.arg[0]; 
	    break; 
	    case 40:
	    *(half*)(text + opt.arg[1]) = opt.arg[0]; 
	    break; 
	    case 41:
	    *(word*)(text + opt.arg[1]) = opt.arg[0]; 
	    break; 
	    case 43:
	    switch(opt.arg[0]) {
		case 1:
		std::cout << opt.arg[1]; 
		break; 
		case 4:
		while (true) {
		    char c = *(char*)(text + opt.arg[1]); 
		    opt.arg[1]++; 
		    if (c)
		        std::cout << c; 
		    else
		        break; 
		}
		break; 
		case 5:
		std::cin >> opt.arg[1]; 
		break; 
		case 8:{
		char st[opt.arg[2]]; 
		std::cin >> st; 
		for (size_t i = 0; i < opt.arg[2]; i++)
		    *(char*)(text + opt.arg[1] + i) = st[i]; 
		break; 
		}
		case 9:
		data += opt.arg[1]; 
		opt.arg[1] = data - opt.arg[1]; 
		break; 
		case 10:
		data = 0; 
		break; 
		case 17:
		data = -opt.arg[1]; 
		break; 
	    }
	    break; 
	    default:
	    break; 
	}
    }

    void operator >> (writeBack& WB) {
	WB.opt = opt; 
    }

}; 

#endif

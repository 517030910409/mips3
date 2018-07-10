#ifndef _registerSet_hpp
#define _registerSet_hpp

#include <string> 
#include <sstream>
#include <map>
#define size_t unsigned int

class registerSet {

    private:

    size_t tmp; 
    size_t rst[35]; 

    public:

    size_t access[35]; 
    std::map<std::string, size_t> search; 

    registerSet() {
	for (size_t i = 0; i < 35; i++) {
	    rst[i] = 0; 
	    access[i] = 0; 
	}
	search["$zero"] = 0; 
	search["$at"] = 1; 
	search["$v0"] = 2; 
	search["$v1"] = 3; 
	search["$a0"] = 4; 
	search["$a1"] = 5; 
	search["$a2"] = 6; 
	search["$a3"] = 7; 
	search["$t0"] = 8; 
	search["$t1"] = 9; 
	search["$t2"] = 10; 
	search["$t3"] = 11; 
	search["$t4"] = 12; 
	search["$t5"] = 13; 
	search["$t6"] = 14; 
	search["$t7"] = 15; 
	search["$s0"] = 16; 
	search["$s1"] = 17; 
	search["$s2"] = 18; 
	search["$s3"] = 19; 
	search["$s4"] = 20; 
	search["$s5"] = 21; 
	search["$s6"] = 22; 
	search["$s7"] = 23; 
	search["$t8"] = 24; 
	search["$t9"] = 25; 
	search["$s8"] = 26; 
	search["$s9"] = 27; 
	search["$gp"] = 28; 
	search["$sp"] = 29; 
	search["$fp"] = 30; 
	search["$ra"] = 31; 
	search["$hi"] = 32; 
	search["$lo"] = 33; 
	search["$pc"] = 34; 
	search["$0"] = 0; 
	search["$1"] = 1; 
	search["$2"] = 2; 
	search["$3"] = 3; 
	search["$4"] = 4; 
	search["$5"] = 5; 
	search["$6"] = 6; 
	search["$7"] = 7; 
	search["$8"] = 8; 
	search["$9"] = 9; 
	search["$10"] = 10; 
	search["$11"] = 11; 
	search["$12"] = 12; 
	search["$13"] = 13; 
	search["$14"] = 14; 
	search["$15"] = 15; 
	search["$16"] = 16; 
	search["$17"] = 17; 
	search["$18"] = 18; 
	search["$19"] = 19; 
	search["$20"] = 20; 
	search["$21"] = 21; 
	search["$22"] = 22; 
	search["$23"] = 23; 
	search["$24"] = 24; 
	search["$25"] = 25; 
	search["$26"] = 26; 
	search["$27"] = 27; 
	search["$28"] = 28; 
	search["$29"] = 29; 
	search["$30"] = 30; 
	search["$31"] = 31; 
    }

    size_t& operator[](const size_t& pos) {
	return rst[pos]; 
    }

    size_t operator[](const size_t& pos) const {
	return rst[pos]; 
    }

}; 

#endif

#ifndef _command_hpp
#define _command_hpp

#include <string>
#include <iostream>
#include "labelMap.hpp"
#include "registerSet.hpp"
#define size_t unsigned int
#define byte char
#define half short int
#define word int

class command {

    public:

    size_t cmd; 
    int arg[3]; 
    bool src; 
    // true for register
    // false for imm or label

    size_t dealRegister(const std::string& pos, const registerSet& rst) {
	return rst.search.at(pos); 
    }

    void load(const std::string& opt, std::istringstream& iarg, const labelMap& label, const registerSet& rst) {
	std::string a1, a2, a3; 
	iarg >> a1 >> a2 >> a3; 
	if (a1.length() && a1[a1.length() - 1] == ',')	a1.pop_back(); 
	if (a2.length() && a2[a2.length() - 1] == ',')	a2.pop_back(); 
	if (a3.length() && a3[a3.length() - 1] == ',')	a3.pop_back(); 
	if (opt == "add" || opt == "addu" || opt == "sub" || opt == "subu" || (opt == "mul" && a3.length()) || (opt == "mulu" && a3.length()) || (opt == "div" && a3.length()) || (opt == "divu" && a3.length()) || opt == "xor" || opt == "xoru" || opt == "rem" || opt == "remu" || opt == "seq" || opt == "sge" || opt == "sgt" || opt == "sle" || opt == "slt" || opt == "sne") {
	    arg[0] = dealRegister(a1, rst); 
	    arg[1] = dealRegister(a2, rst); 
	    if (a3[0] == '$') {
		arg[2] = dealRegister(a3, rst); 
		src = true; 
	    } else {
		std::istringstream istr(a3); 
		istr >> arg[2]; 
		src = false; 
	    }
	}
	if ((opt == "mul" && a3.length() == 0) || (opt == "mulu" && a3.length() == 0) || (opt == "div" && a3.length() == 0) || (opt == "divu" && a3.length() == 0) || opt == "neg" || opt == "negu" || opt == "li" || opt == "move") {
	    arg[0] = dealRegister(a1, rst); 
	    if (a2[0] == '$') {
		arg[1] = dealRegister(a2, rst); 
		src = true; 
	    } else {
		std::istringstream istr(a2); 
		istr >> arg[1]; 
		src = false; 
	    }
	}
	if (opt == "b" || opt == "j" || opt == "jal")
	    arg[0] = label[a1]; 
	if (opt == "beq" || opt == "bne" || opt == "bge" || opt == "ble" || opt == "bgt" || opt == "blt") {
	    arg[0] = dealRegister(a1, rst); 
	    if (a2[0] == '$') {
		arg[1] = dealRegister(a2, rst); 
		src = true; 
	    } else {
		std::istringstream istr(a2); 
		istr >> arg[1]; 
		src = false; 
	    }
	    arg[2] = label[a3]; 
	}
	if (opt == "beqz" || opt == "bnez" || opt == "bgez" || opt == "blez" || opt == "bgtz" || opt == "bltz") {
	    arg[0] = dealRegister(a1, rst); 
	    arg[1] = 0; 
	    src = false; 
	    arg[2] = label[a2]; 
	}
	if (opt == "jr" || opt == "jalr") 
	    arg[0] = dealRegister(a1, rst); 
	if (opt == "mfhi") {
	    arg[0] = dealRegister(a1, rst); 
	    arg[1] = 32; 
	}
	if (opt == "mflo") {
	    arg[0] = dealRegister(a1, rst); 
	    arg[1] = 33; 
	}
	if (opt == "la" || opt == "lb" || opt == "lh" || opt == "lw" || opt == "sb" || opt == "sh" || opt == "sw") {
	    arg[0] = dealRegister(a1, rst); 
	    if (label.exist(a2)) {
		arg[1] = label[a2]; 
		src = false; 
	    } else {
		std::istringstream istr(a2); 
		istr >> arg[1]; 
		char trash; 
		istr >> trash >> a2; 
		a2.pop_back(); 
		arg[2] = dealRegister(a2, rst); 
		src = true; 
	    }
	}
	if (opt == "add")   cmd = 0; 
	if (opt == "addu")  cmd = 1; 
	if (opt == "sub")   cmd = 2; 
	if (opt == "subu")  cmd = 3; 
	if (opt == "mul") {
	    if (a3.length())	cmd = 4; 
	    else    cmd = 6; 
	}
	if (opt == "mulu") {
	    if (a3.length())	cmd = 5; 
	    else    cmd = 7; 
	}
	if (opt == "div") {
	    if (a3.length())	cmd = 8; 
	    else    cmd = 10; 
	}
	if (opt == "divu") {
	    if (a3.length())	cmd = 9; 
	    else    cmd = 11; 
	}
	if (opt == "xor")   cmd = 12; 
	if (opt == "xoru")  cmd = 13; 
	if (opt == "neg")   cmd = 14; 
	if (opt == "negu")  cmd = 15; 
	if (opt == "rem")   cmd = 16; 
	if (opt == "remu")  cmd = 17; 
	if (opt == "li")    cmd = 18; 
	if (opt == "seq")   cmd = 19; 
	if (opt == "sge")   cmd = 20; 
	if (opt == "sgt")   cmd = 21; 
	if (opt == "sle")   cmd = 22; 
	if (opt == "slt")   cmd = 23; 
	if (opt == "sne")   cmd = 24; 
	if (opt == "b" || opt == "j")	cmd = 25; 
	if (opt == "beq" || opt == "beqz")  cmd = 26; 
	if (opt == "bne" || opt == "bnez")  cmd = 27; 
	if (opt == "bge" || opt == "bgez")  cmd = 28; 
	if (opt == "ble" || opt == "blez")  cmd = 29; 
	if (opt == "bgt" || opt == "bgtz")  cmd = 30; 
	if (opt == "blt" || opt == "bltz")  cmd = 31; 
	if (opt == "jr")    cmd = 32; 
	if (opt == "jal")   cmd = 33; 
	if (opt == "jalr")  cmd = 34; 
	if (opt == "la")    cmd = 35; 
	if (opt == "lb")    cmd = 36; 
	if (opt == "lh")    cmd = 37; 
	if (opt == "lw")    cmd = 38; 
	if (opt == "sb")    cmd = 39; 
	if (opt == "sh")    cmd = 40; 
	if (opt == "sw")    cmd = 41; 
	if (opt == "move" || opt == "mfhi" || opt == "mflo")	cmd = 42; 
	if (opt == "syscall")	cmd = 43; 
    }

}; 

#endif

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
    //freopen("code.in", "r", stdin);
    //freopen("code.out","w",stdout);
    registerSet rst; 
    std::string fileName = argv[1]; 
    //std::string fileName; 
    //std::cin >> fileName; 
    size_t data; 
    char* text = load(fileName, rst, data); 
    instructionFetch IF(rst, text); 
    instructionDecode ID(rst); 
    execution EX(text); 
    memoryAccess MA(text, data); 
    writeBack WB(rst); 
    while (true) {
	if ((int)MA.data <= 0) {
	    return -((int)MA.data); 
	}
	WB.work(); 
	MA.work(); 
	EX.work(); 
	ID.work(); 
	if (!ID.lock)
	    IF.work(); 
	//std::cout << "IF:" << IF.lock << ' ' << IF.opt.cmd << ' ' << IF.opt.arg[0] << ' ' << IF.opt.arg[1] << ' ' << IF.opt.arg[2] << '\n'; 	std::cout << "ID:" << ID.lock << ' ' << ID.opt.cmd << ' ' << ID.opt.arg[0] << ' ' << ID.opt.arg[1] << ' ' << IF.opt.arg[2] << '\n'; 	std::cout << "EX:" << "  " << EX.opt.cmd << ' ' << EX.opt.arg[0] << ' ' << EX.opt.arg[1] << ' ' << IF.opt.arg[2] << '\n'; 	std::cout << "MA:" << "  " << MA.opt.cmd << ' ' << MA.opt.arg[0] << ' ' << MA.opt.arg[1] << ' ' << MA.opt.arg[2] << '\n'; 	std::cout << "WB:" << "  " << WB.opt.cmd << ' ' << WB.opt.arg[0] << ' ' << WB.opt.arg[1] << ' ' << WB.opt.arg[2] << '\n'; 
	MA >> WB; 
	EX >> MA; 
	ID >> EX; 
	if (!ID.lock)
	    IF >> ID; 
    }
}

#ifndef _load_hpp
#define _load_hpp

#include <string>
#include <fstream>
#include "command.hpp"
#include "labelMap.hpp"
#define FOUR_M (1 << 22)
#define size_t unsigned int
#define byte char
#define half short int
#define word int

void addCommand(char* const& text, size_t cnt, const std::string& opt, std::istringstream& arg, const labelMap& label, const registerSet& rst) {
    command* address = new command; 
    address -> load(opt, arg, label, rst); 
    *(command**)(text + cnt) = address; 
}

size_t loadText(const std::string& fileName, char* const& text, labelMap& label, const registerSet& rst) {
    std::ifstream file(fileName); 
    std::string str; 
    size_t cnt = sizeof(command*) * 2; 
    bool load = false; 
    while (getline(file, str)) {
	std::istringstream istr(str); 
	std::string opt; 
	istr >> opt; 
	if (opt == ".data") load = false; 
	if (opt == ".text") load = true; 
	if (load && opt != ".text" && opt.length() && opt != "nop") {
	    if (opt[opt.length() - 1] == ':') {
		label[opt] = cnt; 
		continue; 
	    }
	    cnt += sizeof(command*); 
	}
    }
    return cnt; 
}

void loadData(const std::string& fileName, char* const&text, size_t& cnt, labelMap& label) {
    std::ifstream file(fileName); 
    std::string str; 
    bool load = false; 
    while (getline(file, str)) {
	std::istringstream istr(str); 
	std::string opt; 
	istr >> opt; 
	if (opt == ".text") load = false; 
	if (opt == ".data") load = true; 
	if (load && opt != ".data" && opt.length()) {
	    if (opt[opt.length() - 1] == ':') {
		label[opt] = cnt; 
		continue; 
	    }
	    if (opt == ".align") {
		size_t n; 
		istr >> n; 
		n = (1 << n); 
		if (cnt % n) {
		    cnt /= n; 
		    cnt++; 
		    cnt *= n; 
		}
	    }
	    if (opt == ".ascii") {
		std::string st; 
		getline(istr, st); 
		for (size_t i = 2; i < st.length() - 1; i++) {
		    if (st[i] == '\\') {
			i++; 
			if (st[i] == 'n')
			    *(text + cnt) = '\n'; 
			if (st[i] == '"')
			    *(text + cnt) = '\"'; 
			if (st[i] == '\\')
			    *(text + cnt) = '\\'; 
		    } else 
			*(text + cnt) = st[i]; 
		    cnt++; 
		}
	    }
	    if (opt == ".asciiz") {
		std::string st; 
		getline(istr, st); 
		for (size_t i = 2; i < st.length() - 1; i++) {
		    if (st[i] == '\\') {
			i++; 
			if (st[i] == 'n')
			    *(text + cnt) = '\n'; 
			if (st[i] == '"')
			    *(text + cnt) = '\"'; 
			if (st[i] == '\\')
			    *(text + cnt) = '\\'; 
		    } else 
			*(text + cnt) = st[i]; 
		    cnt++; 
		}
		*(text + cnt) = 0; 
		cnt++; 
	    }
	    if (opt == ".byte") {
		byte b; 
		while (istr >> b) {
		    *((byte*)(text + cnt)) = b; 
		    cnt += sizeof(byte); 
		}
	    }
	    if (opt == ".half") {
		half h; 
		while (istr >> h) {
		    *((half*)(text + cnt)) = h; 
		    cnt += sizeof(half); 
		}
	    }
	    if (opt == ".word") {
		word w; 
		while (istr >> w) {
		    *((word*)(text + cnt)) = w; 
		    cnt += sizeof(word); 
		}
	    }
	    if (opt == ".space") {
		size_t n; 
		istr >> n; 
		cnt += n; 
	    }
	}
    }
}

void dealText(const std::string& fileName, char* const&text, const labelMap& label, const registerSet& rst) {
    std::ifstream file(fileName); 
    size_t cnt = 0; 
    std::ostringstream ostr; 
    ostr << "$29 " << FOUR_M - 1; 
    std::istringstream istr1(ostr.str()); 
    addCommand(text, cnt, "li", istr1, label, rst); 
    cnt += sizeof(command*); 
    std::istringstream istr2("main"); 
    addCommand(text, cnt, "j", istr2, label, rst); 
    cnt += sizeof(command*); 
    std::string str; 
    bool load = false; 
    while (getline(file, str)) {
	std::istringstream istr(str); 
	std::string opt; 
	istr >> opt; 
	if (opt == ".data") load = false; 
	if (opt == ".text") load = true; 
	if (load && opt != ".text" && opt.length() && opt[opt.length() - 1] != ':' && opt != "nop") {
	    addCommand(text, cnt, opt, istr, label, rst); 
	    cnt += sizeof(command*); 
	}
    }
}

char* load(const std::string& fileName, const registerSet& rst, size_t& data, size_t& _text) {
    char* text = new char[FOUR_M]; 
    labelMap label; 
    data = loadText(fileName, text, label, rst); 
    _text = data; 
    loadData(fileName, text, data, label); 
    dealText(fileName, text, label, rst); 
    return text; 
}

#endif

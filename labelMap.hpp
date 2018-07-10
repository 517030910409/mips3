#ifndef _labelMap_hpp
#define _labelMap_hpp

#include <map>
#include <string>
#define size_t unsigned int

class labelMap {

    private:

    std::map<std::string, size_t> lbl; 

    public:

    bool exist(std::string labelName) const {
	if (labelName[labelName.length() - 1] ^ ':')	labelName += ":"; 
	return lbl.find(labelName) != lbl.end(); 
    }

    size_t& operator[](std::string labelName) {
	if (labelName[labelName.length() - 1] ^ ':')	labelName += ":"; 
	return lbl[labelName]; 
    }

    const size_t& operator[](std::string labelName) const {
	if (labelName[labelName.length() - 1] ^ ':')	labelName += ":"; 
	return lbl.at(labelName); 
    }

}; 

#endif

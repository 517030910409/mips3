cc = g++
prog = code
($prog) : code.cpp
	g++ code.cpp -o code -std=c++11 -O2
clean :
	rm -rf code

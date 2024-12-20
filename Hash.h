#pragma once
#include <algorithm>
#include<string>
#include "dfa.h"
#include"token.h"
#include <fstream>
using std::ofstream;
class Hash {
private:
	int size;
	token* Mas;
	int function(string s);
public:
	Hash();
	Hash(int size);
	void push_back(token x);
	void vivod(ofstream& fon);
	void push_all(lexer& a);
	string find(string s);
	token operator[](int i);
	
};

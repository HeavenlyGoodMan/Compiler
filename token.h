#pragma once
#include<string>
using std::string;
class token {
public:
	string type;
	string lexem;
	friend class lexer;
	friend class Hash;
	token(string type, string lexem) :type(type), lexem(lexem) {};
	token();
	string getlex();
	string getType();
};

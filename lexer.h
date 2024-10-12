#pragma once
#include <algorithm>
#include<string>
#include "dfa.h"
#include "nfa.h"
#include"token.h"
#include <fstream>
using std::string;
using std::ofstream;
using std::vector;

class lexer
{
private:
	int pos=0;
	dfa Avtomat;
	string text;
	std::vector<token> Musor;
public:
	lexer(int pos, string text);
	token GetToken();
	token nextLex();
	std::vector<token> get_all(int i);
	void vivodMus(ofstream& fon);
	int getsize();
	int getpos();
	void setpos(int i);
};

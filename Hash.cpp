#include "Hash.h"
#include"lexer.h"
#include<fstream>
Hash::Hash()
{
	Mas = new token[9973];
	size = 9973;
}
int Hash::function(string s)
{
	int sum = 0;
	for (int i = 0; i <s.size(); ++i) {
		sum += (s[i] + i * 255);
	}
	return (sum%size);
}
Hash::Hash(int size)
{
	Mas = new token[size];
	size = size;
}

void Hash::push_back(token x)
{	
	int pos, i1=0,s=0;
	s = this->function(x.lexem);
	while (true) {
		pos = s + i1;
		pos %= size;
		if (Mas[pos].lexem == "" || Mas[pos].lexem==x.lexem) {
			Mas[pos] = x;
			break;
		}
		++i1;
	}
}
void Hash::vivod(ofstream& fon) {
	for (int i = 0; i < size; ++i) {
		if (Mas[i].lexem != "") {
			fon << Mas[i].type << " | " << Mas[i].lexem << " | " << i << std::endl;
		}
	}
}
void Hash::push_all(lexer& a) {
	token b;
	while(a.getpos()!=a.getsize()){
		b = a.nextLex();
		if (b.type != "ErrorLex") {
			this->push_back(b);
		}
	}
}
int Hash::find(string s) {
	int pos, i1 = 0, sum = 0;
	sum = this->function(s);
	while (true) {
		pos = sum + i1;
		pos %= size;
		if (Mas[pos].lexem == "") {
			return -1;
		}
		if (s==Mas[pos].lexem) {
			return pos;
		}
		++i1;
		if (i1 == size) {
			return -1;
		}
	}
}
token Hash::operator[](int i) {
	if (i == -1) {
		return token("","Error");
	}
	return Mas[i];
}


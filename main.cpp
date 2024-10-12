#include <iostream>
#include<vector>
#include"dfa.h"
#include"nfa.h"
#include"lexer.h"
#include"hash.h"
#include<fstream>
using namespace std;
int main() {
	string s;
	ifstream fin("input.txt");
	string text = "";
	while (!fin.eof()) {
		getline(fin, s);
		text += s+" ";
	}
	cout << text << endl;

	lexer lex(0, text);
	Hash H;
	ofstream fon("output.txt");
	H.push_all(lex);
	//cout << H[H.find(";")].getlex();
	H.vivod(fon);
	lex.vivodMus(fon);
}
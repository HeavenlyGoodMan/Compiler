#include <iostream>
#include<vector>
#include"dfa.h"
#include"nfa.h"
#include"lexer.h"
#include"hash.h"
#include "SynAnal.h"
#include<fstream>
using namespace std;
int main() {
	string s;
	ifstream fin("input.txt");
	ofstream tree("tree.txt");
	string text = "";
	while (!fin.eof()) {
		getline(fin, s);
		text += s+" ";
	}
	lexer lex(0, text);
	SynAnal A(lex);
	A.Analysis(tree);

	/*for (int i = 0; i < A.koren.children.size(); ++i) {
		cout << (*(A.koren.children[i])).str << " ";
	}*/
	//lexer lex(0, text);
	//Hash H;
	//ofstream fon("output.txt");
	//H.push_all(lex);
	////cout << H[H.find(";")].getlex();
	//H.vivod(fon);
	//lex.vivodMus(fon);
}
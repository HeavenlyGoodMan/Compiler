#include "lexer.h"
#include<fstream>
lexer::lexer(int pos, string text):pos(pos), text(text) {
	string s = "(){},;0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM+-<>=!";
	vector<char> alfa(s.size());
	for (int i = 0; i < s.size(); ++i) {
		alfa[i] = s[i];
	}
	vector<int> fstate(6);
	fstate[0] = 1;
	fstate[1] = 2;
	fstate[2] = 5;
	fstate[3] = 11;
	fstate[4] = 18;
	fstate[5] = 19;
	vector<vector<vector<int>>> A(20, vector<vector<int>>(s.size()));
	for (int i = 0; i < 6; ++i) {
		A[0][i].push_back(1);
	}
	for (int i = 7; i < 16; ++i) {
		A[0][i].push_back(5);
	}
	for (int i = 68; i < 73; ++i) {
		A[0][i].push_back(2);
	}
	for (int i = 70; i < 74; ++i) {
		A[0][i].push_back(3);
	}
	A[0][6].push_back(19);
	A[0][17].push_back(14);
	A[0][23].push_back(12);
	A[0][19].push_back(6);
	for (int i = 16; i < 68; ++i) {
		A[0][i].push_back(18);
	}
	A[0][69].push_back(4);
	for (int i = 16; i < 68; ++i) {
		A[18][i].push_back(18);
	}
	A[3][72].push_back(2);

	for (int i = 7; i < 16; ++i) {
		A[4][i].push_back(5);
	}
	for (int i = 6; i < 16; ++i) {
		A[5][i].push_back(5);
	}
	A[6][18].push_back(7);
	A[7][20].push_back(8);
	A[8][22].push_back(9);
	A[9][19].push_back(10);
	A[10][40].push_back(11);
	A[12][40].push_back(13);
	A[13][20].push_back(11);
	A[14][31].push_back(15);
	A[15][23].push_back(16);
	A[16][34].push_back(17);
	A[17][18].push_back(11);
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < s.size(); ++j) {
			if (A[i][j].size() == 0) {
				A[i][j].push_back(-1);
			}
		}
	}
	nfa myNfa(20, alfa, fstate, A);
	dfa myDfa = myNfa.createDFA();
	vector<string> Type(21);
	for (int i = 4; i < 8; ++i) {
		Type[i] = "ID";
	}
	for (int i = 12; i < 21; ++i) {
		Type[i] = "ID";
	}
	for (int i = 8; i < 11; ++i) {
		Type[i] = "OP";
	}
	Type[1] = "SEP";
	Type[2] = "CONST";
	Type[3] = "CONST";
	Type[17] = "KEY_WORLD";
	myDfa.TypeFinal = Type;
	Avtomat = myDfa;
};
token lexer::GetToken()
{
	int state = 0;
	char c;
	bool l = 1;
	string lex = "", type = "ErrorLex";
	for (int i = pos; i < text.size(); ++i)
	{
		c = text[i];
		if (c == ' ') {
			l += ' ';
			break;
		}
		if (l == 1) {
			state = Avtomat.getState(state, c);
		}
		if (state == -1)
			l = 0;
		lex += c;
	}
	if (std::find(Avtomat.finalStates.begin(), Avtomat.finalStates.end(), state) != Avtomat.finalStates.end()) {
		return token(Avtomat.TypeFinal[(*find(Avtomat.finalStates.begin(), Avtomat.finalStates.end(), state))], lex);
	}
	return token(type, lex);
}
token lexer::nextLex()
{  
    while (text[pos] == ' ') {
        pos++;
    }
    if (pos == text.size()) {
        return token("Error", "");
    }
	token a = this->GetToken();
    if (a.type == "ErrorLex") {
        Musor.push_back(a);
    }
    pos += (a.lexem.size());
    return a;
}

void lexer::vivodMus(ofstream& fon)
{
    for (int i = 0; i < Musor.size(); ++i) {
        fon << Musor[i].type << " " << Musor[i].lexem << std::endl;
    }
}

int lexer::getsize()
{
    return text.size();
}

int lexer::getpos()
{
    return pos;
}

void lexer::setpos(int i)
{
	pos = i;
}



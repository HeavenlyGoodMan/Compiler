#pragma once
#include "lexer.h"
#include <iostream>
using namespace std;

struct Node {
	string str="";
	vector<Node*> children;
	Node(string t) : str(t){}
	Node() = default;
	void vivod(string s, ofstream& tree);
};

class SynAnal {
private:
	lexer lex;
	Node koren;
	bool l = 1;
	void Begin(token& a, Node& n);
	void End(token& a, Node& n);
	void FunName(token& a, Node& n);
	void Description(token& a, Node& n);
	void Op_s(token& a, Node& n);
	void Descr(token& a, Node& n);
	void VarList(token& a, Node& n);
	void VarList_2(token& a, Node& n);
	void Type(token& a, Node& n);
	void Op(token& a, Node& n);
	void SimpleExpr(token& a, Node& n);
	void Expr(token& a, Node& n);
	void Condition(token& a, Node& n);
	void RelationOp(token& a, Node& n);
	void ID(token& a, Node& n);
	void Const(token& a, Node& n);
public:
	SynAnal(lexer lex_) : lex(lex_) {}
	void Analysis(ofstream& tree);
};
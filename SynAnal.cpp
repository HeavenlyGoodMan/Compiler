#include "SynAnal.h"

void SynAnal::Analysis(ofstream& tree)
{	
	koren.str = "Function";
	token a = lex.nextLex();
	Begin(a, koren);
	Description(a, koren);
	op = 1;
	Op_s(a, koren);
	End(a, koren);
	for (int i = 0; i < koren.children.size();++i) {
		koren.tr += koren.children[i]->tr+"\n";
	}
	if (l == 1 && lex.getpos()>=lex.getsize()) {
		cout << "Completed analysis"<<endl;
		koren.vivod("",tree);
	}
	else {
		cout << "Uncompleted analysis" << endl;
		if (l==1 && lex.getpos() < lex.getsize()) {
			cout << "Went beyond the end";
		}
	}
	out << koren.tr;
}

void SynAnal::Begin(token& a, Node& n)
{	
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Begin");
	Type(a, *n.children[n.children.size() - 1]);
	FunName(a, *n.children[n.children.size() - 1]);
	if (a.lexem == "(") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size()-1] = new Node("(");
		a = lex.nextLex();
		if (a.lexem == ")") {
			(n.children[n.children.size() - 1])->children.push_back(nullptr);
			n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(")");
			a = lex.nextLex();
			if (a.lexem == "{") {
				(n.children[n.children.size() - 1])->children.push_back(nullptr);
				n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node("{");
				a = lex.nextLex();
			}
			else if (l) {
				cout << "Errror: expected '{', incoming lexem '"<<a.lexem<<"' (place "<<lex.getpos()<<")" << endl;
				l = 0;
				return;
			}
		}
		else if (l) {
			cout << "Errror: expected ')', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else if (l) {
		cout << "Errror: expected '(', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
	n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[0]->tr + n.children[n.children.size() - 1]->children[1]->tr + "2 Func Decl ";
}

void SynAnal::End(token &a, Node& n)
{
	//cout << 3;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("End");
	if (a.lexem=="return") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
		a = lex.nextLex();
		ID(a, *n.children[n.children.size() - 1]);
		if (a.lexem == ";") {
			(n.children[n.children.size() - 1])->children.push_back(nullptr);
			n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
			a = lex.nextLex();
			if (a.lexem == "}") {
				(n.children[n.children.size() - 1])->children.push_back(nullptr);
				n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
				a = lex.nextLex();
			}
			else if (l) {
				cout << "Errror: expected '}', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
				l = 0;
				return;
			}
		}
		else if (l) {
			cout << "Errror: expected ';', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else if (l) {
		cout << "Errror: expected 'return', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
	n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[1]->tr + " return";
}

void SynAnal::FunName(token& a, Node& n)
{
	//cout << 4;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("FunctionName");
	ID(a, *n.children[n.children.size() - 1]);
	n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[0]->tr + " ";
}

void SynAnal::Description(token& a, Node& n)
{	
	//cout << 5;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Description");
	Descr(a, *n.children[n.children.size() - 1]);
	n.children[n.children.size() - 1]->tr += n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->tr;
	if (a.lexem == "int") {
		Description(a, n);
	//	n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->tr+n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size()-1]->tr;
	}
	else if (a.type != "ID" && a.lexem!="while" && l==1) {
		cout << "Errror: expected ID or 'while' or 'int', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}

}


void SynAnal::Op_s(token &a, Node& n)
{	
	//cout << 6;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Operators");
    Op(a, *n.children[n.children.size() - 1]);
	if (l == 0) {
		return;
	}
	if (n.children[n.children.size() - 1]->children[0]->str == "ID") {
		n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[0]->tr;
		n.children[n.children.size() - 1]->tr += n.children[n.children.size() - 1]->children[2]->tr;
		for (int i = 3; i < n.children[n.children.size() - 1]->children.size(); i += 2) {
			if (i < n.children[n.children.size() - 1]->children.size()-1) {	
				n.children[n.children.size() - 1]->tr += n.children[n.children.size() - 1]->children[i + 1]->tr + " "+n.children[n.children.size() - 1]->children[i]->str+" ";
			}
		}
		n.children[n.children.size() - 1]->tr += " = ";
	}
	else {
		if (n.children[n.children.size() - 1]->children.size() > 6) {
			n.children[n.children.size() - 1]->tr += "m" + to_string(k) + " DEFL " + n.children[n.children.size() - 1]->children[2]->tr + "m" + to_string(k + 1) + " BF " + n.children[n.children.size() - 1]->children[5]->tr + " "+n.children[n.children.size() - 1]->children[6]->tr+"m" + to_string(k) + " BRL " + "m" + to_string(k + 1) + " DEFL ";

		}
		else {
			n.children[n.children.size() - 1]->tr += "m" + to_string(k) + " DEFL " + n.children[n.children.size() - 1]->children[2]->tr + "m" + to_string(k + 1) + " BF " + n.children[n.children.size() - 1]->children[5]->tr + "m" + to_string(k) + " BRL " + "m" + to_string(k + 1) + " DEFL ";
		}
		k += 2;
	}
	if (a.type == "ID" || a.lexem == "while") {
		Op_s(a, n);
		if (l == 0) {
			return;
		}
	}
	
	
}


void SynAnal::Descr(token& a, Node& n)
{
	//cout << 7;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Descr");
	if (a.lexem == "int") {
		Type(a, *n.children[n.children.size() - 1]);
		VarList(a, *n.children[n.children.size() - 1]);
		if (l == 0) {
			return;
		}
		n.children[n.children.size() - 1]->children[1]->type = n.children[n.children.size() - 1]->children[0]->type;
	}
	else if (l) {
		cout << "Errror: expected 'int', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
	n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[0]->tr + n.children[n.children.size() - 1]->children[1]->tr + " " + to_string(n.children[n.children.size() - 1]->children[1]->count) + " Decl ";
}

void SynAnal::VarList(token& a, Node& n)
{	
	//cout << 8;
	if (l == 0) {
		return;
	}
	if (n.str != "VarList") {
		n.children.push_back(nullptr);
		n.children[n.children.size() - 1] = new Node("VarList");
		n.children[n.children.size() - 1]->type = n.children[0]->type;
		if (a.type == "ID") {
			n.children[n.children.size() - 1]->count++;
			ID(a, *n.children[n.children.size() - 1]);
			if (l == 0) {
				return;
			}
			n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->tr + n.children[n.children.size() - 1]->tr;
			n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->type = n.children[n.children.size() - 1]->type;
			VarList_2(a, *n.children[n.children.size() - 1]);

		}
		else if (l) {
			cout << "Errror: expected ID, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else {
		if (a.type == "ID") {
			n.count++;
			ID(a, n);
			if (l == 0) {
				return;
			}
			n.tr = n.children[n.children.size() - 1]->tr+n.tr;
			n.children[n.children.size() - 1]->type = n.type;
			VarList_2(a, n);
		}
		else if (l) {
			cout << "Errror: expected ID, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
}

void SynAnal::VarList_2(token& a, Node& n)
{
	//cout << 9;
	if (l == 0) {
		return;
	}
	if (a.lexem == ",") {
		n.children.push_back(nullptr);
		n.children[n.children.size() - 1] = new Node(",");
		a = lex.nextLex();
		VarList(a, n);
		if (l == 0) {
			return;
		}
	}
	else if (a.lexem == ";") {
		n.children.push_back(nullptr);
		n.children[n.children.size() - 1] = new Node(";");
		a = lex.nextLex();
	}
	else if (l) {
		cout << "Errror: expected ',' or ';', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::Type(token& a, Node& n)
{
	//cout << 10;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Type");
	n.children[n.children.size() - 1]->tr = "int ";
	n.children[n.children.size() - 1]->type = "int";
	if (a.lexem == "int") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
		a = lex.nextLex();
	}
	else if (l) {
		cout << "Errror: expected 'int', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::Op(token& a, Node& n)
{	
	//cout << 11;
	if (l == 0) {
		return;
	}
	if (a.type == "ID") {
		ID(a, n);
		if (l == 0) {
			return;
		}
		if (a.lexem == "=") {
			n.children.push_back(nullptr);
			n.children[n.children.size() - 1] = new Node("=");
			a = lex.nextLex();
			Expr(a, n);
			if (l == 0) {
				return;
			}
			if (a.lexem == ";") {
				n.children.push_back(nullptr);
				n.children[n.children.size() - 1] = new Node(";");
				a = lex.nextLex();
			}
			else if (l) {
				cout << "Errror: expected ';', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
				l = 0;
				return;
			}
		}
		else if (l) {
			cout << "Errror: expected '=', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else if (a.lexem == "while") {
		n.children.push_back(nullptr);
		n.children[n.children.size() - 1] = new Node("while");
		a = lex.nextLex();
		if (a.lexem == "(") {
			n.children.push_back(nullptr);
			n.children[n.children.size() - 1] = new Node("(");
			a = lex.nextLex();
			Condition(a, n);
			if (l == 0) {
				return;
			}
			if (a.lexem == ")") {
				n.children.push_back(nullptr);
				n.children[n.children.size() - 1] = new Node(")");
				a = lex.nextLex();
				if (a.lexem == "{") {
					n.children.push_back(nullptr);
					n.children[n.children.size() - 1] = new Node("{");
					a = lex.nextLex();
					Op_s(a, n);
					if (l == 0) {
						return;
					}
					if (a.lexem == "}") {
						n.children.push_back(nullptr);
						n.children[n.children.size() - 1] = new Node("}");
						a = lex.nextLex();
					}
					else if (l) {
						cout << "Errror: expected '}', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
						l = 0;
						return;
					}
				}
				else if (l) {
					cout << "Errror: expected '{', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
					l = 0;
					return;
				}
			}
			else if (l) {
				cout << "Errror: expected ')', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
				l = 0;
				return;
			}
		}
		else if (l) {
			cout << "Errror: expected '(', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else if (l) {
		cout << "Errror: expected 'while' or ID, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::SimpleExpr(token& a, Node& n)
{
	//cout << 12;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("SimpleExpr");
	if (a.lexem == "(") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node("(");
		a = lex.nextLex();
		Expr(a, *n.children[n.children.size() - 1]);		
		if (l == 0) {
			return;
		}
		if (a.lexem == ")") {
			(n.children[n.children.size() - 1])->children.push_back(nullptr);
			n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(")");
			a = lex.nextLex();
			n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[1]->tr + n.children[n.children.size() - 1]->children[3]->tr + " "+n.children[n.children.size() - 1]->children[2]->str+" ";
		}
		else if (l) {
			cout << "Errror: expected ')', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
			l = 0;
			return;
		}
	}
	else if (a.type == "ID") {
		ID(a, *n.children[n.children.size() - 1]);
		if (l == 0) {
			return;
		}
		n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->tr;
	}
	else if (a.type == "CONST") {
		Const(a, *n.children[n.children.size() - 1]);
		if (l == 0) {
			return;
		}
		n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->tr;
	}
	else if (l) {
		cout << "Errror: expected ID or CONST, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::Expr(token& a, Node& n)
{
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Expr");
	if (a.lexem == "(" || a.type == "ID" || a.type == "CONST") {
		SimpleExpr(a, *n.children[n.children.size() - 1]);
		if (l == 0) {
			return;
		}
		n.children[n.children.size() - 1]->tr= n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1]->tr;
	}
	else if (l) {
		cout << "Errror: expected '(' or ID or CONST, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
	if (a.lexem == "+" || a.lexem == "-") {
		string s = a.lexem;
		n.children.push_back(nullptr);
		n.children[n.children.size() - 1] = new Node(a.lexem);
		a = lex.nextLex();
		Expr(a, n);
		if (l == 0) {
			return;
		}
	}
}

void SynAnal::Condition(token& a, Node& n)
{
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("Condition");
	if (a.lexem == "(" || a.type == "ID" || a.type == "CONST") {
		Expr(a, *n.children[n.children.size() - 1]);
		RelationOp(a, *n.children[n.children.size() - 1]);
		Expr(a, *n.children[n.children.size() - 1]);
		if (l == 0) {
			return;
		}
		n.children[n.children.size() - 1]->tr = n.children[n.children.size() - 1]->children[0]->tr + n.children[n.children.size() - 1]->children[2]->tr + n.children[n.children.size() - 1]->children[1]->tr;
	}
	else if (l) {
		cout << "Errror: expected '(' or ID or CONST, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::RelationOp(token& a, Node& n)
{
	//cout << 15;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("RelationOp");
	if (a.lexem == "==" || a.lexem == "!=" || a.lexem == "<=" || a.lexem == ">=" || a.lexem == ">" || a.lexem == "<") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
		n.children[n.children.size() - 1]->tr =" "+ a.lexem+ " ";
		a = lex.nextLex();
	}
	else if(l) {
		cout << "Errror: expected '!=' or '==' or '<=' or '>='  or '>' or '<', incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void SynAnal::ID(token& a, Node& n)
{	
	//cout << 16;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("ID");
	
	if (a.type == "ID") {
		n.children[n.children.size() - 1]->tr = a.lexem+" ";
		if (op == 1 && table.find(a.lexem)!="int") {
			out << "undeclared variable - " << a.lexem << " (place " << lex.getpos() << ")" << endl;
		}
			if (op==0 && table.find(a.lexem) == "int") {
				out << "override variable - " << a.lexem << " (place " << lex.getpos() << ")" << endl;
			}
			table.push_back(token("int", a.lexem));
			(n.children[n.children.size() - 1])->children.push_back(nullptr);
			n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
			a = lex.nextLex();
	}
	else if (l) {
		cout << "Errror: expected ID, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
	
	
}

void SynAnal::Const(token& a, Node& n)
{
	//cout << 17;
	if (l == 0) {
		return;
	}
	n.children.push_back(nullptr);
	n.children[n.children.size() - 1] = new Node("CONST");
	n.children[n.children.size() - 1]->tr =" "+a.lexem+" ";
	if (a.type == "CONST") {
		(n.children[n.children.size() - 1])->children.push_back(nullptr);
		n.children[n.children.size() - 1]->children[n.children[n.children.size() - 1]->children.size() - 1] = new Node(a.lexem);
		a = lex.nextLex();
	}
	else if (l) {
		cout << "Errror: expected CONST, incoming lexem '" << a.lexem << "' (place " << lex.getpos() << ")" << endl;
		l = 0;
		return;
	}
}

void Node::vivod(string s, ofstream& tree)
{
	tree << s << str <<" " << endl;
	for (int i = 0; i < children.size(); ++i) {
		string s1 = s;
		for (int i = 0; i < str.size(); ++i) {
			s1 += " ";
		}
		children[i]->vivod(s1, tree);
	}
}



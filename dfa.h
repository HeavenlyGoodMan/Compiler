#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include"token.h"
class dfa
{
private:
	int countStates; // ���������� ��������� ��������
	std::vector<char> alphabet; // ������� �������
	std::vector<int> finalStates; // ��������� ����������� ���������
	std::vector<std::vector<int>> transitFunction; // ������� ��������� 
	// transitFunction[i][j] = k ��������, ��� �� i-�� ��������� �� j-�� ������� �������� �������� ������� ��������� � ��������� k
	int getState(int state, char c);
	std::set<int> inverse(int state, int k);
	friend class lexer;

public:
	dfa() = default;
	std::vector <string> TypeFinal;
	dfa(int countStates, std::vector<char> alphabet, std::vector<int> finalStates, std::vector<std::vector<int>> transitFunction);
	bool isAccept(std::string s);
	dfa minimize();
	std::vector<std::vector<int>> quotientSet();
};


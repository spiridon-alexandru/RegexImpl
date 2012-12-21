#include <iostream>
#include "nfa.h"
using namespace std;

NFA::NFA(int _stateNumber) : stateNumber(_stateNumber)
{
	map = vector<vector<string> >(_stateNumber + 1);

	for (int i = 0; i < _stateNumber + 1; i++)
	{
		map[i] = vector<string>(_stateNumber + 1);
	}
}

void NFA::printNFA()
{
	cout << "Number of states: " << stateNumber << "\n";
	cout << "Transitions:\n";

	for (int i = 1; i < stateNumber + 1; i++)
	{
		for (int j = 1; j < stateNumber + 1; j++)
		{
			cout << "From: " << i << " to " << j << " : " << map[i][j] << "\n";
		}
	}
}
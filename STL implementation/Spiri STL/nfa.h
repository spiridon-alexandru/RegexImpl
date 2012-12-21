#ifndef NFA_H
#define NFA_H

#include <vector>
#include <string>
using namespace std;

class NFA 
{
	int stateNumber;
	vector<vector<string> > map;
	int startState;
	vector<int> finalStates;

public:

	NFA(int stateNumber);

	void printNFA();
};

#endif // NFA_H
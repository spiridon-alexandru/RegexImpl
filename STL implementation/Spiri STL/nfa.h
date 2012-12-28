#ifndef NFA_H
#define NFA_H

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <set>

using namespace std;

// TODO SA: change eps character
#define eps '+'

class NFA 
{
	int epsC(int state, set<int> &closure);

public:
	int stateNumber;
	vector<vector<string> > map;
	int startState;
	vector<int> finalStates;

	/**
	 * Constructs a nfa with a defined number of states.
	 */
	NFA(int stateNumber);

	/**
	 * Constructs a nfa for a single character regular expression.
	 */
	NFA(char c);

	/**
	 * Prints the nfa to the stdout
	 */
	void printNFA();

	/**
	 * Simulates the nfa.
	 * @returns true if the input has passed, false otherwise.
	 */
	bool simulate(string input);

	/**
	 * Returns the epsilon closure of the state.
	 */
	set<int> epsClosure(int state);
};

/**
 * Converts an integer into a string.
 */
string toString(int val);

/**
 * Concatenates two nfas and returns the resulting nfa
 */
NFA concat(NFA n1, NFA n2);

/**
 * Alternates (|) two nfas and returns the resulting nfa
 */
NFA alternate(NFA n1, NFA n2);

/**
 * Returns the (n)* nfa
 */
 NFA starTransform(NFA n);

 /**
 * Returns the (n)+ nfa
 */
 NFA plusTransform(NFA n);

#endif // NFA_H
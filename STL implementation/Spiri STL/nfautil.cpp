#include "nfautil.h"

/**
 * Converts an integer into a string.
 */
string toString(int val)
{
	int a = 10;
	stringstream ss;
	ss << val;
	string str = ss.str();

	return str;
}

/**
 * Concatenates two nfas and returns the resulting nfa
 */
NFA concat(NFA n1, NFA n2)
{
	NFA n3(n1.stateNumber + n2.stateNumber);

	n3.startState = 1;

	// add the transitions from n1
	for (int i = 1; i <= n1.stateNumber; i++)
	{
		for (int j = 1; j <= n1.stateNumber; j++)
		{
			n3.map[i][j] = n1.map[i][j];
		}
	}

	// add the transitions from n2
	for (int i = 1; i <= n2.stateNumber; i++)
	{
		for (int j = 1; j <= n2.stateNumber; j++)
		{
			n3.map[i + n1.stateNumber][j + n1.stateNumber] = n2.map[i][j];
		}
	}

	// add the concatenation transitions
	for (int i = 0; i < n1.finalStates.size(); i++)
	{
		n3.map[n1.finalStates[i]][n1.stateNumber + 1] = eps;
	}

	// set the new final states
	n3.finalStates.clear();
	for (int i = 0; i < n2.finalStates.size(); i++)
	{
		n3.finalStates.push_back(n2.finalStates[i] + n1.stateNumber);
	}

	return n3;
}

/**
 * Alternates (|) two nfas and returns the resulting nfa
 */
NFA alternate(NFA n1, NFA n2)
{
	NFA ns = NFA(3);

 	return ns;
}

/**
 * Returns the (n)* nfa
 */
 NFA star(NFA n)
 {
 	NFA ns(n.stateNumber + 2);
 	ns.startState = 1;

 	ns.finalStates.push_back(ns.stateNumber);

 	// connect the start state to the nfa
 	ns.map[1][2] = eps;
 	// connect the start state to the final state
 	ns.map[1][ns.finalStates[0]] = eps;

 	// connect the final states of n to the new final state
 	for (int i = 0; i < n.finalStates.size(); i++)
 	{
 		ns.map[n.finalStates[i] + 1][ns.startState] = eps;
 	}

 	// copy all the n transitions into ns
	for (int i = 1; i < n.map.size(); i++)
	{
		for (int j = 1; j < n.map.size(); j++)
		{
			ns.map[i + 1][j + 1] = n.map[i][j];
		}
	} 	

 	return ns;
 }

 /**
 * Returns the (n)+ nfa
 */
 NFA plus(NFA n)
 {
 	NFA np = NFA(3);

 	return np;
 }
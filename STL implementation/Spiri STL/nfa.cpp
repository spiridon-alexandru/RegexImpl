#include <iostream>
#include <algorithm>
#include "nfa.h"
using namespace std;


/**
 * Constructs a nfa with a defined number of states.
 */
NFA::NFA(int _stateNumber) : stateNumber(_stateNumber)
{
	map = vector<vector<string> >(_stateNumber + 1);

	for (int i = 0; i < _stateNumber + 1; i++)
	{
		map[i] = vector<string>(_stateNumber + 1);
	}
}

/**
 * Constructs a nfa for a single character regular expression.
 */
NFA::NFA(char _c) : stateNumber(2)
{
	map = vector<vector<string> >(3);

	map[0] = vector<string>(3);
	map[1] = vector<string>(3);
	map[2] = vector<string>(3);

	map[1][2] = _c;

	startState = 1;
	finalStates.push_back(2);
}

/**
 * Prints the nfa to the stdout
 */
void NFA::printNFA()
{
	cout << "\nPrinting NFA...\n";
	cout << "Number of states: " << stateNumber << "\n";
	cout << "Start state: " << startState << "\n";
	cout << "Transitions:\n";

	for (int i = 1; i < stateNumber + 1; i++)
	{
		for (int j = 1; j < stateNumber + 1; j++)
		{
			string trans = map[i][j];
			if (trans == "")
				trans = "nan";
			int spaces = sqrt(stateNumber);
			cout << setw(spaces) << trans << " ";
		}
		cout << "\n";
	}

	cout << "Final states: \n";
	for (int j = 0; j < finalStates.size(); j++)
	{
		cout << finalStates[j] << " ";
	}

	cout << "\n";

/*	for (int i = 1; i < stateNumber + 1; i++)
	{
		for (int j = 1; j < stateNumber + 1; j++)
		{
			string trans = map[i][j];
			if (trans == "")
				trans = "nan";
			cout << "From: " << i << " to " << j << " : " << trans << "\n";
		}
	} */
}

/**
 * Simulates the nfa.
 * @returns true if the input has passed, false otherwise.
 */
bool NFA::simulate(string input)
{
	// the current states
	set<int> cs;
	cs.insert(startState);

	// add the closure of the start state
	set<int> closure = epsClosure(startState);
	std::set<int>::iterator closureIt;
	for (closureIt=closure.begin(); closureIt!=closure.end(); ++closureIt)
	{
		cs.insert(*closureIt);
	}

	set<int> newStates;
	std::set<int>::iterator it;

	for (int k = 0; k < input.size(); k++)
	{
		newStates.clear();
		char c = input[k];

//		cout << "For input: " << c << "\n";
//		cout << "Input: ";

		for (it=cs.begin(); it!=cs.end(); ++it)
		{
//			cout << *it << " ";
			int state = *it;
			for (int i = 1; i <= stateNumber; i++)
			{
				int found=map[state][i].find(c);
  				if (found!=string::npos)
  				{
  					std::set<int>::iterator findIt;
					findIt=cs.find(i);
					
  					// add the eps closure if it's not inside the current states
					newStates.insert(i);
  					
  					// add the eps closure
					closure = epsClosure(i);
					for (closureIt=closure.begin(); closureIt!=closure.end(); ++closureIt)
					{
						newStates.insert(*closureIt);
					}

			/*		cout << "Closure: ";
					for (it=newStates.begin(); it!=newStates.end(); ++it)
					{
						cout << *it << " ";
					}
					cout << "\n"; */
  				}
			}
		}
//		cout << "\n";

/*		cout << "Closure: ";
		for (it=newStates.begin(); it!=newStates.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << "\n\n"; */

		// if we can't move to any states with the current input, the input has failed the simulation
		if (newStates.empty())
		{
			return false;
		}

		cs = newStates;
	} 

	// check if we reached a final state
	for (it=newStates.begin(); it!=newStates.end(); ++it)
	{
		int state = *it;
		// if we're in a final state, the input has passed
		if (find(finalStates.begin(), finalStates.end(), state) != finalStates.end())
		{
			return true;
		}
	}

	return false;
}

/**
 * Returns the epsilon closure of the state.
 */
set<int> NFA::epsClosure(int state)
{
	set<int> closure;

	epsC(state, closure);

	return closure;
}

int NFA::epsC(int state, set<int> &closure)
{
	for (int i = 1; i <= stateNumber; i++)
	{
		int found=map[state][i].find(eps);

  		if (found!=string::npos && closure.find(i) == closure.end())
  		{
  			closure.insert(i);
  			int cl = epsC(i,closure);
  			closure.insert(cl);
  			
  		}
	}
	
	return state;
}

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
	NFA na = NFA(n1.stateNumber + n2.stateNumber + 2);

	int finalState = n1.stateNumber + n2.stateNumber + 2;
	na.startState = 1;
	na.finalStates.push_back(finalState);

	// connect the start state of the resulting nfa to the start states of the two nfas
	na.map[na.startState][n1.startState + 1] = eps;
	na.map[na.startState][n2.startState + n1.stateNumber + 1] = eps;

	// add the transitions from n1
	for (int i = 1; i <= n1.stateNumber; i++)
	{
		for (int j = 1; j <= n1.stateNumber; j++)
		{
			na.map[i + 1][j + 1] = n1.map[i][j];
		}
	}

	// add the transitions from n2
	for (int i = 1; i <= n2.stateNumber; i++)
	{
		for (int j = 1; j <= n2.stateNumber; j++)
		{
			na.map[i + n1.stateNumber + 1][j + n1.stateNumber + 1] = n2.map[i][j];
		}
	}

	// connect the final states of the nfas n1 and n2 to the new final state
	for (int i = 0; i < n1.finalStates.size(); i++)
	{
		na.map[n1.finalStates[i] + 1][finalState] = eps;
	}

	for (int i = 0; i < n2.finalStates.size(); i++)
	{
		na.map[n2.finalStates[i] + n1.stateNumber + 1][finalState] = eps;
	}

 	return na;
}

/**
 * Transforms the regex e implemented as finite automata n into
 * 'e?'
 */
NFA questionTransform(NFA n)
{
	NFA nq(n.stateNumber + 2);
	int finalState = n.stateNumber + 2;
	nq.startState = 1;

 	nq.finalStates.push_back(finalState);

 	// connect the start state to the nfa
 	nq.map[1][n.startState + 1] = eps;
 	// connect the start state to the final state
 	nq.map[1][finalState] = eps;

 	// connect the final states of n to the new final state
 	for (int i = 0; i < n.finalStates.size(); i++)
 	{
 		nq.map[n.finalStates[i] + 1][finalState] = eps;
 	}

 	// copy all the n transitions into ns
	for (int i = 1; i < n.map.size(); i++)
	{
		for (int j = 1; j < n.map.size(); j++)
		{
			nq.map[i + 1][j + 1] = n.map[i][j];
		}
	} 	

 	return nq;
}

/**
 * Returns the (n)* nfa
 */
NFA starTransform(NFA n)
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
NFA plusTransform(NFA n)
{
 	int newStateNr = n.stateNumber + 1;
 	NFA np(newStateNr);
 	np.startState = 1;

 	np.finalStates.push_back(newStateNr);

 	// connect the final state to the start state
 	np.map[newStateNr][1] = eps;
 	// connect the previous final states to the new one
 	for (int i = 0; i < n.finalStates.size(); i++)
 	{
 		np.map[n.finalStates[i]][newStateNr] = eps;
 	}

 	// copy all the n transitions into ns
	for (int i = 1; i < n.map.size(); i++)
	{
		for (int j = 1; j < n.map.size(); j++)
		{
			np.map[i][j] = n.map[i][j];
		}
	} 	

 	return np;
}
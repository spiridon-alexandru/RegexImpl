#include <iostream>
#include <string>
#include "nfa.h"
using namespace std;

int main(int argc, char** argv)
{
/*	NFA nfa(20);

	nfa.printNFA(); */

	// creating the regex acd*
	NFA nfa1('a');
	NFA nfa2('c');

	// concat test
//	nfa1.printNFA();
//	nfa2.printNFA();

	NFA nfa3 = concat(nfa1, nfa2);

//	nfa3.printNFA();

	// star test
	NFA nfa4('d');
	NFA nfa5 = starTransform(nfa4);

//	nfa5.printNFA();

	// final nfa acd*
	NFA nfa6 = concat (nfa3, nfa5);

//	nfa6.printNFA();

	// eps closure test
/*	set<int> closure = nfa6.epsClosure(4);
	cout << "Closure of node 4:\n";
	std::set<int>::iterator it;
	for (it=closure.begin(); it!=closure.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n";
	
	closure = nfa6.epsClosure(2);
	cout << "Closure of node 2:\n";
	for (it=closure.begin(); it!=closure.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n"; */

	// nfa simulation test
/*	string test = "acdddd";
	if (nfa6.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	}


	test = "ac";
	if (nfa6.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	}

	test = "acd";
	if (nfa6.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	}

	test = "ace";
	if (nfa6.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	} */

	// plus test
	NFA nfa7('d');
	NFA nfa8 = plusTransform(nfa7);

	//nfa8.printNFA();

	// final nfa acd*
	NFA nfa9 = concat (nfa3, nfa8);

	//nfa9.printNFA();

	// nfa simulation test
	string test = "acd";
	if (nfa9.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	}

	test = "ac";
	if (nfa9.simulate(test))
	{
		cout << "String \"" << test << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << test << "\" failed!\n";
	}

	return 0;
}
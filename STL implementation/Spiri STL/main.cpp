#include <iostream>
#include <string>
#include "nfa.h"
using namespace std;

/**
 * Creates and prints two simple nfas
 * @returns The resulting nfa. 
 */
NFA testCreation();

/**
 * Creates two nfas, concatenates them and prints the result
 * @returns The resulting nfa. 
 */
NFA testConcatenation();

/**
 * Creates a nfa from regex "(ab)?" and prints the result.
 * @returns The resulting nfa.
 */
NFA testQuestionTransformation();


/**
 * Creates a nfa from regex "acd*" and prints the result.
 * @returns The resulting nfa.
 */
NFA testStarTransformation();

/**
 * Creates a nfa from regex "acd*" and prints the closure of a node.
 * @param nfa The nfa cotaining the node that needs closure calculation.
 * @param node The node of which closure needs to be calculated.
 * @returns The closure of the selected node in a stl set.
 */
set<int> testClosure(NFA nfa, int node);

/**
 * Creates a nfa from regex "acd+" and prints the result.
 * @returns The resulting nfa.
 */
NFA testPlusTransformation();

/**
 * Creates a nfa from reges "(a|b)c*" and prints the result.
 * @returns The resulting nfa.
 */
NFA testAlternation();

/**
 * Simulates an input string over the nfa.
 * @param nfa The non-deterministic finite automata.
 * @param input The input string that needs to be simulated.
 */
void simulateNFA(NFA nfa, string input);

int main(int argc, char** argv)
{
	NFA creationNFA = testCreation();
	NFA concatenationNFA = testConcatenation();

	NFA starNFA = testStarTransformation();
	NFA plusNFA = testPlusTransformation();
	// TODO SA: question transformation should validate the empty string
	NFA questionNFA = testQuestionTransformation();
	
	// testing composed question transformation
	// TODO SA: organize better the tests
	NFA n1 = starTransform(questionNFA);

	n1.printNFA();

	string t1 = "ab";
	simulateNFA(n1, t1);

	// should fail
	t1 = "abc";
	simulateNFA(n1, t1);
	// end of composed transformation test

	testClosure(starNFA, 4);
	testClosure(starNFA, 2);

	// nfa simulation test on "acd*"
	string test = "acdddd";
	simulateNFA(starNFA, test);

	test = "ac";
	simulateNFA(starNFA, test);

	test = "acd";
	simulateNFA(starNFA, test);

	// should fail
	test = "ace";
	simulateNFA(starNFA, test);

	// nfa simulation test on "acd+"
	test = "acd";
	simulateNFA(plusNFA, test);

	// should fail
	test = "ac";
	simulateNFA(plusNFA, test);

	NFA alternateNFA = testAlternation();

	// nfa simulation test on "a|b"
	test = "a";
	simulateNFA(alternateNFA, test);

	test = "b";
	simulateNFA(alternateNFA, test); 

	// should fail
	test = "c";
	simulateNFA(alternateNFA, test);

	return 0;
}

/**
 * Creates and prints two simple nfas
 * @returns The resulting nfa. 
 */
NFA testCreation()
{
	// creating the regex acd*
	NFA nfa1('a');

	nfa1.printNFA();

	return nfa1;
}

/**
 * Creates two nfas, concatenates them and prints the result
 * @returns The resulting nfa. 
 */
NFA testConcatenation()
{
	// concat test
	NFA nfa1('a');
	NFA nfa2('c');

	NFA nfa3 = concat(nfa1, nfa2);

	nfa3.printNFA();

	return nfa3;
}

/**
 * Creates a nfa from regex "acd*" and prints the result.
 * @returns The resulting nfa.
 */
NFA testStarTransformation()
{
	NFA nfa1('a');
	NFA nfa2('c');

	NFA nfa3 = concat(nfa1, nfa2);

	// star test
	NFA nfa4('d');
	NFA nfa5 = starTransform(nfa4);

	// final nfa acd*
	NFA nfa6 = concat (nfa3, nfa5);

	nfa6.printNFA();

	return nfa6;
}

/**
 * Creates a nfa from regex "(ab)?" and prints the result.
 * @returns The resulting nfa.
 */
NFA testQuestionTransformation()
{
	NFA nfa1('a');
	NFA nfa2('b');

	NFA nfa3 = concat(nfa1, nfa2);

	// quiestion transformation test
	NFA nfa4 = questionTransform(nfa3);

	nfa4.printNFA();

	return nfa4;
}

/**
 * Creates a nfa from regex "acd*" and prints the closure of a node.
 * @param nfa The nfa cotaining the node that needs closure calculation.
 * @param node The node of which closure needs to be calculated.
 * @returns The closure of the selected node in a stl set.
 */
set<int> testClosure(NFA nfa, int node)
{
	// invalid node
	if (node > nfa.stateNumber || node < 1)
		return set<int>();

	// eps closure test
	set<int> closure = nfa.epsClosure(node);
	cout << "Closure of node " << node << ":\n";
	std::set<int>::iterator it;
	for (it=closure.begin(); it!=closure.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << "\n";

	return closure;
}

/**
 * Creates a nfa from regex "acd+" and prints the result.
 * @returns The resulting nfa.
 */
NFA testPlusTransformation()
{
	NFA nfa1('a');
	NFA nfa2('c');

	NFA nfa3 = concat(nfa1, nfa2);

	// plus test
	NFA nfa4('d');
	NFA nfa5 = plusTransform(nfa4);

	// final nfa acd*
	NFA nfa6 = concat (nfa3, nfa5);

	nfa6.printNFA();

	return nfa6;
}

/**
 * Creates a nfa from reges "(a|b)c*" and prints the result.
 * @returns The resulting nfa.
 */
NFA testAlternation()
{
	NFA nfa1('a');
	NFA nfa2('b');

	NFA nfa3 = alternate(nfa1, nfa2);

	nfa3.printNFA();

	return nfa3;
}

/**
 * Simulates an input string over the nfa.
 * @param nfa The non-deterministic finite automata.
 * @param input The input string that needs to be simulated.
 */
void simulateNFA(NFA nfa, string input)
{
	if (nfa.simulate(input))
	{
		cout << "String \"" << input << "\" passed!\n";
	}
	else
	{
		cout << "String \"" << input << "\" failed!\n";
	}
}
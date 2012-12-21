#include <iostream>
#include <string>
#include "nfa.h"
using namespace std;

int main(int argc, char** argv)
{
	NFA nfa(20);

	nfa.printNFA();

	return 0;
}
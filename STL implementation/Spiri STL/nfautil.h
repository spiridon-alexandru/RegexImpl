#ifndef NFAUTIL_H
#define NFAUTIL_H

#include <string>

using namespace std;

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
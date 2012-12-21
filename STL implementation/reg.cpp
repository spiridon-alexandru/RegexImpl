#include <iostream>
#include <cstring>
#include <stack>
#include "state.h"
#include "ptrlist.h"
#include "frag.h"
#include "list.h"
using namespace std;

#ifndef REG_CPP_
#define REG_CPP_

State matchstate = { Match };
int nstate;

/*
 * Convert infix regexp re to postfix notation.
 * Insert . as explicit concatenation operator.
 * Cheesy parser, return static buffer.
 */
string re2post(char *re)
{
	int nalt, natom;
	string buf = "";
	
	struct {
		int nalt;
		int natom;
	} paren[100], *p;
	
	p = paren;
	nalt = 0;
	natom = 0;

	for(; *re; re++)
	{
		switch(*re)
		{
			case '(':
				if(natom > 1){
					--natom;
					buf += '.';
				}
				if(p >= paren+100)
					return NULL;
				p->nalt = nalt;
				p->natom = natom;
				p++;
				nalt = 0;
				natom = 0;
				break;
			case '|':
				if(natom == 0)
					return NULL;
				while(--natom > 0)
					buf += '.';
				nalt++;
				break;
			case ')':
				if(p == paren)
					return NULL;
				if(natom == 0)
					return NULL;
				while(--natom > 0)
					buf += '.';
				for(; nalt > 0; nalt--)
					buf += '|';
				--p;
				nalt = p->nalt;
				natom = p->natom;
				natom++;
				break;
			case '*':
			case '+':
			case '?':
				if(natom == 0)
					return NULL;
				buf += (*re);
				break;
			default:
				if(natom > 1){
					--natom;
					buf += '.';
				}
				buf += (*re);
				natom++;
				break;
		}
	}
	if(p != paren)
		return NULL;
	while(--natom > 0)
		buf +=  '.';
	for(; nalt > 0; nalt--)
		buf +=  '|';

	return buf;
}


State* post2nfa(string postfix)
{
	stack<Frag> nfaStack;
	Frag e1, e2, e;
	State *s;

	if(postfix == "")
		return NULL;

	for(int i; i < postfix.length(); i++)
	{
		char c = postfix[i];
		switch(c)
		{
			default:
				s = state(c, NULL, NULL);
				nstate++;
				nfaStack.push(frag(s, list1(&s->out)));
				break;
			case '.':	// catenate
				e2 = nfaStack.top();
				nfaStack.pop();
				e1 = nfaStack.top();
				nfaStack.pop();
				patch(e1.out, e2.start);
				nfaStack.push(frag(e1.start, e2.out));
				break;
			case '|':	// alternate
				e2 = nfaStack.top();
				nfaStack.pop();
				e1 = nfaStack.top();
				nfaStack.pop();
				s = state(Split, e1.start, e2.start);
				nstate++;
				nfaStack.push(frag(s, append(e1.out, e2.out)));
				break;
			case '?':	// zero or one
				e = nfaStack.top();
				nfaStack.pop();
				s = state(Split, e.start, NULL);
				nstate++;
				nfaStack.push(frag(s, append(e.out, list1(&s->out1))));
				break;
			case '*':	// zero or more
				e = nfaStack.top();
				nfaStack.pop();
				s = state(Split, e.start, NULL);
				nstate++;
				patch(e.out, s);
				nfaStack.push(frag(s, list1(&s->out1)));
				break;
			case '+':	// one or more
				e = nfaStack.top();
				nfaStack.pop();
				s = state(Split, e.start, NULL);
				nstate++;
				patch(e.out, s);
				nfaStack.push(frag(e.start, list1(&s->out1)));
				break;
		}
	}

	e = nfaStack.top();
	nfaStack.pop();

	patch(e.out, &matchstate);
	return e.start;
}

/* Check whether state list contains a match. */
int ismatch(List *l)
{
	int i;

	for(i=0; i<l->n; i++)
		if(l->s[i] == &matchstate)
			return 1;
	return 0;
}

/* Run NFA to determine whether it matches s. */
int match(State *start, char *s)
{
	int i, c;
	List *clist, *nlist, *t;

	clist = startlist(start, &l1);
	nlist = &l2;
	for(; *s; s++){
		c = *s & 0xFF;
		step(clist, c, nlist);
		t = clist; clist = nlist; nlist = t;	/* swap clist, nlist */
	}
	return ismatch(clist);
}

int main(int argc, char **argv)
{
	string post;
	State *start;

	if(argc < 3)
	{
		cout << "usage: nfa regexp string...\n" << "\n";
		return 1;
	}
	
	post = re2post(argv[1]);
	cout << post << "\n";
	if(post == "")
	{
		cout << "bad regexp: " << argv[1] << "\n";
		return 1;
	}

	start = post2nfa(post);
	if(start == NULL)
	{
		cout << "error in post2nfa: " << post << "\n";
		return 1;
	}
	
	l1.s = new State*[nstate];
	l2.s = new State*[nstate];
	for(int i=2; i<argc; i++)
	{
		if(match(start, argv[i]))
		{
			cout << "Matches: " << argv[i] << "\n";
		}
	}

	return 0;
}

#endif /* REG_CPP_ */
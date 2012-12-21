#ifndef STATE_H_
#define STATE_H_

/*
 * Represents an NFA state plus zero or one or two arrows exiting.
 * if c == Match, no arrows out; matching state.
 * If c == Split, unlabeled arrows to out and out1 (if != NULL).
 * If c < 256, labeled arrow with character c to out.
 */
enum
{
	Match = 256,
	Split = 257
};

typedef struct State State;
struct State
{
	int c;
	State *out;
	State *out1;
	int lastlist;
};

/* Allocate and initialize State */
State* state(int c, State *out, State *out1)
{
	State *s;
	s = new State();
	s->lastlist = 0;
	s->c = c;
	s->out = out;
	s->out1 = out1;
	return s;
}

#endif /* STATE_H_ */
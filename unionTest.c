#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Ananas Ananas;
struct Ananas
{
	int a;
	char b;
};

typedef struct Banana Banana;
struct Banana
{
	int a;
	char b;
};

typedef union test test;
union test 
{
	Ananas * n1;
	Banana * n2;
} u;

int main(int argc, char **argv)
{
	Ananas n;
	n.a = 2;
	n.b = 'c';

	Banana n2;
	n2.a = 3;
	n2.b = 'a';

	test u;
	u.n1 = &n;
	u.n2 = &n2;

	printf("Union a: %d %c\n", (*u.n1).a, (*u.n1).b);
	printf("Union a: %d %c\n", (*u.n2).a, (*u.n2).b);

/*	u.a = 23213;

	printf("Union int: %d %.3f %s \n", u.a, u.d, u.c);

	u.d = 3.42;

	printf("Union float: %d %.3f %s \n", u.a, u.d, u.c); */

	printf("%d %d", sizeof(int), sizeof(char));

	return 0;
}
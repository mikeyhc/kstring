#include <kstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTSTR_A "abc "
#define TESTSTR_B "another string"

int main(void)
{
	unsigned failures;
	const char *a, *c;
	char *b;

	failures = 0;
	
	a = kstring_new(TESTSTR_A);
	b = malloc(sizeof(TESTSTR_B) + 1);
	if(!a || !b){
		if(a) kstring_destroy(a);
		if(b) free(b);
		return -1;
	}
	strcpy(b, TESTSTR_B);
	c = kstrcat(a, b);
	if(!c){ 
		kstring_destroy(c);
		return -1;
	}

	printf("c = a + b: ");
	if(!strcmp(c, TESTSTR_A TESTSTR_B))
		printf("PASSED\n");
	else
		printf("FAILED(%s)\n", c), failures++;
	return failures;
}

#include <kstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTSTR_A "abc"
#define TESTSTR_B "another string"

int main(void)
{
	unsigned failures;
	const char *iskstr; 
	char *notkstr;

	failures = 0;
	
	iskstr = kstring_new(TESTSTR_A);
	notkstr = malloc(sizeof(TESTSTR_B) + 1);
	if(!iskstr || !notkstr){
		if(iskstr)
			kstring_destroy(iskstr);
		if(notkstr)
			free(notkstr);
		return -1;
	}
	strcpy(notkstr, TESTSTR_B);

	printf("is_kstring(iskstr):  ");
	if(is_kstring(iskstr))
		printf("PASSED\n");
	else
		printf("FAILED\n"), failures++;
	printf("is_kstring(notkstr): "); 
	if(!is_kstring(notkstr))
		printf("PASSED\n");
	else
		printf("FAILED\n"), failures++;
	return failures;
}

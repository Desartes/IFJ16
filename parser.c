#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
// #include "scanner.c"

int program();

	FILE *f;
	string *s;

int main(void)
{
	f = fopen("test.txt","r");
	s = malloc(sizeof(string));

	if(f == NULL || s == NULL)
		return -1;
	init_string(s);


	program();



	return 0;
}

int first_time = 1;

int program() {
	int token;

/* Class Main { 
***********************************************************************/
	switch( token = get_token(f,s) ) {
		case kw_class:
			printf("Class Success : %d\n", token);
			switch( token = get_token(f,s) ) {
				case kw_main:
					printf("Main Success : %d\n", token);
					if ( (token = get_token(f,s)) == char_LMZatvorka) {
						printf("{ Success : %d\n", token);
						return program();
					}
				case is_id:
					printf("ID Success : %d\n", token);
					if ( (token = get_token(f,s)) == char_LMZatvorka) {
						printf("{ Success : %d\n", token);
						return program();
					}

			}
		case char_PMZatvorka:
			printf("} Success : %d\n", token);
				return program();
		case EOF:
			printf("End of file\n");
			first_time = 0;
			return 0;
		default:
			printf("Error\n");
			return 1;
	}

/**********************************************************************/


	return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"
// #include "scanner.c"

int root();
int class_body();

FILE *f;
string *s;

int first_time;

int main(void)
{
	f = fopen("test.txt","r");
	s = malloc(sizeof(string));

	if(f == NULL || s == NULL)
		return -1;
	init_string(s);

	first_time = 1;
	root();



	return 0;
}


int root() {
	int token;

/* Class Main/ID { // root
***********************************************************************/
	switch( token = get_token(f,s) ) {

		case kw_class:
			printf("Class Success : %s\n", s->str);
			switch( token = get_token(f,s) ) {
				case kw_main:
					printf("Main Success : %s\n", s->str);
					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
							first_time = 0;
							printf("{ Success : %d\n", token);
							if ( class_body() == ERR_OK ) {
								return root();
							} else {
								printf("Error\n");
								return ERR_SYNTAX_ERR;
							}
						default:
							printf("Error %d\n", token);
							return ERR_SYNTAX_ERR;
					}

				case is_id:
					if (first_time)	{
						printf("Error\n");
						return ERR_SYNTAX_ERR;
					}

					printf("ID Success : %s\n", s->str);
					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
							first_time = 0;
							printf("{ Success : %d\n", token);
							if ( class_body() == ERR_OK ) {
								return root();
							}
						default:
							return ERR_SYNTAX_ERR;
					}
			}
		
		
		case EOF:
			printf("End of file\n");
			first_time = 0;
			return 0;
		
		default:
			printf("Error : %d\n", ERR_SYNTAX_ERR);
			return ERR_SYNTAX_ERR;
	}

/**********************************************************************/


	return 0;
}

int class_body() {
	int token;

	if ( (token = get_token(f, s)) == char_PMZatvorka ) {
		printf("} Success : %d\n", token);
		return ERR_OK;
	} else {
		return ERR_SYNTAX_ERR;
	}
}
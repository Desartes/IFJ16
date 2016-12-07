#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"
// #include "scanner.c"

int root();
int class_body();
int func_body();
int func_params();
int expression_solve();

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
	printf("Result of parse : %d\n", root());


	// int x;
	// while( (x = get_token(f, s)) != EOF ) {
	// 	printf("%s : %d\n", s->str, x);
	// }



	return 0;
}


int root() {
	int token;
	int result;

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
							if ( (result = class_body()) == ERR_OK ) {
								return root();
							} else {
								printf("Error\n");
								return result;
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
							if ( (result = class_body()) == ERR_OK ) {
								return root();
							} else {
								return result;
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
			printf("Error : %d\n", token);
			return ERR_SYNTAX_ERR;
	}

/**********************************************************************/


	return 0;
}

/* static void/sting/int/double/ { // class
***********************************************************************/
int class_body() {
	int token;
	int result;

	switch( (token = get_token(f, s)) ) {
		case kw_static:
			printf("%s\n", s->str);
			switch( token = get_token(f,s) ) {
				case kw_int:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if (func_body() == ERR_OK) {
											return class_body();
										}
									}
								case char_rovnasa:
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
									return class_body();
								default:
									return ERR_SYNTAX_ERR;	 
							}

						default:
							return ERR_SYNTAX_ERR;
					}
				case kw_double:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if (func_body() == ERR_OK) {
											return class_body();
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
								case char_rovnasa:
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
									return class_body();
								default:
									return ERR_SYNTAX_ERR;	
							}

						default:
							return ERR_SYNTAX_ERR;
					}
				case kw_string:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if (func_body() == ERR_OK) {
											return class_body();
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
								case char_rovnasa:
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
									return class_body();
								default:
									return ERR_SYNTAX_ERR;	
							}

						default:
							return ERR_SYNTAX_ERR;
					}
				case kw_void:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if (func_body() == ERR_OK) {
											return class_body();
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
							}

						default:
							return ERR_SYNTAX_ERR;
					}

				default:
					return ERR_SYNTAX_ERR;
			}
			
		case char_PMZatvorka:
			printf("Success : }\n");
			return ERR_OK;
		default:
			return ERR_SYNTAX_ERR;
	}

}
int func_params() {
	int token;
	while( (token = get_token(f,s) ) != char_PZatvorka ) {
		printf("Param success : %s\n", s->str);
	}
	printf(")\n");
	return ERR_OK;
}
int func_body() {
	int token;
	int result;

	switch(token = get_token(f,s)) {
		case kw_int:
			printf("%s\n", s->str);
			switch(token = get_token(f,s)) {
				case is_id:
				printf("%s\n", s->str);
					switch(token = get_token(f,s)) {
						case char_rovnasa:
							if ( (result = expression_solve()) == ERR_OK ) {
								return func_body();
							} else {
								return result;
							}
						case char_bod_ciarka:
							return func_body();
						default:
							return ERR_SYNTAX_ERR;
					}
				default:
					return ERR_SYNTAX_ERR;
			}
		case kw_double:
			printf("%s\n", s->str);
			switch(token = get_token(f,s)) {
				case is_id:
				printf("%s\n", s->str);
					switch(token = get_token(f,s)) {
						case char_rovnasa:
							if ( (result = expression_solve()) == ERR_OK ) {
								return func_body();
							} else {
								return result;
							}
						case char_bod_ciarka:
							return func_body();
						default:
							return ERR_SYNTAX_ERR;
					}
				default:
					return ERR_SYNTAX_ERR;
			}
		case kw_string:
			printf("%s\n", s->str);
			switch(token = get_token(f,s)) {
				case is_id:
				printf("%s\n", s->str);
					switch(token = get_token(f,s)) {
						case char_rovnasa:
							if ( (result = expression_solve()) == ERR_OK ) {
								return func_body();
							} else {
								return result;
							}
						case char_bod_ciarka:
							return func_body();
						default:
							return ERR_SYNTAX_ERR;
					}
				default:
					return ERR_SYNTAX_ERR;
			}


		case kw_return:
			printf("%s\n", s->str);


		case char_PMZatvorka:
			printf("}\n");
			return ERR_OK;
		default:
			return ERR_SYNTAX_ERR;
	}




	while( (token = get_token(f,s) ) != char_PMZatvorka ) {
		printf("function body success : %s\n", s->str);
	}
	printf("}\n");
	return ERR_OK;
}
int expression_solve() {
	int token;
	while( (token = get_token(f,s) ) != char_bod_ciarka ) {
		printf("%s : %d\n", s->str, token);
	}
	printf("Success ;\n");
	return ERR_OK;
}
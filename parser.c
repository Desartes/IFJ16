#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"
#include "ial.h"
// #include "scanner.c"

int root();
int class_body();
int func_body();
int func_params();
int expression_solve();
int bool_expr();

FILE *f;
string *s;

int main(void)
{
	f = fopen("test.txt","r");
	s = malloc(sizeof(string));

	// if(f == NULL || s == NULL)
	// 	return -1;
	// init_string(s);

	printf("Result of parse : %d\n", root());

	// binList *classes = malloc(sizeof(binList));
	// Biteminit(classes);


	// int meh = 5;
	// int k = 6;
	// int kk = 7;

	// struct var *oke;
	// oke = TSnodcreate("x", k_int, &meh);
	// TSinsert(tree, oke);

	// oke = TSnodcreate("y", k_int, &k);
	// TSinsert(tree, oke);

	// oke = TSnodcreate("z", k_int, &kk);
	// TSinsert(tree, oke);

	// struct var *res;
	// res = TSsearch(tree, "y");

	// // printf("%d\n", (*(int *)(oke->data)) );
	// printf("%d\n", res );


	// printf("%d\n", (*(int *)(res->data)) );



	// int x;
	// while( (x = get_token(f, s)) != EOF ) {
	// 	printf("%d String       %s\n", x, s->str);
	// 	printf("%d Alloc        %d\n", x, s->alloc);
	// 	printf("%d Length       %d\n\n", x, s->length);
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
					// bin_tree *class = malloc(sizeof(bin_tree));

					// find Main v liste tried, ak existuje return semanticka chyba
					// ak neexistuje, ADD main 
					printf("Main Success : %s\n", s->str);
					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
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
					// find ID triedy v liste tried, ak existuje return semanticka chyba
					// ak neexistuje, ADD ID do tried 

					printf("ID Success : %s\n", s->str);
					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
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
								// pozrieť v tabulke či existuje, ak áno, semanticka chyba, ak nie tak ho tam pridaj
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
										}
									}
								case char_rovnasa:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
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
								// pozrieť v tabulke či existuje, ak áno, semanticka chyba, ak nie tak ho tam pridaj
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
								case char_rovnasa:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
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
								// pozrieť v tabulke či existuje, ak áno, semanticka chyba, ak nie tak ho tam pridaj
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
								case char_rovnasa:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
								// pozrieť do tabulky či existuje, ak áno semanticka chyba, ak nie, pridaj ho tam (premenna)
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
								// pozrieť v tabulke či existuje, ak áno, semanticka chyba, ak nie tak ho tam pridaj
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
										}
									} else {
										if (token != char_LMZatvorka) {
											return ERR_SYNTAX_ERR;
										}
										return result;
									}
							}
						case kw_run:
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:
								// pozrieť v tabulke či existuje, ak áno, semanticka chyba, ak nie tak ho tam pridaj
									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
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
			printf("Class body : }\n");
			return ERR_OK;
		default:
			return ERR_SYNTAX_ERR;
	}

}
int func_params() { // -------------------------------------------------------------------------------------------------------- TODO
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

		case is_id:{
			string *class = malloc(sizeof(string));
			copy_string(s, class);
			printf("%s\n", s->str);
			switch(token = get_token(f,s)) {
				case char_rovnasa:
					printf("=\n");
					if ( (result = expression_solve()) == ERR_OK ) {
						return func_body();
					} else {
						return result;
					}

				case char_LZatvorka:
					printf("(\n");
					if ( (result = func_params()) == ERR_OK && (token = get_token(f,s)) == char_bod_ciarka ) {
						return func_body();
					} else {
						if (token != char_bod_ciarka) {
							return ERR_SYNTAX_ERR;
						}
						return result;
					}
				case char_bodka:{
					if (strcmp(class->str, "ifj16") == 0) {
						switch(token = get_token(f, s)) {
							case kw_readInt:
							case kw_readDouble:
							case kw_length:
							case kw_readString:
							case kw_print:
							case kw_substr:
							case kw_compare:
							case kw_find:
							case kw_sort:
								switch(token = get_token(f, s)) {
									case char_LZatvorka:
										printf("(\n");
										if ((result = func_params()) == ERR_OK && (token = get_token(f,s)) == char_bod_ciarka)	{
											return func_body();
										} else {
											return result;
										}
									default:
										return ERR_SYNTAX_ERR;
								}
							default:
								return ERR_SYNTAX_ERR;

						}
					} else {
						switch(token = get_token(f,s)) {
							case is_id:
								switch(token = get_token(f, s)) {
									case char_bod_ciarka:
										return func_body();
									case char_rovnasa:
										if ( (result = expression_solve()) == ERR_OK ) {
											return func_body();
										} else {
											return result;
										}

									case char_LZatvorka:
										printf("(\n");
										if ((result = func_params()) == ERR_OK && (token = get_token(f,s)) == char_bod_ciarka)	{
											return func_body();
										} else {
											return result;
										}
									default:
										return ERR_SYNTAX_ERR;
								}
							default:
								return ERR_SYNTAX_ERR;
						}
					}
						

				}
				default:
					printf("Error\n");
					return ERR_SYNTAX_ERR;

			}
		}

		case kw_while:
		printf("While\n");
			switch(token = get_token(f,s)) {
				case char_LZatvorka:
				printf("(\n");
					if ( (result = bool_expr()) == ERR_OK && (token = get_token(f,s)) == char_LMZatvorka )	{
						printf("{\n");
						if ((result = func_body()) == ERR_OK) {
							return func_body();
						}
					} else {
						if (token != char_LMZatvorka) {
							return ERR_SYNTAX_ERR;
						}
						return result;
					}
				case char_PMZatvorka:
					printf("}\n");
					return ERR_OK;
				default:
					return ERR_SYNTAX_ERR;		
			}

		case kw_if:
		printf("IF\n");
			switch(token = get_token(f,s)) {
				case char_LZatvorka:
				printf("(\n");
					if ( (result = bool_expr()) == ERR_OK && (token = get_token(f,s)) == char_LMZatvorka )	{
						printf("{\n");
						if ((result = func_body()) == ERR_OK) {
							if ((token = get_token(f,s)) == kw_else && (token = get_token(f,s)) == char_LMZatvorka) {
								printf("ELSE\n{\n");
								if ((result = func_body()) == ERR_OK) {
									return func_body();
								} else {
									return result;
								}
							} else {
								return ERR_SYNTAX_ERR;
							}
						} else {
							return ERR_SYNTAX_ERR;
						}
					} else {
						if (token != char_LMZatvorka) {
							return ERR_SYNTAX_ERR;
						}
						return result;
					}
				case char_PMZatvorka:
					printf("}\n");
					return ERR_OK;
				default:
					return ERR_SYNTAX_ERR;		
			}

		case kw_return:
			printf("return\n");
			if ( (result = expression_solve()) == ERR_OK ) {
			 	return func_body();
			 } else {
			 	return result;
			 }

		case char_PMZatvorka:
			printf("}\n");
			return ERR_OK;
		default:
			return ERR_SYNTAX_ERR;
	}


}
int expression_solve() { // -------------------------------------------------------------------------------------------------------- TODO
	int token;
	while( (token = get_token(f,s) ) != char_bod_ciarka ) {
		printf("%s : %d\n", s->str, token);
	}
	printf("Success ;\n");
	return ERR_OK;
}
int bool_expr() { // -------------------------------------------------------------------------------------------------------- TODO
	int token;
	while( (token = get_token(f,s) ) != char_PZatvorka ) {
		printf("%s\n", s->str);
	}
	printf(")\n");
	return ERR_OK;
}
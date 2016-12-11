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
binList *classes;
bin_tree *current_class;

char *current_func;
char *current_class_name;
char *current_var;



int main(void)
{
	f = fopen("test.txt","r");
	s = malloc(sizeof(string));

	// if(f == NULL || s == NULL)
	// 	return -1;
	// init_string(s);

	classes = malloc(sizeof(binList));
	Biteminit(classes);

	printf("Result of parse : %d\n", root());

	// printf("%d\n", Tree_search(classes, "Yay") != NULL );

	// char *str = "Main";


	// int meh = 5;
	// int k = 6;
	// int kk = 7;


	// bin_tree *class = malloc(sizeof(bin_tree));
	// BinInsertLast(classes, class, str);


	// struct var *oke;
	// oke = TSnodcreate("x", k_int, &meh);
	// TSinsert(class, oke);


	// // printf("%d\n", (*(int *)(oke->data)) );
	// // printf("%d\n", res );

	// printf("%s\n", Tree_search(classes, str)->global->key_val );

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

		case kw_class: {
			bin_tree *class = malloc(sizeof(bin_tree));

			printf("Class Success : %s\n", s->str);
			switch( token = get_token(f,s) ) {
				case kw_main:

					if ( Tree_search(classes, s->str) != NULL )	{ 
						return ERR_DEF_ERR; // pokus o redefiniciu
					}

					BinInsertLast(classes, class, s->str);
					current_class = class;
					current_class_name = malloc(sizeof(char) * strlen(s->str));
					strcpy(current_class_name, s->str);

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
					
					if ( Tree_search(classes, s->str) != NULL )	{ 
						return ERR_DEF_ERR; // pokus o redefiniciu
					}

					BinInsertLast(classes, class, s->str);
					current_class = class;
					current_class_name = malloc(sizeof(char) * strlen(s->str));
					strcpy(current_class_name, s->str);

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
		}
			
		case EOF:
			current_class = NULL;
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
	int return_type;

	switch( (token = get_token(f, s)) ) {
		case kw_static:
			printf("%s\n", s->str);
			token = get_token(f,s);
			return_type = token;
			struct var *new_var;

			switch( token ) {
				case kw_int:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:{

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);


						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:{
									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									printf("(\n");
									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
										printf("{\n");
										if ((result = func_body()) == ERR_OK) {
											return class_body();
										} else {
											return result;
										}
									}
								}
								case char_rovnasa:{

									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);

									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								}
								case char_bod_ciarka:{

									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);

									return class_body();
								}
								default:
									return ERR_SYNTAX_ERR;	 
							}

						default:
							return ERR_SYNTAX_ERR;
						}
					}
				case kw_double:
					printf("%s\n", s->str);
					switch( token = get_token(f, s) ) {
						case is_id:

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);
						
						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

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

									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);


									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);

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

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);

						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:{

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

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
								case char_rovnasa:
									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);


									if ( (result = expression_solve()) == ERR_OK ) {
										return class_body();
									} else {
										return result;
									}
								case char_bod_ciarka:
									if( TSsearch(current_class, current_func) != NULL ) {
										return ERR_DEF_ERR; // redefinicia premennej
									}

									new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
									TSinsert(current_class, new_var);

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

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);

						printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

								if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

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
							if (strcmp(current_class_name, "Main") != 0)	{
								return ERR_DEF_ERR; // pokus o deklaraciu run() mimo Main class
							} 



							current_func = malloc(sizeof(char) * strlen(s->str));
							strcpy(current_func, s->str);

							printf("%s\n", s->str);
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // pokus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									printf("(\n");
									if( (token = get_token(f,s)) == char_PZatvorka && (token = get_token(f,s)) == char_LMZatvorka ) {
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
									}
								default: 
									return ERR_SYNTAX_ERR;
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
	// int return_type;
	while( (token = get_token(f,s) ) != char_PZatvorka ) {
		// switch(token) {
		// 	case kw_int:
		// 	case kw_double:
		// 	case kw_string:
		// 	case kw_boolean:
		// 		// return_type = token;
		// 		switch(token = get_token(f,s)) {
		// 			case is_id:
		// 				switch(token = get_token(f,s)) {
		// 					case char_ciarka:
		// 						continue;
		// 					case char_PZatvorka:
		// 						return ERR_OK;
		// 					default:
		// 						return ERR_SYNTAX_ERR;
		// 				}
		// 			default:
		// 				return ERR_OK;
		// 		}
		// 	default:
		// 		return ERR_SYNTAX_ERR;
		// }
		printf("Param success : %s\n", s->str);
	}
	printf(")\n");
	return ERR_OK;
}
int func_body() {
	int token;
	int result;
	int return_type;

	switch(token = get_token(f,s)) {
		return_type = token;
		struct var *new_var;
		case kw_int:
			printf("%s\n", s->str);


			switch(token = get_token(f,s)) {
				case is_id:
				
				current_var = malloc(sizeof(char) * strlen(s->str));
				strcpy(current_var, s->str);

					

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
			char *class = malloc(sizeof(char) * strlen(s->str));
			strcpy(class, s->str);
			printf("%s\n", class);

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
					printf("%s\n", s->str);
					if (strcmp(class, "ifj16") == 0) {
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
/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ16       											           */
/*Mena riesitelov: Peter Grofcik , Rastislav Pobis, Patrik Krajc , Filip Kolesar*/
/*Loginy riesitelov: xgrofc00, xpobis00, xkrajc17, xkoles06                    */
/*******************************************************************************/

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

	printf("Result of parse : Code %d\n", root());

	// char *str = "Main";


	// int meh = 5;
	// int k = 6;
	// int kk = 7;


	// bin_tree *class = malloc(sizeof(bin_tree));
	// BinInsertLast(classes, class, str);


	// struct var *oke;
	// oke = TSnodcreate("x", k_int, &meh);
	// TSinsert(class, oke);







	// int x;
	// while( (x = get_token(f, s)) != EOF ) {
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

			switch( token = get_token(f,s) ) {
				case kw_main:

					if ( Tree_search(classes, s->str) != NULL )	{ 
						return ERR_DEF_ERR; // pokus o redefiniciu
					}

					BinInsertLast(classes, class, s->str);
					current_class = class;
					current_class_name = malloc(sizeof(char) * strlen(s->str));
					strcpy(current_class_name, s->str);

					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
							if ( (result = class_body()) == ERR_OK ) {
								return root();
							} else {
								return result;
							}
						default:
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

					switch( token = get_token(f,s) ) {
						case char_LMZatvorka:
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
			return 0;
		
		default:
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
			token = get_token(f,s);
			return_type = token;
			struct var *new_var;

			switch( token ) {
				case kw_int:
					switch( token = get_token(f, s) ) {
						case is_id:{

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);


							switch( token = get_token(f,s) ) {
								case char_LZatvorka:{
									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
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
					switch( token = get_token(f, s) ) {
						case is_id:

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);
						
							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
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
					switch( token = get_token(f, s) ) {
						case is_id:

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);

							switch( token = get_token(f,s) ) {
								case char_LZatvorka:{

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
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
					switch( token = get_token(f, s) ) {
						case is_id:

						current_func = malloc(sizeof(char) * strlen(s->str));
						strcpy(current_func, s->str);

							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

								if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // poklus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									if( ((result = func_params()) == ERR_OK) && (token = get_token(f,s)) == char_LMZatvorka ) {
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

							switch( token = get_token(f,s) ) {
								case char_LZatvorka:

									if (TSfuncsearch(current_class, current_func) != NULL) {
										return ERR_DEF_ERR; // pokus or redefine
									}
									
									struct func *newfunc = TSFnodcreate(current_func, return_type);
									TSFinsert(current_class, newfunc);

									if( (token = get_token(f,s)) == char_PZatvorka && (token = get_token(f,s)) == char_LMZatvorka ) {
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
	}
	return ERR_OK;
}

// int func_dec_params() { // -------------------------------------------------------------------------------------------------------- TODO
// 	int token;
// 	while( (token = get_token(f,s) ) != char_PZatvorka ) {
// 		switch(token) {
// 			case kw_int:
// 			case kw_double:
// 			case kw_string:
// 			case kw_boolean:
// 				switch(token = get_token(f,s)) {
// 					case is_id:
// 						switch(token = get_token(f,s)) {
// 							case char_ciarka:
// 								continue;
// 							case char_PZatvorka:
// 								return ERR_OK;
// 							default:
// 								return ERR_SYNTAX_ERR;
// 						}
// 					default:
// 						return ERR_OK;
// 				}
// 			default:
// 				return ERR_SYNTAX_ERR;
// 		}
// 	}
// 	return ERR_OK;
// }



int func_body() {
	int token;
	int result;
	int return_type;
		token = get_token(f,s);
		return_type = token;
		// struct var *new_var;

	switch(token) {
		case kw_int:

			switch(token = get_token(f,s)) {
				case is_id:
				
				current_var = malloc(sizeof(char) * strlen(s->str));
				strcpy(current_var, s->str);

				bin_tree *stromcek = malloc(sizeof(bin_tree));

				if (Tree_search(classes, current_class_name)->local->premen == NULL) {
					TSinit(stromcek);
				} else {
					stromcek = Tree_search(classes, current_class_name)->local->premen;
				}

				if (TSsearch(stromcek, current_var) != NULL ) {
					return ERR_DEF_ERR; // redefinicia
				}

				TSfuncinsert(Tree_search(classes, current_class_name), current_func, current_var, return_type, "", stromcek);

				// new_var = TSnodcreate(current_func, return_type, ""); // priradenie premennej cez precedenčku
				// TSinsert(current_class, new_var);


				// bin_tree *meh;

				// struct var *variable = malloc(sizeof(struct var));
				// // variable = TSnodcreate(current_var, return_type,NULL);
				// meh = malloc(sizeof(bin_tree));
				// TSinit(meh);
				// TSfuncinsert(Tree_search(classes, current_class_name)->local->premen, current_func, current_var, return_type, NULL, meh);
				// // variable;


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
			switch(token = get_token(f,s)) {
				case is_id:

				current_var = malloc(sizeof(char) * strlen(s->str));
				strcpy(current_var, s->str);

				bin_tree *stromcek = malloc(sizeof(bin_tree));

				if (Tree_search(classes, current_class_name)->local->premen == NULL) {
					TSinit(stromcek);
				} else {
					stromcek = Tree_search(classes, current_class_name)->local->premen;
				}

				if (TSsearch(stromcek, current_var) != NULL ) {
					return ERR_DEF_ERR; // redefinicia
				}

				TSfuncinsert(Tree_search(classes, current_class_name), current_func, current_var, return_type, "", stromcek);

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
			switch(token = get_token(f,s)) {
				case is_id:

				current_var = malloc(sizeof(char) * strlen(s->str));
				strcpy(current_var, s->str);

				bin_tree *stromcek = malloc(sizeof(bin_tree));

				if (Tree_search(classes, current_class_name)->local->premen == NULL) {
					TSinit(stromcek);
				} else {
					stromcek = Tree_search(classes, current_class_name)->local->premen;
				}

				if (TSsearch(stromcek, current_var) != NULL ) {
					return ERR_DEF_ERR; // redefinicia
				}

				TSfuncinsert(Tree_search(classes, current_class_name), current_func, current_var, return_type, "", stromcek);

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

			switch(token = get_token(f,s)) {
				case char_rovnasa:
					if ( (result = expression_solve()) == ERR_OK ) {
						return func_body();
					} else {
						return result;
					}

				case char_LZatvorka:
					if ( (result = func_params()) == ERR_OK && (token = get_token(f,s)) == char_bod_ciarka ) {
						return func_body();
					} else {
						if (token != char_bod_ciarka) {
							return ERR_SYNTAX_ERR;
						}
						return result;
					}
				case char_bodka:{
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
					return ERR_SYNTAX_ERR;

			}
		}

		case kw_while:
			switch(token = get_token(f,s)) {
				case char_LZatvorka:
					if ( (result = bool_expr()) == ERR_OK && (token = get_token(f,s)) == char_LMZatvorka )	{
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
					return ERR_OK;
				default:
					return ERR_SYNTAX_ERR;		
			}

		case kw_if:
			switch(token = get_token(f,s)) {
				case char_LZatvorka:
					if ( (result = bool_expr()) == ERR_OK && (token = get_token(f,s)) == char_LMZatvorka )	{
						if ((result = func_body()) == ERR_OK) {
							if ((token = get_token(f,s)) == kw_else && (token = get_token(f,s)) == char_LMZatvorka) {
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
					return ERR_OK;
				default:
					return ERR_SYNTAX_ERR;		
			}

		case kw_return:
			if ( (result = expression_solve()) == ERR_OK ) {
			 	return func_body();
			 } else {
			 	return result;
			 }

		case char_PMZatvorka:
			return ERR_OK;
		default:
			return ERR_SYNTAX_ERR;
	}


}
int expression_solve() { // -------------------------------------------------------------------------------------------------------- TODO
	int token;
	while( (token = get_token(f,s) ) != char_bod_ciarka ) {
	}
	return ERR_OK;
}
int bool_expr() { // -------------------------------------------------------------------------------------------------------- TODO
	int token;
	while( (token = get_token(f,s) ) != char_PZatvorka ) {
	}
	return ERR_OK;
}
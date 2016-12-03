#ifndef LEX_KEY
#define LEX_KEY
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

typedef struct
{
	char *str;
	unsigned int Long;
	unsigned int alloc;
}strings;

typedef enum 
{
	k_boolean,
	k_break,
	k_class,
	k_continue,
	k_do,
	k_double,
	k_else,
	k_false,
	k_for,
	k_if,
	k_int,
	k_return,
	k_String,
	k_static,
	k_true,
	k_void,
	k_while
}key;
#endif
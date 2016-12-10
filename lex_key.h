#ifndef LEX_KEY
#define LEX_KEY
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

#define IS_MUL 400
#define IS_DIV 401
#define IS_ADD 402
#define IS_SUB 403
#define IS_CON 404
#define IS_INC 405
#define IS_DEC 406
#define IS_NEG 407
#define IS_READ 408
#define IS_WRITE 409
#define IS_JUMP 410
#define IS_ASSIGN 411
#define IS_CALL_FUNCTION 412
#define IS_CLEAR 413
#define IS_LESS 414
#define IS_GREATER 415
#define IS_LESS_EQUAL 416
#define IS_GREATER_EQUAL 417
#define IS_EQUAL 418
#define IS_NOT_EQUAL 419
#define IS_COPY 420
#define IS_LENGHT 421
#define IS_FIND 422

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
	k_while,
	k_function
}key;

typedef enum
{
  l_id, l_key, l_assign,          // identifikator   klicove slovo   :=
  l_colon, l_int,                 // :   integer
  l_real, l_str, l_bool,          // float   string   bool
  l_add, l_sub, l_mul, l_div,     // +   -   *   /
  l_less, l_lequal, l_greater,    // <   <=  >
  l_gequal, l_equal, l_not,       // >=  =   <>
  l_lparenth, l_rparenth,         // (   )
  l_endl, l_eof, l_enddot,        // ;   EOF .
  l_sep, l_E, l_left, l_reset = 99             // ,   chyba
} lexType;

#endif
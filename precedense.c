#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"

typedef struct{
	int id;
	int token;
	string *value;
} stack_item;

int token_type(int symbol);
int push(stack_item *data);
stack_item* pop();
int isempty();
stack_item* peek();


FILE *f;
string *s;

enum tokenz {
    PLUS_MINUS  = 0,
    MUL_DIV     = 1,  
    REL         = 2, 
    P_Z         = 3,  
   	L_Z         = 4,  
    ID     		= 5,  
    DOLAR       = 6,  
};

// int main()
// {

// 	f = fopen("prec_test.txt","r");
// 	s = malloc(sizeof(string));
// 	int x;
// 	// while( (x = get_token(f, s)) != EOF ) {
// 	// 	printf("%d String       %s\n", x, s->str);
// 	// 	printf("%d Alloc        %d\n", x, s->alloc);
// 	// 	printf("%d Length       %d\n\n", x, s->length);
// 	// }

// char precedence_table [14][14] = {	
// 	{'>','>','<','<','>','>','>','>','>','>','<','>','<','>'},	
// 	{'>','>','<','<','>','>','>','>','>','>','<','>','<','>'},	
// 	{'>','>','>','>','>','>','>','>','>','>','<','>','<','>'},	
// 	{'>','>','>','>','>','>','>','>','>','>','<','>','<','>'},
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},
// 	{'<','<','<','<','<','<','<','<','>','>','<','>','<','>'},	
// 	{'<','<','<','<','<','<','<','<','>','>','<','>','<','>'},	
// 	{'<','<','<','<','<','<','<','<','<','<','>','=','<',' '},
// 	{'>','>','>','>','>','>','>','>','>','>',' ','>',' ','>'},
// 	{'>','>','>','>','>','>','>','>','>','>',' ','>',' ','>'},
// 	{'<','<','<','<','<','<','<','<','<','<','<',' ','<',' '},
// };

// 	stack_item *dolar;
// 	dolar = malloc(sizeof(stack_item));
// 	dolar->id = 6;

// 	int token;
// 	int pocitadlo = 0;

// 	int popped = 0;


// 	stack_item *item;

// 	int meh;
// 	meh = 1;

// 	push(dolar);
// 	while( meh ) {
// 		token = get_token(f,s);
// 		item = malloc(sizeof(stack_item));
// 		if (token == char_PZatvorka) {
// 			meh = 0;
// 			item->id = DOLAR;
// 		} else {
// 			string *s_temp;
// 			s_temp = malloc(sizeof(string));
// 			copy_string(s, s_temp);
// 			item->id = token_type(token);
// 			item->value = s_temp;
// 		}
// 		printf("%d\n", (table[peek()->id][item->id]));
// 		do {
// 			if ( (strcmp(table[peek()->id][item->id], "<") == 0) || (strcmp(table[peek()->id][item->id], "=") == 0) ) {
// 				push(item);
// 				break;
// 				// printf("PUSH %d\n", item->id);
// 			} else {
// 				printf("POP %d\n", pop()->id);
// 			}
// 		} while ((peek()->id != DOLAR) && (item->id != DOLAR));
		
// 	}


// 	// while (  ((token = get_token(f,s)) != char_PZatvorka) || (pocitadlo > -1) ) {
// 	// 	string *temp;
// 	// 	temp = malloc(sizeof(string));
// 	// 	copy_string(s, temp);
// 	// 	stack_item *item;
// 	// 	item = malloc(sizeof(stack_item));
// 	// 	if (token == char_PZatvorka) {
// 	// 		pocitadlo--;
// 	// 		item = dolar;
// 	// 		// printf("%d\n\n", item->id);
// 	// 	} else {
// 	// 		if (token == char_LZatvorka) {
// 	// 			pocitadlo++;
// 	// 		}
// 	// 		item->id = token_type(token);
// 	// 		item->token = token;
// 	// 		item->value = temp;
// 	// 	}

// 	// 	do {
// 	// 		if( (table[peek()->id][item->id] == char_mensi) || (table[peek()->id][item->id] == char_rovnasa) ) {
// 	// 			push(item);
// 	// 			popped = 0;
// 	// 			printf("PUSH %d\n", item->token);
// 	// 			// continue;
// 	// 		} else {

// 	// 			stack_item *blyat;
// 	// 			blyat = malloc(sizeof(stack_item));
// 	// 			blyat->value = malloc(sizeof(string));	
// 	// 			blyat = pop();
// 	// 			printf("POP %d\n", item->token);

// 	// 			popped = 1;
// 	// 		}
// 	// 		if (item->id == 6 && peek()->id == 6) {
// 	// 			printf("%d\n", peek()->id);
// 	// 			return ERR_OK;
// 	// 		}
			
// 	// 	} while (popped);
		
// 	// }

// 	return 1;
// }


int MAXSIZE = 50;       
stack_item *stack[50];     
int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

stack_item* peek() {
   return stack[top];
}

stack_item* pop() {
   stack_item *data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
      return 0;
   }
}

int push(stack_item *data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
      return 1;
   } else {
      printf("Could not insert data, Stack is full.\n");
      return 0;
   }
}



int token_type(int symbol) {

    switch (symbol) {
        case char_plus:
            return PLUS_MINUS;
        case char_minus:
            return PLUS_MINUS;
        case char_star:
            return MUL_DIV;
        case char_slash:
            return MUL_DIV;
        case is_int:
            return ID;
        // case LESS:
        //     printf("'<'");
        // case GREAT:
        //     printf("'>'");
        // case LESS_EQ:
        //     printf("'<='");
        // case GREAT_EQ:
        //     printf("'>='");
        // case EQUAL:
        //     printf("==");
        // case N_EQUAL:
        //     printf("!=");
        // case LEFT_BRACKET:
        //     printf("(");
        // case RIGHT_BRACKET:
        //     printf(")");
        // case INT_LITERAL:
        //     printf("int");
        // case DOUBLE_LITERAL:
        //     printf("dbl");
        // case STRING_LITERAL:
        //     printf("str");
        // case ID:
        //     printf("id");
        // case SEMICOLON:
        //     printf(";");
        // case END_OF_FILE:
        //     printf("$");
        // case T_L:
        //     printf("<");
        // case T_R:
        //     printf(">");
        // case NT_EXPR:
        //     printf("E");
        default:
            printf("DEFAULT TOKEN TYPE %d", symbol);
            return -1;
    }
}
// char precedence_table [14][14] = {	// precedencna tabulka ... extern??
// 	{'>','>','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok +
// 	{'>','>','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok -
// 	{'>','>','>','>','>','>','>','>','>','>','<','>','<','>'},	// riadok *
// 	{'>','>','>','>','>','>','>','>','>','>','<','>','<','>'},	// riadok /
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok <
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok >
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok <=
// 	{'<','<','<','<','>','>','>','>','>','>','<','>','<','>'},	// riadok >=
// 	{'<','<','<','<','<','<','<','<','>','>','<','>','<','>'},	// riadok ==
// 	{'<','<','<','<','<','<','<','<','>','>','<','>','<','>'},	// riadok != 
// 	{'<','<','<','<','<','<','<','<','<','<','>','=','<',' '},	// riadok (
// 	{'>','>','>','>','>','>','>','>','>','>',' ','>',' ','>'},	// riadok )
// 	{'>','>','>','>','>','>','>','>','>','>',' ','>',' ','>'},	// riadok id
// 	{'<','<','<','<','<','<','<','<','<','<','<',' ','<',' '},	// riadok $
// };
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"

int push(char data);
char pop();
int isempty();
char peek();


FILE *f;
string *s;


// int main()
// {
// 	const char table[7][7] = {
// //             0    1    2    3    4    5    6
// //             + -  * /  rel  (    )    ID   $
// /*  0 + - */ { '>', '<', '>', '<', '>', '<', '>' },
// /*  1 * / */ { '>', '>', '>', '<', '>', '<', '>' },
// /*  2 rel */ { '<', '<', ' ', '<', '>', '<', '>' },
// /*  3 (   */ { '<', '<', '<', '<', '=', '<', ' ' },
// /*  4 )   */ { '>', '>', '>', ' ', '>', ' ', '>' },
// /*  5 id  */ { '>', '>', '>', ' ', '>', ' ', '>' },
// /*  6 $   */ { '<', '<', '<', '<', ' ', '<', ' ' }
// };

// enum tokenz {
//     PLUS_MINUS  = 0,
//     MUL_DIV     = 1,  
//     REL         = 2, 
//     P_Z         = 3,  
//    	L_Z         = 4,  
//     ID     		= 5,  
//     DOLAR       = 6,  
// };

// 	int token;
// 	int pocitadlo = 0;


// 	f = fopen("prec_test.txt","r");
// 	s = malloc(sizeof(string));


// 	token = get_token(f,s);

// 	printf("%d\n", PLUS_MINUS == 0);





// 	printf("%d\n", atoi((s->str)));

// 	// push('$');

// 	// while( (token = get_token(f,s)) != char_PZatvorka || (pocitadlo > 0) ) {
// 	// 	if (token == char_PZatvorka) {
// 	// 		pocitadlo--;
// 	// 	}

// 	// 	if ( strcmp('>',meh(peek(), )) == 0 )	{
// 	// 		push(s->str);
// 	// 	}
// 	// 	if ( strcmp('<',meh(peek(), )) == 0 )	{
// 	// 		printf("%s\n", pop());
// 	// 	}
// 	// }







// 	return 0;
// }


int MAXSIZE = 50;       
int stack[8];     
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

char peek() {
   return stack[top];
}

char pop() {
   char data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
      return 0;
   }
}

int push(char data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
      return 1;
   } else {
      printf("Could not insert data, Stack is full.\n");
      return 0;
   }
}
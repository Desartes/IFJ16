#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "scanner.c"

int main(void)
{
	FILE *f = fopen("test.txt","r");
	string *s;

	s = malloc(sizeof(string));
	if(f == NULL || s == NULL)
		return -1;
	init_string(s);
	int x;
	while(x  != EOF	){
		x = get_token(f,s);
		printf("%i\n", x);
		for(int i = 0; s->str[i] != '\0'; i++){
			putchar(s->str[i]);
		}
		printf("\n");
		
	}
	return 0;
}
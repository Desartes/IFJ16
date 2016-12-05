#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
// #include "scanner.c"

int program();

	FILE *f;
	string *s;

int main(void)
{
	f = fopen("test.txt","r");
	s = malloc(sizeof(string));

	if(f == NULL || s == NULL)
		return -1;
	init_string(s);


	program();



	return 0;
}

int first_time = 0;

int program() {
	int x;
/* Class Main { 
***********************************************************************/
	if (first_time == 0) {
		if ( (x = get_token(f,s)) == kw_class) {
			if ( (x = get_token(f,s)) == kw_main ) {
				if ((x = get_token(f,s)) == char_LMZatvorka) {
					first_time++;
					program();
				} else {
					printf("Error 1 %d\n", x);
					// Error
				}
			} else {
				printf("Error 2 %d\n", x);
				// Error
			}
		} else {
			printf("Error 3 %d\n", x);
			// Error
		}
	} else {
		if ( (x = get_token(f,s)) == kw_class) {
			if ( (x = get_token(f,s)) == is_id ) {
				if ((x = get_token(f,s)) == char_LMZatvorka) {
					/* code */
				} else {
					printf("Error 1 %d\n", x);
						// Error
				}
			} else {
				printf("Error 2 %d\n", x);
			// Error
			}
		} else {
			printf("Error 3 %d\n", x);
			// Error
		}
	}
/**********************************************************************/
	return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
// #include "scanner.c"

int main(void)
{
	FILE *f = fopen("test.txt","r");
	string *s;
	s = malloc(sizeof(string));

	if(f == NULL || s == NULL)
		return -1;
	init_string(s);
	int x;




	if (x == kw_class) {
		
	}

		
	}
	return 0;
}

int first_time = 0;

int program() {


	if (first_time)	{
		if ( (x = get_token(f,s)) == kw_class) {
			if ( (x = get_token()) == kw_main ) {
				if ( (x = get_token()) == kw_run ) {
					/* code */
				}
			}
		}
	}





	if ( (x = get_token(f,s)) == kw_class) {
		if ( (x = get_token()) == kw_main ) {
			if ( (x = get_token()) ==  )
			{
				/* code */
			}
		}
	}

}
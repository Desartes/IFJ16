#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"
#include "ial.h"

int main(int argc, char **argv)
{
	/*FILE *file=fopen(argv[1],"r");
	if(file==NULL)
	{
		fprintf(stderr,"Chyba citania suboru\n");
		return 1;
	}*/

	/*char target[] = "ABC ABCDAB ABCDABCDABDE";
	char *ch = target;
	char pattern[] = "ABCDABD";
	int i;

	i = kmp(target, pattern, strlen(target), strlen(pattern));
	if (i >= 0)
		printf("matched @: %s\n%d\n", ch + i,i);
	else
		printf("NoT MATCHED\n");
	return 0;
	*/
	int a[] = { 7, 12, 1, -2, 0, 15, 4, 11, 9};

	int i;
	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);

	quickSort( a, 0, 8);

	printf("\n\nSorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
}
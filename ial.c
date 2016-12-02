#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "err.h"

int *mall_kmp(char *pod, int len_p)
{
	int k=-1;
	int i=1;
	int *pi_len=malloc(sizeof(int)*len_p);
	
	if(!pi_len)
		err(ERR_INTERNAL_ERR);
	
	pi_len[0]=k;

	for (i=1; i < len_p; i++) {
		while (k > -1 && pod[k+1] != pod[i])
			k = pi_len[k];
		if (pod[i] == pod[k+1])
			k++;
		pi_len[i] = k;
	}
	return pi_len;




}

int kmp(char *ret,char *pod,int len_r, int len_p)
{
		int i;
		int *pi_len = mall_kmp(pod, len_p);
		int k=-1;

		if(!pi_len)
			err(ERR_INTERNAL_ERR);

		for (i = 0; i < len_r; i++) {
		while (k > -1 && pod[k+1] != ret[i])
			k = pi_len[k];
		if (ret[i] == pod[k+1])
			k++;
		if (k == len_p - 1) {
			free(pi_len);
			return i-k;
		}
	}
	free(pi_len);
		err(ERR_INTERNAL_ERR);
}


int partition( int PS_med[], int left, int right) {
   int med=PS_med[left], i_left=left, k_right=right+1, help;
		
   while( 1)
   {	
		
   		do ++i_left; while( PS_med[i_left] <= med && i_left <= right );
   		do --k_right; while( PS_med[k_right] > med );

		if(i_left>=k_right)
			break;
		help=PS_med[i_left];
		PS_med[i_left]=PS_med[k_right];
		PS_med[k_right]=help;   			

   }
   help=PS_med[left];
   PS_med[left]=PS_med[k_right];
   PS_med[k_right]=help;
   return k_right;
}

void quickSort( int pole[], int left, int right)
{
   int help;

   if( left < right ) 
   {
       help = partition( pole, left, right);
       quickSort( pole, left, help-1);
       quickSort( pole, help+1, right);
   }
	
}

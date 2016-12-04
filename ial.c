#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ial.h"
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


void TSinit(bin_tree *table)
{
	table->global=table->local=NULL;
}
void TSinit_local(bin_tree *table, bin_tree *global_table)
{
	table->global=global_table->local;
	table->local=NULL;
}

struct node *TSnodcreate(char *name,key typ, void *data)
{
	struct node *nod;
	if((nod=malloc(sizeof(struct node)))==NULL)
		err(ERR_INTERNAL_ERR);
	strncpy(nod->key_val,name,BUFFER_SIZE);
	nod->define=false;
	nod->f_data=nod->Rnode=nod->Lnode=NULL;
	name=NULL;

	switch(typ)
	{
		case k_boolean:
			nod->data=(bool *) malloc(sizeof(bool));
			break;
		case k_int:
			nod->data=(int *) malloc(sizeof(int));
			break;
		case k_String:
			nod->data=(char *) malloc(sizeof(strlen(data)));
			break;
		case k_double:
			nod->data=(double *) malloc(sizeof(double));
			break;
		default:
			free(nod);
			err(ERR_INTERNAL_ERR);
	}
	if(nod->data!=NULL)
	{
			switch(typ)
			{
			case k_boolean:
				*((bool *)nod->data) = *(bool *)data;
				break;
			case k_int:
				*((int *)nod->data) = *(int *)data;
				break;
			case k_String:
				*((char *)nod->data) = *(char *)data;
				break;
			case k_double:
				*((double *)nod->data) = *(double *)data;
				break;
			default:
				free(nod);
				err(ERR_INTERNAL_ERR);
			}
	}
	else
	{
		free(nod);
		err(ERR_INTERNAL_ERR);
	}
	return nod;


}

struct node * TSFnodcreate(char * name, key typ,bool define,struct f_elem *elem)
{
	struct node *nod;
	if((nod=malloc(sizeof(struct node)))==NULL)
		err(ERR_INTERNAL_ERR);
	nod->typ=k_function;
	strncpy(nod->key_val,name,BUFFER_SIZE);
	name=NULL;
	nod->Rnode=nod->Lnode=NULL;

	if((nod->f_data=(f_data *)malloc(sizeof(f_data)))==NULL)
		err(ERR_INTERNAL_ERR);

	switch(typ)
	{
		case k_boolean:
			nod->data=(bool *) malloc(sizeof(bool));
			break;
		case k_int:
			nod->data=(int *) malloc(sizeof(int));
			break;
/*		case k_String:
			nod->data=(char *) malloc(sizeof(strlen(data)));
			break; */
		case k_double:
			nod->data=(double *) malloc(sizeof(double));
			break;
		default:
			free(nod);
			err(ERR_INTERNAL_ERR);
	}
	if(nod->data==NULL)
	{
			err(ERR_INTERNAL_ERR);
	}

	((f_data *)nod->f_data)->ret = typ;
	((f_data *)nod->f_data)->elem = elem;
	((f_data *)nod->f_data)->define = define;
	if((((f_data *)nod->f_data)->table=(bin_tree *)malloc(sizeof(bin_tree)))==NULL)
		err(ERR_INTERNAL_ERR);
	TSinit(((f_data *)nod->f_data)->table);
	Listinit(&((f_data *)nod->f_data)->ins_list);
	return nod;
}


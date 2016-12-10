#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ial.h"
#include "err.h"

/*
*	Pomocna funkcia pre KMP algoritmus pre alokaciu pamete o dlzky vyhladavaneho podretazca
*/
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
/*
*	Knuth-Morris-Prattov algoritmus
*/
int kmp(char *ret,char *pod)
{
	int len_r=strlen(ret);
	int len_p=strlen(pod);
	int i;
	int *pi_len = mall_kmp(pod, len_p);
	int k=-1;

	if(!pi_len)
		err(ERR_INTERNAL_ERR);

	for (i = 0; i < len_r; i++) 
	{
		while (k > -1 && pod[k+1] != ret[i])
			k = pi_len[k];
		if (ret[i] == pod[k+1])
			k++;
		if (k == len_p - 1) 
		{
			free(pi_len);
			return i-k;
		}
	}
	free(pi_len);
	return 0;
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

/*
*	Quicksort algoritmus rieseny rekurzivne 
*/
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

/*
*	Funkcie na pracu s listom obsahujucim parametre jednotlivej funkcie
*/
void Listinit(tList *L){
	L->first = NULL;
	L->last = NULL;
	L->active = NULL;
}

void DisposeList(tList *L){
	while(L->first != NULL){
		tListItemPtr item = L->first->next;
		free(L->first);
		L->first = item;
	}
}

void InsertFirst(tList *L,tInstr instr){
	struct listItem *newItem = malloc(sizeof(struct listItem));
	if(newItem == NULL)
		err(ERR_INTERNAL_ERR);

	newItem->instruction = instr;
	newItem->next = L->first;
	L->first = newItem;
}

void InsertLast(tList *L, tInstr instr){
	struct listItem *newItem = malloc(sizeof(struct listItem));
	if(newItem == NULL)
		err(ERR_INTERNAL_ERR);
	newItem->instruction = instr;

	if(L->first != NULL){
		L->last->next = newItem;
		L->last = newItem;
	}else
		L->first = L->last = newItem;
}


/*
*	Funkcie na pracu s TS tabulkou/tabulkami pomocou algoritmov binnary tree
*/
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
		case k_String:
			nod->data=(char *) malloc(sizeof(BUFFER_SIZE));
			break; 
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

int TSinsert(bin_tree *table, struct node *in)
{
	return TSNinsert(&table->local, in);
}

int TSNinsert(struct node **mark_nod, struct node *in)

{
	if(*mark_nod==NULL || (strcmp(in->key_val,(*mark_nod)->key_val)==ERR_OK) )
	{
		if(*mark_nod==NULL)
		{
			*mark_nod=in;
			return ERR_OK;
		}
		else
		{
			(*mark_nod)->data=in->data;
			return ERR_OK;
		}
	}
	else 
	{

		if(strcmp(in->key_val,(*mark_nod)->key_val)>ERR_OK)
			return TSNinsert(&(*mark_nod)->Rnode,in);
		else
			return TSNinsert(&(*mark_nod)->Lnode,in);
	}
}

struct node * TSsearch(bin_tree * table, char * key)
{
	struct node *search=TSNsearch(table->local,key);
	if(search!=NULL)
		return search;
	else
		return TSNsearch(table->global,key);

}

struct node * TSNsearch(struct node *mark_nod, char *key)
{
	if(mark_nod==NULL)
		return NULL;
	if(strcmp(mark_nod->key_val,key)==ERR_OK)
		return mark_nod;
	else
	{
		if(strcmp(mark_nod->key_val,key)>ERR_OK)
			return TSNsearch(mark_nod->Lnode,key);
		else
			return TSNsearch(mark_nod->Rnode,key);
	}
}


int TScopy(bin_tree * table, bin_tree * N_table)
{
	N_table->global=table->global;
	N_table->local=TSNcopy(table->local);
	return ERR_OK;
}
struct node *TSNcopy(struct node *nod)
{
	struct node *NEW;
	if((NEW=TSnodcreate(nod->key_val,nod->typ,nod->data))!=NULL)
	{
		NEW->Rnode=TSNcopy(nod->Rnode);
		NEW->Lnode=TSNcopy(nod->Lnode);
		return NEW;
	}
	return NULL;
}

int TSdispose(bin_tree * table)
{
	TSNdispose(&table->local);
	table->local=NULL;
	return ERR_OK;


}
int TSNdispose(struct node ** mark_nod)
{
	if(*mark_nod!=NULL)
	{
		TSNdispose(&((*mark_nod)->Lnode));
		TSNdispose(&((*mark_nod)->Rnode));


		if((*mark_nod)->typ==k_function )
		{
			TSdispose(((f_data *)(*mark_nod)->f_data)->table);
			TSFpardispose(((f_data *)(*mark_nod)->f_data)->elem);
			free(((f_data *)(*mark_nod)->f_data)->table);
			DisposeList(&((f_data *)(*mark_nod)->f_data)->ins_list);
			free((*mark_nod)->f_data);
		}
		free((*mark_nod)->data);
		free(*mark_nod);
	}
	return ERR_OK;
}
int TSFpardispose(struct f_elem *pList)
{
	struct f_elem * parameter;
	while(pList!=NULL);
	{

		parameter=pList;
		pList=pList->next;
		free(parameter);
	}

	return ERR_OK;
}
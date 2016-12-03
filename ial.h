#ifndef IAL_H_
#define IAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex_key.h"
#include "ilist.h"

int *mall_kmp(char *pod, int len_p);
int kmp(char *ret,char *pod,int len_r, int len_p);
void quickSort( int[], int, int);
int partition( int[], int, int);

struct node
{
	char key_val[BUFFER_SIZE];
	bool define;
	void *data;
	void *f_data;
	key typ;

	struct node *Lnode;
	struct node *Rnode;
};

typedef struct
{
	struct node *global;
	struct node *local;
}bin_tree;

struct f_elem
{
	char key_val[BUFFER_SIZE];
	key typ;
	struct f_elem *next;
}

typedef struct 
{
	key ret;
	bool define;
	tlist ins_list;
	bin_tree *table;
	struct f_elem *elem;
}f_data;

void TSinit(bin_tree *table);
void TSinit_local(bin_tree *table, bin_tree *global_table);
struct node *TSnodecreate(char *name, key typ, void *data);
struct node * TSFnodcreate(char * name, key typ,bool define,struct f_elem *elem);
#endif
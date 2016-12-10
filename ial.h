#ifndef IAL_H_
#define IAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex_key.h"
#include "err.h"


#define I_SORT 27


/*
*	Knuth-Morris-Prattov algoritmus
*	Quick sort algoritmus
*/
int *mall_kmp(char *pod, int len_p);
int kmp(char *ret,char *pod);
void quickSort( int[], int, int);
int partition( int[], int, int);

/*
*	Praca s listovou strukturov opisujucov obsah funkcii
*/
typedef struct {
  int instType;
  void *addr1;
  void *addr2;
  void *addr3;
  key typ;
} tInstr;

typedef struct listItem {
  tInstr instruction;
  struct listItem *next;
} *tListItemPtr;


typedef struct {
  struct listItem *first;
  struct listItem *last;
  struct listItem *active;
} tList;

void Listinit(tList *L);
void DisposeList(tList *L);
void InsertFirst(tList *L,tInstr instr);
void InsertLast(tList *L, tInstr instr);

/*
*	Praca s TS-tabulkou pomocou binnary tree
*/ 
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
};

typedef struct 
{
	key ret;
	bool define;
	tList ins_list;
	bin_tree *table;
	struct f_elem *elem;
}f_data;

void TSinit(bin_tree *table);/*funkcie na inicializaciu prazdneho binnary tree*/
void TSinit_local(bin_tree *table, bin_tree *global_table);

struct node *TSnodcreate(char *name, key typ, void *data);/*vytvorenie uzlu pre binnary tree prva pre premenne druha pre funkcie*/
struct node * TSFnodcreate(char * name, key typ,bool define,struct f_elem *elem);

int TSinsert(bin_tree *table, struct node *in);//priradenie uzla do binnary tree , volas len prvu druha je volana prvou
int TSNinsert(struct node **mark_nod, struct node *in);

struct node * TSsearch(bin_tree *table, char *key);//vyhladanie uzla v binnary tree, opet volas len prvu
struct node * TSNsearch(struct node *mark_nod, char *key);

int TScopy(bin_tree *table, bin_tree *N_table);//rekurzivne skopiruje cely binnary tree , opet volas len prvu
struct node *TSNcopy(struct node *nod);

int TSdispose(bin_tree * table);//odstrani cely binnary tree vratane elementov premennych pre funkcie v pliste opet volas len prvy
int TSFpardispose(struct f_elem *pList);
int TSNdispose(struct node ** mark_nod);

#endif
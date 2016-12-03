#include "ilist.h"
#include "err.h"

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
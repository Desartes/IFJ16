#include <stdio.h>
#include <stdlib.h>
#include "instrlist.h"
#include "err.h"
tList *instr_list;

void listInit(tList *L){

	L->first = NULL;
	L->active = NULL;
	L->last = NULL;
	
}

void listFree(tList *L){

	for(L->active = L->first;L->first != NULL;L->first = L->active){
			L->active = L->first->nextItem;		//zachovavame pointer na nastupny prvek
			free(L->first);
		}
	L->last = NULL;

}

void listInsertLast(tList *L, tInstr I){

	tListItem * item;
	item = malloc(sizeof(tListItem));

	if(item == NULL){
		printf("Allocation error");
		exit(99);
	}

	item->instruction = I;
	item->nextItem = NULL;

	if(L->first != NULL){
	    L->last->nextItem = item;
	    L->last = item;
	}    
	else{
		L->first = L->last = item;
	}

}

#ifdef DEBUG
void print_instr(tInstr *instr) {
    printf("%p ", (void *)instr);

    switch (instr->instType) {
        case I_ADD:
            printf("ADD"); break;
        case I_SUB:
            printf("SUB"); break;
        case I_MUL:
            printf("MUL"); break;
        case I_DIV:
            printf("DIV"); break;
        case I_F_ADD:
            printf("FADD"); break;
        case I_F_SUB:
            printf("FSUB"); break;
        case I_F_MUL:
            printf("FMUL"); break;
        case I_F_DIV:
            printf("FDIV"); break;
        case I_VAL_PUSH:
            printf("VAL_PUSH"); break;
        case I_TAB_PUSH:
            printf("TAB_PUSH"); break;
        case I_CONV:
            printf("CONV"); break;
        case I_SWAP:
            printf("SWAP"); break;
        case I_CONCAT:
            printf("CONCAT"); break;
        case I_LESS:
            printf("LESS"); break;
        case I_GREAT:
            printf("GREAT"); break;
        case I_LESS_EQ:
            printf("LES_EQ"); break;
        case I_GREAT_EQ:
            printf("GREAT_EQ"); break;
        case I_EQ:
            printf("EQ"); break;
        case I_N_EQ:
            printf("N_EQ"); break;
        case I_F_LESS:
            printf("F_LESS"); break;
        case I_F_GREAT:
            printf("F_GREAT"); break;
        case I_F_LESS_EQ:
            printf("F_LES_EQ"); break;
        case I_F_GREAT_EQ:
            printf("F_GREAT_EQ"); break;
        case I_F_EQ:
            printf("F_EQ"); break;
        case I_F_N_EQ:
            printf("F_N_EQ"); break;
        case I_GOTO:
            printf("GOTO"); break;
        case I_LABEL:
            printf("LABEL"); break;
        case I_MOVSTACK:
            printf("MOVSTACK"); break;
        case I_RETURN:
            printf("RETURN"); break;
        case I_CALL:
            printf("CALL"); break;
        default:
            printf("%d", instr->instType);
    }

    printf(" %p %p %p, ", instr->addr1, instr->addr2, instr->addr3);
}

void print_instr_list() {
    tInstr *instr;

    listFirst(instr_list);

    while (instr_list->active != NULL) {
        instr = listGetData(instr_list);

        print_instr(instr);
        printf("\n");

        listNext(instr_list);
    }
}
#endif

void add_instr(int type, void * add1, void * add2, void * add3) {
    tInstr instr = { type, add1, add2, add3 };

    listInsertLast(instr_list, instr);

#ifdef DEBUG
    printf("instr: ");
    print_instr(&instr);
#endif
}

void set_function_beginning(tListItem **item) {
    add_instr(IN_LABEL, NULL, NULL, NULL);
    *item = instr_list->last;
}

void listFirst(tList *L){

	 L->active = L->first;

}

void listNext(tList *L){

	if (L->active != NULL)
  		L->active = L->active->nextItem;

}

tInstr *listGetData(tList *L)
{

  if (L->active == NULL)
  {
    printf("Chyba, zadna instrukce neni aktivni");
    exit(99);
  }
  else return &(L->active->instruction);

}

void listGoto(tList *L, tListItem *gotoInstr)
{
  L->active =  gotoInstr;
}

void *listGetPointerLast(tList *L)
{
	return (void *)L->last;
}
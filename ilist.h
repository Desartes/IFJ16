
#ifndef I_LIST_H
#define I_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int instType;
  void *addr1;
  void *addr2;
  void *addr3;
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
int  GetInstruction( tList *L );
#endif
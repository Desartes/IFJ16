/**
*	Projekt:Implementace interpretu imperativniho jazyka IFJ2016
*	Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar
*	Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE	20

struct node{
	char name[SIZE]
	void *IdenData;
	void *FunData;
	bool defined ;

	struct *LNode;
	struct *RNode;
};

typedef struct{
	struct node *local;
	struct node *global;
}btree;
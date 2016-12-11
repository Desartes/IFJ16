/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ16                                       */
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar*/
/*Loginy riesitelov: xgrofc00, xpobis00, xkrajc17,xkoles06                    */
/*******************************************************************************/

#ifndef _PRECEDENSE_H
#define _PRECEDENSE_H
#define STACK_SIZE 50

typedef struct{
  int id;
  int token;
  char * value;
} stack_item;

typedef struct {
  stack_item *arr[STACK_SIZE];  
  int top;
} tStack;

enum tokenz{
    PLUS        =0,
    MINUS       =1,
    MUL         =2,
    DIV         =3,
    L_Z         =4,
    P_Z         =5,
    MENSI       =6,
    VACSI       =7,
    MENSI_R     =8,
    VACSI_R     =9,
    ROVNY       =10,
    NEROVNY     =11,
    ID          =12,
    END         =13,
};


#endif
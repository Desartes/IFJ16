/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ16                                       */
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar*/
/*Loginy riesitelov: xgrofc00, xpobis00, xkrajc17,xkoles06                    */
/*******************************************************************************/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "scanner.h"
#include "err.h"
#include "precedense.h"

char precedence_table [14][14] = {  
//            +   -   *    /  (   )   <   >   <=  >=  ==  !=  ID  $
/*0 + */    {'>','>','<','<','<','>','>','>','>','>','>','>','<','>'},
/*1 - */    {'>','>','<','<','<','>','>','>','>','>','>','>','<','>'},
/*2 * */    {'>','>','>','>','<','>','>','>','>','>','>','>','<','>'},
/*3 / */    {'>','>','>','>','<','>','>','>','>','>','>','>','<','>'},
/*4 ( */    {'<','<','<','<','<','=','<','<','<','<','<','<','<',' '},
/*5 ) */    {'>','>','>','>',' ','>','>','>','>','>','>','>',' ','>'},
/*6 < */    {'<','<','<','<','<','>','>','>','>','>','>','>','<','>'},
/*7 > */    {'<','<','<','<','<','>','>','>','>','>','>','>','<','>'},
/*8 <= */   {'<','<','<','<','<','>','>','>','>','>','>','>','<','>'},
/*9 >= */   {'<','<','<','<','<','>','>','>','>','>','>','>','<','>'},
/*10 == */  {'<','<','<','<','<','>','<','<','<','<','<','<','<','>'},
/*11 != */  {'<','<','<','<','<','>','<','<','<','<','<','<','<','>'},
/*12 i */   {'>','>','>','>',' ','>','>','>','>','>','>','>',' ','>'},
/*13 $ */   {'<','<','<','<','<',' ','<','<','<','<','<','<','<',' '},
};

int token_type(int symbol) {
    switch (symbol) {
        case char_plus:
            return PLUS;
        case char_minus:
            return MINUS;
        case char_star:
            return MUL;
        case char_slash:
            return DIV;
        case char_LZatvorka:
            return L_Z;
        case char_PZatvorka:
            return P_Z;
        case  char_mensi:
            return MENSI;
        case char_vacsi:
            return VACSI;
        case char_mensirovny:
            return MENSI_R;
        case char_vacsirovny:
            return VACSI_R;
        case char_rovny:
            return ROVNY;
        case char_nerovny:
            return NEROVNY;
        case is_int:
        case is_double:
        case kladny_exp_D:
        case zaporny_exp_D:
        case kladny_exp_I:
        case zaporny_exp_I:
           return ID;
        case char_rovnasa: case char_PMZatvorka:
          return END;
        default:
          return END; 
    }
    return 1;
}

void stackInit ( tStack* s ) {
  s->top = -1;
}

int stackEmpty ( const tStack* s ) {
  return (s->top == -1);
}

int stackFull ( const tStack* s ) {
  return (s->top == (STACK_SIZE-1));
}



void stackPush( tStack *s, stack_item* item) {
  s->top++;
  s->arr[s->top] = item;
}

int main(void)
{
  FILE *f =fopen("test.txt","r");
  string *s = malloc(sizeof(string));
  if(f == NULL || s == NULL)
    return 0;
  tStack *stack=malloc(sizeof(tStack));
  stack_item *item=malloc(sizeof(stack_item));
  item->is_double=13;
  stackInit(stack);
  stackPush(stack,item);
  int token ;
  printf("%i %i\n",item->id ,stack->arr[stack->top]->id);
  do{
    stack_item *item=malloc(sizeof(stack_item));
    token = get_token(f,s);
    item->id=token_type(token);
    item->token = token;
    item->value = malloc(sizeof(strlen(s->str))+1);
    strcpy(item->value,s->str);
    printf("%s \n",item->value);
    switch(precedence_table[stack->arr[stack->top]->id][item->id]){
      case ' ':
        printf("EROOR ' '\n");
        return 0;
      case '<':
        printf("PUSH\n");
        break;
      case '>':
        printf("POP\n");
        break;
     }
  }while(item->value=='\0');
  return 0;
} 
// hodnota value stack->arr[stack->top]->value
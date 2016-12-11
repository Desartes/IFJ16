#ifndef _ILIST_H
#define _ILIST_H
#include"scanner.h"
#include"ial.h"
//identifikator
#define ID       0




// seznam instrukci
typedef enum insType{
 
 I_ADD,         // 0   // operace pro int nad dvema prvky na zasobniku
 I_SUB,        // 1
 I_MUL,        // 2
 I_DIV ,        // 3
 I_TAB_PUSH ,   // 8   // vloz na zasobnik
 I_VAL_PUSH ,   // 9
 I_CONV  ,      // 10   // preved vrchol zasobniku z int na double
 I_SWAP ,       // 11  // vymen horni dva prvky zasobniku
 I_CONCAT ,     // 12  // spoj horni dva retezce na zasobniku
I_LESS    ,    // 13  // porovna horni dva inty
 I_GREATER ,       //14
 I_LESS_EQ  ,   // 15
 I_GREAT_EQ ,    //16
 I_EQ    ,      // 17
 I_N_EQ  ,      // 18

 I_GOTO    ,    // 25
 IN_IFNGOTO ,    // 26
IN_JMP_WHILE ,   //27

 I_DEC ,         //28
 I_INC  ,       // 29
 IN_LABEL ,       //32
 IN_MOVSTACK,     //33
 IN_RETURN   ,    //34
 IN_CALL ,        //35
 IN_CONV_SYMBOL, // 36
  IN_MOV  ,        //37

 IN_INT_TO_STR ,  //38
 IN_DBL_TO_STR,  // 39

 IN_MAX    ,      //40
 I_READ,
 I_WRITE,
 I_STOP,
 I_LABEL,
} insType;
//specialni znaky
#define END_OF_FILE    60



// vsechny tokeny maji hodnotu mensi nez TOKEN_MAX
#define TOKEN_MAX 72

// pomocne defines pro zjednoduseni kodu
// instrukce pro double se daji ziskat jako (instrukce pro int) + F_***_OFFSET
#define F_ARITH_OFFSET  (IN_F_ADD - IN_ADD)
#define F_REL_OFFSET    (IN_F_LESS - IN_LESS)

void listInit(tList *L); // funkce inicializuje seznam instrukci
void listFree(tList *L); // funkce dealokuje seznam instrukci
void listInsertLast(tList *L, tInstr I); // vlozi novou instruci na konec seznamu
void listFirst(tList *L); // zaktivuje prvni instrukci
void listNext(tList *L); // aktivni instrukci se stane nasledujici instrukce
tInstr *listGetData(tList *L); // vrati aktivni instrukci
void listGoto(tList *L, tListItemPtr *gotoInstr); // nastavime aktivni instrukci podle zadaneho ukazatele
void *listGetPointerLast(tList *L); // vrati ukazatel na posledni instrukci

void add_instr(int type, void * ptr1, void * ptr2, void * ptr3);
void set_function_beginning(tListItemPtr **item);
void print_instr(tInstr *instr);
void print_instr_list();

#endif
/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ2016       											           */
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar*/
/*Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    */
/*******************************************************************************/
#include "string.h"

#ifndef _SCANNER_H
#define _SCANNER_H

//identifikator
#define ID       0

//keywords
#define BOOLEAN    1
#define BREAK      2
#define CLASS      3
#define CONTINUE   4
#define DO         5
#define DOUBLE     6
#define ELSE       7
#define FALSE      8
#define FOR        9
#define IF         10
#define INT        11
#define RETURN     12
#define STRING     12
#define STATIC     14
#define TRUE       15
#define VOID       16
#define WHILE      17
//povinne
#define MAIN 18
#define RUN  19

//operatory
#define PLUS     20
#define MINUS    21
#define MUL      22
#define DIV      23
#define LESS     24 
#define GREAT    25 
#define LESS_EQ  26 
#define GREAT_EQ 27 
#define EQUAL    28 
#define N_EQUAL  29 
#define ASSIGN   30 

//znaky
#define LEFT_VINCULUM  31 // '{'   - pouzivano u trid a funkci
#define RIGHT_VINCULUM 32 // '}'   - pouzivano u trid a funkci
#define LEFT_BRACKET   33 // '('   - pouzivano u funkci a cyklu
#define RIGHT_BRACKET  34 // ')'   - pouzivano u funkci a cyklu
#define SEMICOLON      35 // ';'
#define COMMA          36 // ,

//literaly

#define STRING_LITERAL 50
#define INT_LITERAL    51
#define DOUBLE_LITERAL 52

//specialni znaky
#define E_O_F    120

//chybove hlasky
#define LEX_ERROR    1
//hlavicka funkce simulujici lexikalni analyzator
void setSourceFile(FILE *f);
int get_next_token(char **buffer);
void return_token(int token, char *buffer);

#endif
/**
*   Projekt:Implementace interpretu imperativniho jazyka IFJ2016
*   Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar
*   Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    
**/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// #include "ilist.h"
#include "string.h"
#include "lex.h"
#include "err.h"
FILE *file;
int token; 
string argms; 

typedef struct token_t {
    int token;
    char *buffer;
    struct token_t *next;
} token_t;

token_t *t_buff ;


void setfileFile(FILE *f)
{
  file = f;
}

void print_t(elm){
switch(elm){
	 {
        case PLUS:
            printf("+"); break;
        case MINUS:
            printf("-"); break;
        case MUL:
            printf("*"); break;
       case DIV:
            printf("/"); break;
        case LESS:
            printf("'<'"); break;
        case GREAT:
            printf("'>'"); break;
        case LESS_EQ:
            printf("'<='"); break;
        case GREAT_EQ:
            printf("'>='"); break;
        case EQUAL:
            printf("=="); break;
        case N_EQUAL:
            printf("!="); break;
        case LEFT_BRACKET:
            printf("("); break;
        case RIGHT_BRACKET:
            printf(")"); break;
        case LEFT_VINCULUM:
            printf("{"); break;
        case RIGHT_VINCULUM:
            printf("}"); break;
        case COMMA:
            printf(","); break;
        case ASSIGN:
            printf("="); break;
        //case :
        //    printf(""); break;
        case INT_LITERAL:
            printf("int literal"); break;
        case DOUBLE_LITERAL:
            printf("double literal"); break;
        case STRING_LITERAL:
            printf("str literal"); break;
        case ID:
            printf("id"); break;
        case SEMICOLON:
            printf(";"); break;
        case E_O_F:
            printf("$"); break;
        default:
            printf("%d", symbol); break;
    }
}
void return_token(int token, char *buffer) {
token_t *elm = malloc(sizeof(token_t));

if (elm == NULL)
        return;

    elm->token = token;
    elm->buffer = buffer;
    elm->next = t_buff;

 t_buff = elm;

    printf("SCANNER: returning token ");
    print_token(token);
    printf(", %s\n", buffer);
}

int lex(string *buffer);
int get_next_token(char **buffer) {
int result;
if (tbuf == NULL) {
        string str;
        strInit(&str);
        result = lex(&str);
        *buffer = str.str;

        printf("SCANNER: sending token ");
        print_token(result);
        printf(", %s\n", *buffer);

        return result;
    }

result = t_buff->token;
    *buffer = t_buff->buffer;

    token_t *temp = t_buff;
    t_buff = t_buff->next;
    free(temp);

    printf("SCANNER: sending token ");
    print_token(result);
    printf(", %s\n", *buffer);

    return result;
}

nt lex(string *buffer) {   
int c; // promenna pre znak
int state = 0; // stav automatu

int plus_count = 0; // kontrola ci je na vstupu +
int minus_count = 0; // kontrola ci je na vstupu -
int less_count = 0; // kontrolla ci je na vstupu <
int great_count = 0; // kontrola ci je na vstupu >
int excl_count = 0;  // kontrola ci je na vstupu !
int eq_count = 0; // kontrola ci je na vstupu =

int count_stars = 0 ;// kontrola spravnosti ukoncenia blokoveho komentaru
int count_dot = 0 ;//
int count_sign=0;
int count_queue =0;

strClear(buffer);
while(1){
	if ((c=getc(file))==EOF)
	{
	return E_O_F;
	break;
	}
case 0: //Stav na zaciatku

      if (isspace(c)) state = 0; // Odignuruje biele miesta ale zostane tu

		else if (c == '/') { count_queue = 1; state = 8; }
			else if (c == '"'){ // jedna se o zaciatok retazca

        state = 4; // preskoc do stavu pro zpracovani retazca
}
 else if (isalpha(c) || c == '_' || c == '$'){ // jedna se o indentifikator ale klucove slovo
	    strAddChar(buffer, c); // nahraj znak do struktury
	    state = 3; // preskoc do miesta  kde sa budu riesit identifikatory ...
}
 else if (isdigit(c)){ // Jedna sa o cislo

        strAddChar(buffer, c);
        state = 5;
} 
	//Ostatne znaky
	  else if (c == '+') { plus_count = 1; state = 8;}
	 else if (c == '-') { minus_count = 1; state = 8;}
	 else if (c == '*' && count_queue == 0) { return MUL; }
	 else if (c == '<') { less_count = 1; state = 8;}
	 else if (c == '>') { great_count = 1; state = 8;}
	 else if (c == '=') { eq_count = 1; state = 8;}
	 else if (c == '!') { excl_count = 1; state = 8;}
	 else if (c == '{') {  return LEFT_VINCULUM; }
	 else if (c == '}') {  return RIGHT_VINCULUM; }
	 else if (c == '(') {  return LEFT_BRACKET; }
	 else if (c == ')') {  return RIGHT_BRACKET; }
	 else if (c == ';') {  return SEMICOLON; }
	 else if (c == ',') { return COMMA; }
	 else return ERR_LEX_ERR;
	 break;
case 1: // RADKOVY KOMENTAR

        if (c != '\n') state = 1;  // Odignorovanie riadkoveho komentaru

        if (c == '\n') state = 0; // konec radku a teda i komentare ???

        break;

case 2: // BLOKOVY KOMENTAR

        if (c != '*' && c!= '/') { state = 2;} // odignorovanie vnutra komentaru

        else if (c == '*') { count_stars = 1; state = 2;} // eviduj hviezdu a zostan tu

        else if (c == '/' && count_stars == 1) { count_stars = 0; state = 0;} //koniec blokoveho komentaru vrat sa do stavu 0

        else if (c == EOF) {return ERR_LEX_ERR;} //Ak nenarazi na koniec komentaru ERR_LEX_ERR

break;
	 case 3: // IDENTIFIKATORY, KLICOVA SLOVA

        if (isalnum(c) || c == '_' || c == '$' || c == '.'){ // pridana tecka jako znak pouzivany pro plne kvalifikovany identifikator

        if (c == '.' && count_dot == 0) count_dot++; //Ak naslo bodku inkrementuje count_dot

        else if (c == '.' && count_dot > 0 ) {return ERR_LEX_ERR; break;} //Ak najde dalsiu jedna sa o neplatnz identifikator

		strAddChar(buffer, c); // Ak sa jedna o identifikator alebo klucove slovo naplnime strukturu
 		state = 3; // Zostane tu a riesi dalej ident. a keywords

        }

	    else {// struktura naplnena, nasleduje prazdne misto nebo nepovoleny znak nebo zacatek zavorky

        if (!isspace(c) && !isalnum(c) && c != '_' && c != '$' && c != '.' && c != '(' && c!= ')' && c!= '{' && c!= '}' && c!= '=' && c!= '+' && c!= '-' && c!= '*' && c!= '/' && c!= '<' && c!= '>' && c!='!' && c!= ';' && c != ',') { return ERR_LEX_ERR; break; } // pokud se neobjevi prazdne misto nebo zavorky nebo operatory ale nejaky nepovoleny znak je to error

        ungetc(c, file); // POZOR! Je potreba vratit posledni nacteny znak

        // kontrola, zda se nejedna o klicove slovo nebo treba povinnou vestavenou fci

	    if (strCmpConstStr(buffer, "boolean") == 0) { return BOOLEAN;}
   	else if (strCmpConstStr(buffer, "break") == 0) { return BREAK; }
   else if (strCmpConstStr(buffer, "class") == 0) { return CLASS;}
   else if (strCmpConstStr(buffer, "continue") == 0) { return CONTINUE;}
   else if (strCmpConstStr(buffer, "do") == 0) { return DO; }
   else if (strCmpConstStr(buffer, "double") == 0) { return DOUBLE;}
   else if (strCmpConstStr(buffer, "else") == 0) { return ELSE;}
   else if (strCmpConstStr(buffer, "false") == 0) {return FALSE;}
   else if (strCmpConstStr(buffer, "for") == 0) {return FOR;}
   else if (strCmpConstStr(buffer, "if") == 0) {return IF;}
   else if (strCmpConstStr(buffer, "int") == 0) {return INT;}
   else if (strCmpConstStr(buffer, "return") == 0) {return RETURN;}
   else if (strCmpConstStr(buffer, "String") == 0) {return STRING;}
   else if (strCmpConstStr(buffer, "static") == 0) {return STATIC;}
   else if (strCmpConstStr(buffer, "true") == 0) {return TRUE;}
   else if (strCmpConstStr(buffer, "void") == 0) {return VOID;}
   else if (strCmpConstStr(buffer, "while") == 0) {return WHILE;}
   else if (strCmpConstStr(buffer, "Main") == 0) { return MAIN;}
   else if (strCmpConstStr(buffer, "run") == 0) {return RUN; }

	    else {return ID;}
	} break;

    case 4: // RETEZCOVY LITERAL

        if (c != '"' && c!= '\x5C'){ // dokud sme v retezci a nejsou pouzity specialni znaky jako \n \"

         strAddChar(buffer, c); // tak normalne naplnuj strukturu

         count_queue = 0; // radsi furt nuluj count_queue jelikoz se nejedna o specialni znak

         state = 4; // a zustan tady
        }

        else if (c == '\x5C'){ // bude nasledovat specialni znak

         strAddChar(buffer, c); // nahraj lomitko do struktury

         count_queue = 1; // signalizuj ze se bude jedna o nejaky spec. znak

         state = 4; // a zustan tady

        }

        else if (c == '"' && count_queue == 1){ // jedna se o uvozovky uvnitr stringu NE signalizujici jeho konec

         strAddChar(buffer, c); // hod je do struktury

         state = 4; // a zustan tady

        }

        else if (c == '"' && count_queue == 0){ // sme na konci retezce

         return STRING_LITERAL; // vrat retezcovy literal
        } break;

    case 5: // CELOCISELNY LITERAL

        if (isdigit(c)){ // pokud prichazi cislo

         strAddChar(buffer, c); // pln strukturu

         state = 5; // a zustan tady
        }

        else if (!isdigit(c) && c != ';' && c != '.' && c != 'e' && c != 'E' && !isspace(c) && c != ')' && c != '+' && c != '-' && c != '/' && c != '*' && c != '!'){ // pokud nasleduje znak jiny nez ; ktery signalizuje konec zadavani literalu nebo tecka signalizujici des. cislo nebo exponent, je to error

          return ERR_LEX_ERR; break;
        }

        else if (c == ';'){

          ungetc(c, file); // konec celeho cisla, vracime ; nebo volny zpatky, zpracujem pak

          return INT_LITERAL; // a vrati se celociselny literal

        }

        else if (isspace(c) || c == ')'){ // nasleduje volne misto, konec zadavani cisla, cislo muze byt zprava v zavorce! DOPLNIT DO FLOATU!!!!

          ungetc(c, file);

          return INT_LITERAL; // a vrati se celociselny literal
        }

        else if(c == '.') { // bude se jednat o desetinny literal ve kterem se nachazi desetinna cast

         strAddChar(buffer, c);
         state = 6;

        }

        else if(c == 'e' || c == 'E') { // bude se jednat o desetinny literal ve kterem NENI desetinna cast ale pouze exponent

         strAddChar(buffer, c);
         state = 7;

        }
        break;

    case 6: // DESETINNY LITERAL

        if (isdigit(c)){ //Ak prijde cislo

         strAddChar(buffer, c); // pln strukturu

         state = 6; // a zustan tady
        }

        else if (c == 'e' || c == 'E'){ // nasleduje exponent

         strAddChar(buffer, c);

         state = 7;
        }

        else if (!isdigit(c) && c != ';' && c != 'e' && c != 'E' && !isspace(c) && c != ')' && c != '+' && c != '-' && c != '/' && c != '*' && c != '!'){ // Ked je iny nez ; alebo exponent je to ERR_LEX_ERR

          return ERR_LEX_ERR; break;
        }

        else if (c == ';'){

          ungetc(c, file); // konec desetinneho cisla, vracime ; zpatky, zpracujem pak

          return DOUBLE_LITERAL; // a vrati se desetinny literal bez exponentu

        }

        else if (isspace(c) || c == ')'){

        ungetc(c, file);

        return DOUBLE_LITERAL; // a vrati se celociselny literal

        }

        break;

    case 7: // DESETINNY LITERAL S EXPONENTEM

        if ((c == '+' || c == '-') && sign_count == 0){ // nasleduje nepovinne znamenko

         sign_count = 1; // bylo pouzito nepovinne znamenko

         strAddChar(buffer, c); // uloz ho do struktury

         state = 7; // a zustan tady
        }

        else if (isdigit(c)) { // nasleduje neprazdna posloupnost cislic

         strAddChar(buffer, c); // uloz ho do struktury

         state = 7; // a zustan tady
        }

        else if (!isdigit(c) && c != ';' && c != '+' && c != '-') {// nic jineho nez cisla za exponentem nebo semicolon tu byt nemuze

         return ERR_LEX_ERR; break;
        }

        else if (c == '+' || (c == '-' && sign_count == 1)) { // pokus o pouziti dalsiho znamenka, nepovoleno

         return ERR_LEX_ERR; break;
        }

        else if (c == ';'){

          ungetc(c, file); // konec desetinneho cisla s exponentem, vracime ; zpatky, zpracujem pak

          return DOUBLE_LITERAL; // a vrati se desetinny literal bez exponentu

} break;
  case 8: // OPERATORY, SLOZENE OPERATORY, ROZPOZNAVANI ZACATKU KOMENTARU

          if (plus_count == 1 && c == '+')  { return INC; }
     else if (plus_count == 1 && c != '+')  {ungetc(c, file); return PLUS;} // vrat neplatny znak, je to plus
     else if (minus_count == 1 && c == '-') { return DEC; }
     else if (minus_count == 1 && c != '-') {ungetc(c, file);  return MINUS;} // vrat neplatny znak, je to minus
     else if (less_count == 1 && c == '=')  { return LESS_EQ;}
     else if (less_count == 1 && c != '=')  {ungetc(c, file); return LESS; } // vrat neplatny znak, je to mensi nez
     else if (great_count == 1 && c == '=') {return GREAT_EQ;}
     else if (great_count == 1 && c != '=') {ungetc(c, file); return GREAT; } // vrat neplatny znak, je to vetsi nez
     else if (excl_count == 1 && c == '=')  {return N_EQUAL;}
     else if (eq_count == 1 && c != '=')    {ungetc(c, file); return ASSIGN; } // vrat neplatny znak, je to rovnasa
     else if (eq_count == 1 && c == '=')    {return EQUAL;} // vrat operator ==
     else if (count_queue == 1 && c != '/' && c != '*') {ungetc(c, file); return DIV; } // nejedna se o komentar ale o operator deleni
     else if (count_queue == 1 && c == '/') state = 1; // jedna se o jednoriadkovy komentar
     else if (count_queue == 1 && c == '*') {state = 2;} // jedna se o blokovy komentar
     else return ERR_LEX_ERR;
break;
}
}
}
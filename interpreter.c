
/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ16       											           
*/
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip 
Kolesar*/
/*Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    
*/
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ial.h"
#include "scanner.h"
#include "instr.h"
#include "err.h"
#include "lex_key.h"

  //Funkcia na vykonanie interpretu
int interpret(){
	tList *intlist;
  listFirst(intlist);//zaktivuje prvu instrukciu
	tInstr *I;
while(1){
I=listGetData(intlist);// vrati aktivni instrukci
switch(I->instType){ //Dalej postupuje podla tipu instrukcie na vstupe
unsigned int size, length;
char ch;
case IS_STOP:
return 0;
break;
//Instrukcia navestia nic nerobi
case IS_LABEL:
		
break;
//Instrukcia pre nacitannie do operandov
case IS_READ:
switch(I->typ){
      case k_int:
      if ( scanf("%d", (int *)I->addr3) != 1) return ERR_SEM_OTHER_ERR ;
		break;
	  case k_double:
	  if (scanf("%lf", (double *)I->addr3) != 1) return ERR_SEM_OTHER_ERR;
		break;
    case k_string:
    if (scanf("%lf", (string *)I->addr3) != 1) return ERR_SEM_OTHER_ERR;
    break;
	}
break;
break;

//ukoncenie nacitania z stdin
 
  case I_WRITE:
  if (*(int*)I->addr1==1){
  	switch(I->typ){
  		case k_int:
            printf("%d", *(int *)I->addr1); break;
          case k_double:
            printf("%g", *(double *)I->addr1); break;
          case k_String:
            printf("%s\n",((string*)I->addr1)->str); break;
           case k_boolean:
            if (*(bool *)I->addr1 == true) printf("TRUE");
            else printf("FALSE");
            break;
          default:
            break;
}
}
//Instrukcia na scitanie operandov
 case IS_ADD:
if(I->typ==k_int){
      *((int*)I->addr3) = *((int*)I->addr1) + *((int*)I->addr2);
		
		}
	else if(I->typ==k_double){
	  *((double*)I->addr3) = *((double*)I->addr1) + *((double*)I->addr2);
		
	 }
	else if(I->typ==k_double&&I->typ==k_int){
	  *((double*)I->addr3) = *((double*)I->addr1) + *((double*)I->addr2);
		
	 }
	else if(I->typ==k_String){
	    ((string *)I->addr3)->alloc = (((string *)I->addr1)->alloc + ((string *)I->addr2)->alloc);
          if ((((string *)I->addr3)->str = malloc(sizeof(string) * ((string *)I->addr3)->alloc)) == NULL)
            return ERR_INTERNAL_ERR;
          strcpy(((string *)I->addr3)->str, ((string *)I->addr1)->str);
          strcat(((string *)I->addr3)->str, ((string *)I->addr2)->str);
      }
	
	else return  ERR_RUNTIME_OTHER_ERR;
		break;
//Instrukcia pre odcitanie operandov
  case IS_SUB:
			if(I->typ==k_int)
			{
      		*((int*)I->addr3) = *((int*)I->addr1) - 
*((int*)I->addr2);
			}
			else if(I->typ==k_double)
			{
	 		 *((double*)I->addr3) = *((double*)I->addr1) - 
*((double*)I->addr2);
			}
			else return  ERR_RUNTIME_OTHER_ERR;
			break;
//Instrukcia na nasobenie operandov
    case IS_MUL:
if(I->typ==k_int){

      *((int*)I->addr3) = *((int*)I->addr1) * *((int*)I->addr2);
		
		}
	else if(I->typ==k_double){
	  *((double*)I->addr3) = *((double*)I->addr1) * 
*((double*)I->addr2);
	}
	 else if(I->typ==kw_double&&I->typ==kw_int) {
	 	*((double*)I->addr3) = *((double*)I->addr1) * 
*((double*)I->addr2);
	 }

	else return  ERR_RUNTIME_OTHER_ERR;
		break; 
		//Instrukcia na delenie operandov
		  	 case IS_DIV:
   					if(I->typ==k_int)
   					{
   							if 
              (*(int*)I->addr1||*(int*)I->addr2==0)
   							{
   									
                  return ERR_ZERO_DIVISION_ERR;
   							}
      				*((int*)I->addr3) = *((int*)I->addr1) * *((int*)I->addr2);
      			    }
					else if(I->typ==k_double)
					{
							if (*(double*)I->addr1||*(double*)I->addr2==0.0)
   							{
   							return 
        ERR_ZERO_DIVISION_ERR;
   							}
	  						*((double*)I->addr3) = *((double*)I->addr1) * *((double*)I->addr2);
					     }
					     else 
            if(I->typ==k_double&&I->typ==k_int){
							if 
                      (*(double*)I->addr1==0||*(double*)I->addr1==0.0||*(double*)I->addr2==0||*(double*)I->addr2==0.0)
							     {
							return ERR_ZERO_DIVISION_ERR;
							}
	   }	
	else return  ERR_RUNTIME_OTHER_ERR;
		break; 
		/*Instrukcia na porovnavanie operandov zo znakom LESS 
<*/
      	case IS_LESS:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 < *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1< *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) < ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 < *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		/*Instrukcia na porovnavainie operandov  zo znakom 
GREATER > */
		case IS_GREATER:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 > *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 > *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		  /*Instrukcia na porovnavainie operandov  zo znakom 
LESSEQ <=*/
		case  IS_LESS_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 <= *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 <= *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) <= ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 <= *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
	/*Instrukcia na porovnavainie operandov zo znakom GREATERQ >=*/
		case  IS_GREAT_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 >= *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 >= *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) >= ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 >= *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
	//Instrukcia na porovnavainie operandov e zo znakom GREATERQ 
/*>=*/
		case  IS_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 == *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 == *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
			case  IS_N_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 == *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 == *(double *)I->addr2; break;
          case k_String: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_boolean: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		 case  IS_INC:
        switch(I->instType)
        {
          case k_int: *(int *)I->addr1 = *(int *)I->addr1 +1; break;
          case k_double: *(double *)I->addr1 = *(double *)I->addr1 +1; 
break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		case  IS_DEC:
        switch(I->instType)
        {
          case k_int: *(int *)I->addr1 = *(int *)I->addr1 -1; break;
          case k_double: *(double *)I->addr1 = *(double *)I->addr1 -1; 
break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}

}
listNext(intlist);
}
 return ERR_OK;
}


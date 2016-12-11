
/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ2016       											           */
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar*/
/*Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    */
/*******************************************************************************/
#include <stdio.h>
#include "interpreter.h"

#define AFM 100
void *data_g [AFM];
//pomocna funkcia na uvolnenie data_g
 void free_data_gl(){
	for (int i = 0; i < AFM; i++)
	{
			if (data_g[i]!=NULL)
			{
			free(data_g[i]);
			}
	
	}
  }
  //Funkcia na vykonanie interpretu
int interpret(tList *intlist){
	listFirst(intlist);//zaktivuje prvu instrukciu
	tInstr *I;
while(1){
I=listGetData(intlist);// vrati aktivni instrukci
switch(I->instType){ //Dalej postupuje podla tipu instrukcie na vstupe
unsigned int size, length;
char ch;
case I_STOP:
return 0;
break;
//Instrukcia navestia nic nerobi
case I_LABEL:
		
break;
//Instrukcia pre nacitannie do operandov
case I_READ:
switch(I->typ){
      case k_int:
      if ( scanf("%d", (int *)I->addr3) != 1) return ERR_SEM_OTHER_ERR ;
		break;
	  case k_double:
	  if (scanf("%lf", (double *)I->addr3) != 1) return ERR_SEM_OTHER_ERR;
		break;
		//Osetrenie nacitania pre string kvoli zadefinovaniu strukturi z nazvom string
	  case k_string:
	     size = 8;
	     length = 0;
            if ((((string *)I->addr3)->str = realloc(((string *)I->addr3)->str, sizeof(char) * size)) == NULL)
              return ERR_INTERNAL_ERR;
            while (EOF != (ch = getchar()) && ch != '\n')
            {
              ((string *)I->addr3)->str[length++] = ch;
              if (length == size)
              {
                if ((((string *)I->addr3)->str = realloc(((string *)I->addr3)->str, sizeof(char) * (size += 8))) == NULL)
                  return ERR_INTERNAL_ERR;
              }
            }
            ((string *)I->addr3)->str[length] = '\0';
            if ((((string *)I->addr3)->str = realloc(((string *)I->addr3)->str, sizeof(char) * length)) == NULL)
               return ERR_INTERNAL_ERR;
            ((string *)I->addr3)->alloc = length;
            ((string *)I->addr3)->length = length;
            break;
					default:
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
          case k_string:
            printf("%s\n",(string*)I->addr1); break;
           case k_bool:
            if (*(bool *)I->addr1 == true) printf("TRUE");
            else printf("FALSE");
            break;
          default:
            break;
}
}
//Instrukcia na scitanie operandov
 case I_ADD:
if(I->typ==k_int){
      *((int*)I->addr3) = *((int*)I->addr1) + *((int*)I->addr2);
		
		}
	else if(I->typ==k_double){
	  *((double*)I->addr3) = *((double*)I->addr1) + *((double*)I->addr2);
		
	 }
	else if(I->typ==k_double&&I->typ==k_int){
	  *((double*)I->addr3) = *((double*)I->addr1) + *((double*)I->addr2);
		
	 }
	else if(I->typ==k_string){
	    ((string *)I->addr3)->alloc = (((string *)I->addr1)->alloc + ((string *)I->addr2)->alloc);
          if ((((string *)I->addr3)->str = malloc(sizeof(string) * ((string *)I->addr3)->alloc)) == NULL)
            return ERR_INTERNAL_ERR;
          strcpy(((string *)I->addr3)->str, ((string *)I->addr1)->str);
          strcat(((string *)I->addr3)->str, ((string *)I->addr2)->str);
      }
	
	else return  ERR_RUNTIME_OTHER_ERR;
		break;
//Instrukcia pre odcitanie operandov
  case I_SUB:
			if(I->typ==k_int)
			{
      		*((int*)I->addr3) = *((int*)I->addr1) - *((int*)I->addr2);
			}
			else if(I->typ==k_double)
			{
	 		 *((double*)I->addr3) = *((double*)I->addr1) - *((double*)I->addr2);
			}
			else return  ERR_RUNTIME_OTHER_ERR;
			break;
//Instrukcia na nasobenie operandov
    case I_MUL:
if(I->typ==k_int){

      *((int*)I->addr3) = *((int*)I->addr1) * *((int*)I->addr2);
		
		}
	else if(I->typ==k_double){
	  *((double*)I->addr3) = *((double*)I->addr1) * *((double*)I->addr2);
	}
	 else if(I->typ==kw_double&&I->typ==kw_int) {
	 	*((double*)I->addr3) = *((double*)I->addr1) * *((double*)I->addr2);
	 }

	else return  ERR_RUNTIME_OTHER_ERR;
		break; 
		//Instrukcia na delenie operandov
		  	 case I_DIV:
   					if(I->typ==k_int)
   					{
   							if (*(int*)I->addr1||*(int*)I->addr2==0)
   							{
   									return ERR_ZERO_DIVISION_ERR;
   							}
      				*((int*)I->addr3) = *((int*)I->addr1) * *((int*)I->addr2);
      			    }
					else if(I->typ==k_double)
					{
							if (*(double*)I->addr1||*(double*)I->addr2==0.0)
   							{
   							return ERR_ZERO_DIVISION_ERR;
   							}
	  						*((double*)I->addr3) = *((double*)I->addr1) * *((double*)I->addr2);
					}
					else if(I->typ==k_double&&I->typ==k_int){
							if (*(double*)I->addr1==0||*(double*)I->addr1==0.0||*(double*)I->addr2==0||*(double*)I->addr2==0.0)
							{
							return ERR_ZERO_DIVISION_ERR;
							}
	   }	
	else return  ERR_RUNTIME_OTHER_ERR;
		break; 
		//Instrukcia na porovnavainie operandov zo znakom pre porovnanie <
		case I_LESS:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 < *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1< *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) < ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 < *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		//Instrukcia na porovnavainie operandov zo znakom pre porovnanie >
		case I_GREATER:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 > *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 > *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		//Instrukcia na porovnavainie operandov zo znakom pre porovnanie <=
		case  I_LESS_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 <= *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 <= *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) <= ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 <= *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		//Instrukcia na porovnavainie operandov zo znakom pre porovnanie >=
		case  I_GREAT_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 >= *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 >= *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) >= ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 >= *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		//Instrukcia na porovnavainie operandov zo znakom pre porovnanie ==
		case  I_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 == *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 == *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
			case  I_N_EQ:
        switch(I->instType)
        {
          case k_int: *(bool *)I->addr3 = *(int *)I->addr1 == *(int *)I->addr2; break;
          case k_double: *(bool *)I->addr3 = *(double *)I->addr1 == *(double *)I->addr2; break;
          case k_string: *(bool *)I->addr3 = (strcmp(((string *)I->addr1)->str, ((string *)I->addr2)->str) > ERR_OK ); break;
          case k_bool: *(bool *)I->addr3 = *(bool *)I->addr1 > *(bool *)I->addr2; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		 case  I_INC:
        switch(I->instType)
        {
          case k_int: *(int *)I->addr1 = *(int *)I->addr1 +1; break;
          case k_double: *(double *)I->addr1 = *(double *)I->addr1 +1; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}
		case  I_DEC:
        switch(I->instType)
        {
          case k_int: *(int *)I->addr1 = *(int *)I->addr1 -1; break;
          case k_double: *(double *)I->addr1 = *(double *)I->addr1 -1; break;
          default:
            return  ERR_TYPE_COMP_ERR;
		}

}
listNext(intlist);
}
 return ERR_OK;
}

int main()
{
	tInstr *s;
	return 0;
}
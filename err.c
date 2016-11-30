/*******************************************************************************/
/*Projekt:Implementace interpretu imperativniho jazyka IFJ2016       											           */
/*Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar*/
/*Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    */
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "galloc.h"

void err_codes(int erroro)
{
    switch(erroro)
    {
        case(ERR_LEX_ERR):
            fprintf(stderr, "Lexical error!\n");
            break;
        case(ERR_SYNTAX_ERR):
            fprintf(stderr, "Syntax error!\n");
            break;
        case(ERR_DEF_ERR):
            fprintf(stderr, "Undefined/redefined function/variable, etc.!\n");
            break;
        case(ERR_TYPE_COMP_ERR):
            fprintf(stderr, "Type compatibility error in arithmetic/string/relation expressions, invalid count/type of arguments during function call!\n");
            break;
        case(ERR_TYPE_DETECT_ERR):
            fprintf(stderr, "Type detection error!\n");
            break;
        case(ERR_SEM_OTHER_ERR):
            fprintf(stderr, " Other semantic errors!\n");
            break;
        case(ERR_NUM_INPUT_ERR):
            fprintf(stderr, "Runtime error during numeric input!\n");
            break;
        case(ERR_UNINITIALIZED_ERR):
            fprintf(stderr, "Runtime error - operation with uninitialized variable!\n");
            break;
        case(ERR_ZERO_DIVISION_ERR):
            fprintf(stderr, "Runtime error - division by zero!\n");
            break;
        case(ERR_RUNTIME_OTHER_ERR):
            fprintf(stderr, "Runtime error - other\n");
            break;
        case(ERR_INTERNAL_ERR):
            fprintf(stderr, "Internal interpreter error!\n");
            break;

    }

    exit(err);
}
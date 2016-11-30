/**
*   Projekt:Implementace interpretu imperativniho jazyka IFJ2016
*   Mena riesitelov: Rastislav Pobis, Patrik Krajc , Peter Grofcik ,Filip Kolesar
*   Loginy riesitelov: xpobis00, xkrajc17, xgrofc00, xkoles06                    
**/

#ifndef __ERROR_H_INCLUDED
#define __ERROR_H_INCLUDED
/* Draft for error-related header file */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum err_codes {
    ERR_OK                  = 0, // Everything is ok
    ERR_LEX_ERR             = 1,  // Lexical error
    ERR_SYNTAX_ERR          = 2,  // Syntax error
    ERR_DEF_ERR             = 3,  // Undefined/redefined function/variable, etc.
    /* TODO: Better name */
   ERR_TYPE_COMP_ERR       = 4,  // Type compatibility error in arithmetic/string/relation expressions, invalid count/type of arguments during function call
    ERR_TYPE_DETECT_ERR     = 5,  // Type detection error
    ERR_SEM_OTHER_ERR       = 6,  // Other semantic errors
    ERR_NUM_INPUT_ERR       = 7,  // Runtime error during numeric input
    ERR_UNINITIALIZED_ERR   = 8,  // Runtime error - operation with uninitialized variable
    ERR_ZERO_DIVISION_ERR   = 9,  // Runtime error - division by zero
    ERR_RUNTIME_OTHER_ERR   = 10, // Runtime error - other
    ERR_INTERNAL_ERR        = 99, // Internal interpreter error
};

void err (int erroro);
#endif;
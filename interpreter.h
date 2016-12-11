
#ifdef _INTERPRETER_H
#define _INTERPRETER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ial.h"
#include "scanner.h"
#include "instr.h"
#include "err.h"

int interpret(tList *L);
#endif

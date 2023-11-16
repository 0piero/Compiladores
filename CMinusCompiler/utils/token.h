#ifndef TOKEN_H
#define TOKEN_H
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "char_type_checker.h"

static char* __rsv_word_tbl[6] = {"if", "while", "int", "void", "return", "else"};
static char* __token_tbl[6] = {"IF", "WHILE", "INT", "VOID", "RETURN", "ELSE"};

int str_to_int(char* lxm);
char* lxm_to_token(char* lxm);
char* symbol_to_token(char* symbol);

#endif
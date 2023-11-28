#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

struct TokenNode {
    char * token;   // ID, INT, ...
    char * lexem;   // Lexema puro, ex: int ABC;
    char* scope;    // global, funcao, ...
    char* nodetype; // VARIAVEL ou FUNCAO
    char* datatype; // INT, CHAR, etc...
    int line;       // Linha em que aparece
};
typedef struct TokenNode TokenNode;

TokenNode* allocate_token_node();

#endif
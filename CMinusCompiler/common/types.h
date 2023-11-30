#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

#define INTEGER_T 0
#define VOID_T 1

#define FUNCAO 2
#define VARIAVEL 3


struct TokenNode {
    char * token;   // ID, INT, ...
    char * lexem;   // Lexema puro, ex: int ABC;
    char* scope;    // global, funcao, ...
    char* len;        // Array size
    int nodetype; // VARIAVEL ou FUNCAO
    int datatype; // INT ou VOID
    int line;       // Linha em que aparece
};
typedef struct TokenNode TokenNode;

TokenNode* allocate_token_node();
void printTokenNode(TokenNode*);

#endif
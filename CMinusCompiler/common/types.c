#include "types.h"

TokenNode* allocate_token_node(){
    TokenNode *t;
    t = malloc(sizeof(TokenNode));
    t->token = malloc(sizeof(char) * 40);
    t->lexem = malloc(sizeof(char) * 40);
    t->scope = malloc(sizeof(char) * 40);
    t->nodetype = malloc(sizeof(char) * 40);
    t->datatype = malloc(sizeof(char) * 40);
    t->len = malloc(sizeof(char) * 40);

    return t;
}
#include "types.h"
#include <stdio.h>
TokenNode* allocate_token_node(){
    TokenNode *t;
    t = malloc(sizeof(TokenNode));
    t->token = malloc(sizeof(char) * 40);
    t->lexem = malloc(sizeof(char) * 40);

    return t;
}

void printTokenNode(TokenNode *t){
    printf(" ============ \n");
    printf("Token: %s \n", t->token);
    printf("Lexem: %s \n", t->lexem);
    printf("Scope: %s \n", t->scope);
    //printf("Len: %s \n", t->len);
    printf("NodeType: %d \n", t->nodetype);
    printf("DataType: %d \n", t->datatype);
    printf("Line: %d \n", t->line);
    printf(" ============ \n");

}
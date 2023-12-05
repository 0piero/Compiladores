#include "types.h"
#include <stdio.h>
#include <string.h>

LinkedList* allocate_linked_list(){
    LinkedList* l;
    l = malloc(sizeof(LinkedList));
    l->data = -1;
    l->next = NULL;
    return l;
}

void insert_linked_list(LinkedList* l, int data){
    LinkedList* head = l;
    LinkedList* aux = allocate_linked_list();
    if(l->next == NULL && l->data == -1){
        l->data = data;
        return;
    }
    while(l->next != NULL)  l = l->next;
    aux->data = data;
    l->next = aux;
    l = head;
}

TokenNode* allocate_token_node(){
    TokenNode *t;
    t = malloc(sizeof(TokenNode));
    t->token = malloc(sizeof(char) * 40);
    t->lexem = malloc(sizeof(char) * 40);
    t->scope = malloc(sizeof(char) * 40);
    t->len = malloc(sizeof(char) * 40);

    t->token = "\0";
    t->lexem = "\0";
    t->len = "\0";
    strcpy(t->scope, "global");

    t->nodetype = -1;
    t->datatype = -1;
    t->line = -1;

    return t;
}

void printTokenNode(TokenNode *t){
    if (t!= NULL){
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

}

TokenNode* copy_tkn_node_scope(TokenNode* nod, char* scope){
  TokenNode* cpy_nod = allocate_token_node();
  cpy_nod->lexem = nod->lexem;
  cpy_nod->scope = scope;
  return cpy_nod;
}
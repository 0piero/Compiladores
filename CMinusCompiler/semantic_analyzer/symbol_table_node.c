#include "symbol_table_node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

symbol_table_node* allocate_symbol_table_node(){
  symbol_table_node *st = malloc(sizeof(symbol_table_node));
  st->nome = malloc(40);
  st->escopo = malloc(40);
  st->id = -1;
  st->datatype = -1;
  st->nodetype = -1;
  st->lines = allocate_linked_list();
  st->next = NULL;
  return st;
}

void print_line(symbol_table_node *st){
  char *nodeTypeString = malloc(20);
  char *dataTypeString = malloc(20);

  printf("%3d ", st->id);
  printf("%10s ", st->nome);
  printf("%10s    ", st->escopo);

  if(st->datatype == INTEGER_T) strcpy(dataTypeString, "INTEIRO");
  else if(st->datatype == VOID_T) strcpy(dataTypeString, "VAZIO");
  else strcpy(dataTypeString, "INDEFINIDO");

  if(st->nodetype == VARIAVEL) strcpy(nodeTypeString, "VARIAVEL");
  else if(st->nodetype == FUNCAO) strcpy(nodeTypeString, "FUNCAO");
  else strcpy(nodeTypeString, "INDEFINIDO");

  printf("%10s    ", dataTypeString);
  printf("%10s    ", nodeTypeString);

  LinkedList *aux = st->lines;
  while(aux != NULL){
    printf("%d, ", aux->data);
    aux = aux->next;
  }
  printf("\n");
}

void print_symbol_table_node(symbol_table_node* st){
  symbol_table_node *aux = st;
  if(aux->next == NULL && aux->id == -1){
    printf("Tabela vazia.\n");
    return;
  }
  while(aux){
    print_line(aux);
    aux = aux->next;
  }

}

void insert_symbol_table_node(symbol_table_node* st, char* nome, char* escopo, int datatype, int nodetype, int line){
  symbol_table_node *head = st;
  symbol_table_node *aux = allocate_symbol_table_node();
  int id = 1;
  // Primeiro elemento
  if(st->next == NULL && st->id == -1){
    st->id = id;
    st->nome = nome;
    st->escopo = escopo;
    st->datatype = datatype;
    st->nodetype = nodetype;
    insert_linked_list(st->lines, line); 
    return;
  }
  id = 2;

  while(1){
    if(!strcmp(st->nome, nome) && !strcmp(st->escopo, escopo)){
      insert_linked_list(st->lines, line);
      return;
    }
    if(st->next == NULL) break;
    st = st->next;
    id++;
  }

  st->next = aux;

  aux->id = id;
  aux->nome = nome;
  aux->escopo = escopo;
  aux->datatype = datatype;
  aux->nodetype = nodetype;
  insert_linked_list(aux->lines, line);

  st = head;
}

symbol_table_node* findTable(symbol_table_node* table, TokenNode* tkNode){
  symbol_table_node *head = table;
  while(head != NULL){
    if(
        !strcmp(head->nome, tkNode->lexem) &&
        !strcmp(head->escopo, tkNode->scope)
      ){
        return head;
      }

    head = head->next;
  }

  // Simbolo nao encontrado.
  return NULL;  
}
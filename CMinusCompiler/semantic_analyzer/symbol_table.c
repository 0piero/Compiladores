#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

symbol_table* allocate_symbol_table(){
  symbol_table *st = malloc(sizeof(symbol_table));
  st->nome = malloc(40);
  st->escopo = malloc(40);
  st->id = -1;
  st->datatype = -1;
  st->nodetype = -1;
  st->lines = allocate_linked_list();
  st->next = NULL;
  return st;
}

void print_line(symbol_table *st){
  printf("%d ", st->id);
  printf("%10s ", st->nome);
  printf("%10s    ", st->escopo);
  printf("%d    ", st->datatype);
  printf("%d    ", st->nodetype);
  LinkedList *aux = st->lines;
  while(aux != NULL){
    printf("%d, ", aux->data);
    aux = aux->next;
  }
  printf("\n");
}

void print_symbol_table(symbol_table* st){
  symbol_table *aux = st;
  if(aux->next == NULL && aux->id == -1){
    printf("Tabela vazia.\n");
    return;
  }
  while(aux){
    print_line(aux);
    aux = aux->next;
  }

}



void insert_symbol_table(symbol_table* st, char* nome, char* escopo, int datatype, int nodetype, int line){
  symbol_table *head = st;
  symbol_table *aux = allocate_symbol_table();
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
    if(st->nodetype == VARIAVEL && !strcmp(st->nome, nome) && !strcmp(st->escopo, escopo)){
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
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>

symbol_table* allocate_symbol_table(){
  symbol_table *st;
  st->nome = malloc(40);
  st->escopo = malloc(40);
  st->id = -1;
  st->datatype = -1;
  st->nodetype = -1;
  st->lines = allocate_linked_list();
  st->next = NULL;
}

void print_symbol_table(symbol_table* st){
  // Imprimindo so a primeira linha por enquanto.
  printf("%d    ", st->id);
  printf("%s    ", st->nome);
  printf("%s    ", st->escopo);
  printf("%d    ", st->datatype);
  printf("%d    ", st->nodetype);
  LinkedList *aux = st->lines;
  while(aux->next != NULL){
    printf("%d, ", aux->data);
    aux = aux->next;
  }
}
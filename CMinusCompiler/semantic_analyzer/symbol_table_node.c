#include "symbol_table_node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

symbol_table* allocate_symbol_table(){
  symbol_table* s = (symbol_table*) malloc(sizeof(symbol_table));
  int i;
  for (i=0;i<SYMBOL_TABLE_SIZE;i++){
    (s->tbl)[i] = NULL;
  }
  return s;
}
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

void print_node_data(symbol_table_node *st){
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

void print_symbol_table_line(symbol_table_node* nod){
  symbol_table_node *aux = nod;
  if(aux->next == NULL && aux->id == -1){
    printf("Tabela vazia.\n");
    return;
  }
  while(aux){
    print_node_data(aux);
    aux = aux->next;
  }

}

void print_symbol_table(symbol_table* st){
  int i;
  for (i=0;i<SYMBOL_TABLE_SIZE;i++){
    print_symbol_table_line((st->tbl)[i]);
  }
}

void insert_symbol_table_node(symbol_table* st, char* nome, char* escopo, int datatype, int nodetype, int line){
  char* key_str = strcat(strcat(escopo, "_"), nome);
  long int hash_key = symbol_table_hash(key_str);

  symbol_table_node* head = st->tbl[hash_key];
  symbol_table_node* aux;
  aux = head;

  // Primeiro elemento
  if (head == NULL){
    head = allocate_symbol_table_node();
    head->nome = nome;
    head->escopo = escopo;
    head->datatype = datatype;
    head->nodetype = nodetype;
    insert_linked_list(head->lines, line);
    return;
  }

  while(aux != NULL){
    if(!strcmp(aux->nome, nome) && !strcmp(aux->escopo, escopo)){
      insert_linked_list(aux->lines, line);
      return;
    }
    head = aux;
    aux = aux->next;
  }

  /* novo simbolo a ser inserido */
  head->next = allocate_symbol_table_node();
  head->next->nome = nome;
  head->next->escopo = escopo;
  head->next->datatype = datatype;
  head->next->nodetype = nodetype;
  insert_linked_list(head->next->lines, line);
}

symbol_table_node* findTable(symbol_table* table, TokenNode* tkNode){
  char* key_str = strcat(strcat(tkNode->scope, "_"), tkNode->lexem);
  long int hash_key = symbol_table_hash(key_str);

  symbol_table_node *head = table->tbl[hash_key];
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


long int symbol_table_hash(char* key){
  int size_str = strlen(key), i;
  long int key_int_value = 0;
  int p = 509;
  long int alpha = 1;
  long int hash;
  for (i=0;i<size_str;i++){
    key_int_value += ((long int) key[i]) * alpha;
    alpha = alpha * 2;
  }
  hash = ((3*key_int_value + 7) % p) % SYMBOL_TABLE_SIZE;
  return hash;
}







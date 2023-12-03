#ifndef SYMBOL_TABLE_NODE_H
#define SYMBOL_TABLE_NODE_H

#include "../common/types.h"

typedef struct symbol_table_node symbol_table_node;
struct symbol_table_node {
  int id;
  char *nome;
  char *escopo;
  int datatype;
  int nodetype;
  LinkedList *lines;

  symbol_table_node *next;
};

symbol_table_node* allocate_symbol_table_node();
void print_symbol_table_node(symbol_table_node* st);
void print_line(symbol_table_node *st);


void insert_symbol_table_node(symbol_table_node* st, char* nome, char* escopo,
                          int datatype, int nodetype, int line);

symbol_table_node* findTable(symbol_table_node* st, TokenNode* tkNode);

#endif
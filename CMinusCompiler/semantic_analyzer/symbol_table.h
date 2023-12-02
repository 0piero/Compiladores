#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../common/types.h"

typedef struct symbol_table symbol_table;
struct symbol_table {
  int id;
  char *nome;
  char *escopo;
  int datatype;
  int nodetype;
  LinkedList *lines;

  symbol_table *next;
};

symbol_table* allocate_symbol_table();
void print_symbol_table(symbol_table* st);

void insert_symbol_table(symbol_table* st, char* nome, char* escopo,
                          int datatype, int nodetype, int line);

#endif
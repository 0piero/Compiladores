#ifndef SYMBOL_TABLE_NODE_H
#define SYMBOL_TABLE_NODE_H

#include "../common/types.h"

#define SYMBOL_TABLE_SIZE 503

typedef struct symbol_table_node symbol_table_node;
struct symbol_table_node {
  int id;
  char* nome;
  char* escopo;
  int datatype;
  int nodetype;
  LinkedList *lines;
  LinkedList *lines_decl;
  int visited; /* marcação para verificar se o ID foi visitado na tabela de simbolos durante a verificacao de declaracao unica*/
  symbol_table_node *next;
};

typedef struct symbol_table symbol_table;
struct symbol_table {
  symbol_table_node* tbl[SYMBOL_TABLE_SIZE];
};

symbol_table* allocate_symbol_table();
symbol_table_node* allocate_symbol_table_node();
void print_node_data(symbol_table_node *st);

void print_symbol_table_line(symbol_table_node* nod);
void print_symbol_table(symbol_table* st);

void insert_symbol_table_node(symbol_table* st, char* nome, char* escopo, int datatype, int nodetype, int line, int isVarDecl);

long int symbol_table_hash(char* key); /* a chave pode ser definida como uma combinacao de id+scope */

symbol_table_node* findTable(symbol_table* st, TokenNode* tkNode);

#endif
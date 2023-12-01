#include "./parse.tab.h"
#include "./common/types.h"
#include "./parser/syntax_tree.h"
#include "./parse_tree.h"
#include "./semantic_analyzer/symbol_table.h"

#include <stdio.h>
#include <string.h>

void tree_to_table(syntax_tree *t, symbol_table *st);

int main(){
  syntax_tree *t = parseTree();
  printf("Generated tree...\n");
  syntax_tree_display(t);

  symbol_table *st = allocate_symbol_table();
  printf("Allocating Symbols table...\n");
  insert_symbol_table(st, "aux", "main", INTEGER_T, VARIAVEL, 3);
  insert_symbol_table(st, "aux", "main", INTEGER_T, VARIAVEL, 4);

  insert_symbol_table(st, "i", "main", INTEGER_T, VARIAVEL, 1);
  insert_symbol_table(st, "i", "main", INTEGER_T, VARIAVEL, 2);
  insert_symbol_table(st, "i", "main", INTEGER_T, VARIAVEL, 9);


  insert_symbol_table(st, "func", "global", VOID_T, FUNCAO, 10);

  print_symbol_table(st);
}

void tree_to_table(syntax_tree *t, symbol_table *st){
	while(t != NULL){
		if(!strcmp(t->node_data->token, "ID")){
      // Insert in table
    }
		//Filhos
		for(int i = 0; i < 3; i++){
			tree_to_table(t->child[i], st);
		}
			t = t->sibling;
	}
}
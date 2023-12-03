#include "./parse.tab.h"
#include "./common/types.h"
#include "./parser/syntax_tree.h"
#include "./parse_tree.h"
#include "./semantic_analyzer/symbol_table.h"
#include "./semantic_analyzer/analyze.h"

#include <stdio.h>
#include <string.h>

void tree_to_table(syntax_tree *t, symbol_table *st);

int main(){
  syntax_tree *t = parseTree();
  syntax_tree_display(t);

  symbol_table *st = allocate_symbol_table();

  printf("\nAllocating Symbols table...\n");
  tree_to_table(t, st);
  print_symbol_table(st);
  printf("\n");
  
  semanticAnalyze(t, st);
}

void tree_to_table(syntax_tree *t, symbol_table *st){
  while(t != NULL){
		if(!strcmp(t->node_data->token, "ID")){
      insert_symbol_table(st,
                          t->node_data->lexem,
                          t->node_data->scope,
                          t->node_data->datatype,
                          t->node_data->nodetype,
                          t->node_data->line);
    }
		
    //Filhos
		for(int i = 0; i < t->n_child; i++){
     tree_to_table(t->child[i], st);   
		}

    t = t->sibling;
	}
}
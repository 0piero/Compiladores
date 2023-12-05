#include "./parse.tab.h"
#include "./common/types.h"
#include "./parser/syntax_tree.h"
#include "./parse_tree.h"
#include "./semantic_analyzer/symbol_table_node.h"
#include "./semantic_analyzer/analyze.h"

#include <stdio.h>
#include <string.h>

void tree_to_table(syntax_tree *t, symbol_table *st);
void fixDataTypes(syntax_tree *t, symbol_table *st);

int main(){ /* ok */
  syntax_tree *t = parseTree();
  syntax_tree_display(t);

  symbol_table* st = allocate_symbol_table();

  printf("\nAllocating Symbols table...\n");
  tree_to_table(t, st);
  fixDataTypes(t, st);
  print_symbol_table(st);
  printf("\n");
  DeclUniqueness(t, st);
  semanticAnalyze(t, t, st);
}

void tree_to_table(syntax_tree *t, symbol_table *st){ /* ok */
  while(t != NULL){
		if(!strcmp(t->node_data->token, "ID")){
      insert_symbol_table_node(st,
                          t->node_data->lexem,
                          t->node_data->scope,
                          t->node_data->datatype,
                          t->node_data->nodetype,
                          t->node_data->line,
                          t->isVarDecl);
    }
		
    //Filhos
		for(int i = 0; i < t->n_child; i++){
      tree_to_table(t->child[i], st);   
		}

    t = t->sibling;
	}
}

void fixDataTypes(syntax_tree* t, symbol_table *st){ /* ok */
    while(t != NULL){
		  if(t->isActivation){
        TokenNode *actTokNode = allocate_token_node();
        actTokNode->lexem = t->node_data->lexem;
        actTokNode->scope = t->node_data->scope;
        symbol_table_node *activationNode = findTable(st, actTokNode);

        TokenNode *funcTokNode = allocate_token_node();
        funcTokNode->lexem = t->node_data->lexem;
        strcpy(funcTokNode->scope, "global");
        //printf("key str:[%s] [%s]\n", funcTokNode->lexem, funcTokNode->scope);
        symbol_table_node *funcNode = findTable(st, funcTokNode);
        if(funcNode == NULL){
          printf("ERRO SEMÂNTICO: funcao não declarada. LINHA: %d\n", t->node_data->line);
          exit(1);
        }
        activationNode->datatype = funcNode->datatype;
      }

      //Filhos
		  for(int i = 0; i < t->n_child; i++){
        fixDataTypes(t->child[i], st);   
		  }

      t = t->sibling;
	}
}
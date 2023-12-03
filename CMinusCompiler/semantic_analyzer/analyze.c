#include "./analyze.h"
#include <string.h>

void semanticAnalyze(syntax_tree* tree, symbol_table_node* table){
  while(tree != NULL){

    if(!strcmp(tree->node_data->token, "ASSIGN")){
      analyzeAssignment(tree, table);
    }

    // Caso o nó não tenha filhos.
    if(tree->n_child == 0) return;

    for(int i = 0; i < tree->n_child; i++){
      semanticAnalyze(tree->child[i], table);
    }

    tree = tree-> sibling;
  }
}

void analyzeAssignment(syntax_tree* tree, symbol_table_node* table){
  symbol_table_node *varLine = findTable(table, tree->child[0]->node_data);
  int exprType = tree->child[1]->node_data->datatype;


  if(tree->child[1]->node_data->nodetype == FUNCAO){
    exprType = findTable(table, tree->child[1]->node_data)->datatype;
  }

  if(varLine == NULL){
    printf("ERRO SEMÂNTICO: atribuição em variável não encontrada. ");
    printf("LINHA: %d\n", tree->child[0]->node_data->line);
    exit(1);
  }

  
  if(varLine->datatype != exprType){
    printf("ERRO SEMÂNTICO: atribuição com tipos diferentes. ");
    printf("LINHA: %d\n", tree->child[1]->node_data->line);
    exit(1);
  }


}
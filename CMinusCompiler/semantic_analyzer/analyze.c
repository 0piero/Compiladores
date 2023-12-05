#include "./analyze.h"
#include <string.h>
#include <stdio.h>

void analyzeAssignment(syntax_tree* tree, symbol_table* table);
void analyzeActivation(syntax_tree *root, syntax_tree *tree, symbol_table* table);
void DeclUniqueness(syntax_tree *root, symbol_table *tbl);

void semanticAnalyze(syntax_tree* root, syntax_tree* tree, symbol_table* table){
  while(tree != NULL){

    if(!strcmp(tree->node_data->token, "ASSIGN")){
      analyzeAssignment(tree, table);
    }
    if(tree->isActivation){
      analyzeActivation(root, tree, table);
    }

    // Caso o nó não tenha filhos.
    if(tree->n_child == 0) return;

    for(int i = 0; i < tree->n_child; i++){
      semanticAnalyze(root, tree->child[i], table);
    }

    tree = tree-> sibling;
  }
}

void analyzeAssignment(syntax_tree* tree, symbol_table* table){
  symbol_table_node *varLine = findTable(table, tree->child[0]->node_data);
  if(varLine->datatype == -1){
    TokenNode *tk = tree->child[0]->node_data;
    strcpy(tk->scope, "global");
    symbol_table_node *varLineGlobal = findTable(table, tk);
    if(varLineGlobal) varLine = varLineGlobal;
  }
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

void analyzeActivation(syntax_tree *root, syntax_tree *tree, symbol_table* table){
  syntax_tree* param = tree->child[0];
  
  while(param != NULL){
    symbol_table_node* currParam = findTable(table, param->node_data);
    if(!currParam){
      strcpy(param->node_data->scope, "global");
      currParam = findTable(table, param->node_data);
    }

    int currType = currParam->datatype;
  
    while(root != NULL){
      // Se nao for ativacao, e uma declaracao.
      // printTokenNode(root->node_data);
      if(!root->isActivation) break;
      root = root->sibling;
    }

    if(!root){
      printf("ERRO SEMÂNTICO: funcao não declarada. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }

    int funcDeclType = root->node_data->datatype;
    if(funcDeclType != currType){
      printf("ERRO SEMÂNTICO: argumento de tipo diferente. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }

    param = param->sibling;
  }
}

void DeclUniqueness(syntax_tree *root, symbol_table *tbl){
  syntax_tree* nod = root;
  while (nod != NULL){
    /* filho 0 zero sempre guarda o tipo de uma variavel, poderia ser mais explicito */
    if (nod->isVarDecl || (nod->node_data->nodetype == FUNCAO && nod->isActivation==0)){

      symbol_table_node* var_nod = findTable(tbl, nod->node_data);
      if (var_nod != NULL && var_nod->lines_decl->next != NULL){
        /* exibe a linha seguinte na lista de linhas do simbolo encontrado na tabela  */
        printf("ERRO SEMÂNTICO: declaração %s não-única. LINHA: %d\n", var_nod->nome, var_nod->lines->next->data);
      }
    }
    for(int i = 0; i < nod->n_child; i++){ /* se fosse var n precisaria verificar o filho 0 */ 
      DeclUniqueness(nod->child[i], tbl);
    }
    nod = nod->sibling;
  }
}




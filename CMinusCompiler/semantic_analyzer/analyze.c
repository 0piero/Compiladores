#include "./analyze.h"
#include <string.h>
#include <stdio.h>

void analyzeAssignment(syntax_tree* tree, symbol_table* table);
void analyzeActivation(syntax_tree *root, syntax_tree *tree, symbol_table* table);
void DeclUniqueness(syntax_tree *root, symbol_table *tbl);
void ConsistentFRet(syntax_tree *root, syntax_tree *nod, symbol_table *tbl);

void semanticAnalyze(syntax_tree* root, syntax_tree* tree, symbol_table* table){
  while(tree != NULL){
    if((tree->node_data != NULL) && (tree->node_data->nodetype == FUNCAO) && (tree->isVarDecl==1)){
      //printf("%s\n", tree->node_data->lexem);
      ConsistentFRet(tree, tree->child[2]->child[1], table); // child[2] eh o node de comp-decl
    }
    if(!strcmp(tree->node_data->token, "ASSIGN")){
      analyzeAssignment(tree, table);
    }
    if(tree->isActivation){
      analyzeActivation(root, tree, table);
    }
    //Caso o nó não tenha filhos.
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
    char srch_scope[6] = "global";
    TokenNode*  tk_cpy = copy_tkn_node_scope(tk, srch_scope);
    symbol_table_node *varLineGlobal = findTable(table, tk_cpy);
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
  syntax_tree *funcParams;
  int flag = 1;
  while(param != NULL){
    int currParamType = -1;
    if(param->isActivation){
      TokenNode *tk = param->node_data;
      strcpy(tk->scope, "global");
      currParamType = findTable(table, tk)->datatype;
    }else{
      currParamType = param->node_data->datatype;
    }
  
    while(root != NULL){
      // printTokenNode(root->node_data);
      if(root->isFunDecl && flag){
        flag = 0;
        funcParams = root->child[1];
        break;
      }
      root = root->sibling;
    }

    if(!root && flag){
      printf("ERRO SEMÂNTICO: funcao não declarada. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }

    int funcDeclType = funcParams->node_data->datatype;
    if(funcDeclType != currParamType){
      printf("ERRO SEMÂNTICO: argumento de tipo diferente. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }

    funcParams = funcParams->sibling;
    param = param->sibling;

    if(!funcParams && param){
      printf("ERRO SEMÂNTICO: faltando argumentos. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }
    if(funcParams && !param){
      printf("ERRO SEMÂNTICO: argumentos a mais. LINHA: %d\n", tree->node_data->line);
      exit(1);
    }
  }
}

void DeclUniqueness(syntax_tree *root, symbol_table *tbl){
  syntax_tree* nod = root;
  while (nod != NULL){

    if (nod->isVarDecl){
      symbol_table_node* var_nod = findTable(tbl, nod->node_data);
      if (var_nod != NULL && var_nod->lines_decl->next != NULL && !var_nod->visited){
        /* marca o node da outra declaração como visitado */
        var_nod->visited = 1;
        /* exibe a linha seguinte na lista de linhas do simbolo encontrado na tabela  */
        LinkedList* conf_lptr = var_nod->lines_decl;
        while(conf_lptr){
          printf("ERRO SEMÂNTICO: declaração %s não é única. LINHA: %d\n", var_nod->nome, conf_lptr->data);
          conf_lptr = conf_lptr->next; 
        }
        exit(1);
      }
    }
    for(int i = 0; i < nod->n_child; i++){
        DeclUniqueness(nod->child[i], tbl);
    }
    nod = nod->sibling;
  }
}


void ConsistentFRet(syntax_tree *root, syntax_tree *nod, symbol_table *tbl){
  while(nod != NULL){
    if (!strcmp(nod->node_data->token, "RETURN")){

      if (nod->n_child > 0 && nod->child[0]->isActivation == 1)
      {
        /* copia com escopo global para a findTable */
        char srch_scope[6] = "global";
        TokenNode* glbl_nod_data = copy_tkn_node_scope(nod->child[0]->node_data, srch_scope);

        symbol_table_node* atv_nod = findTable(tbl, glbl_nod_data);
        if (atv_nod != NULL && atv_nod->datatype != root->node_data->datatype){
          printf("ERRO SEMÂNTICO: retorno da função %s inconsistente com a definição. LINHA: %d\n",
            root->node_data->lexem, nod->node_data->line);  
        }
      }

      else if(nod->n_child == 0 && root->node_data->datatype != VOID_T) /* return com 0 filhos retorna void */
      {
        printf("ERRO SEMÂNTICO: retorno da função %s inconsistente com a definição. LINHA: %d\n",
          root->node_data->lexem, nod->node_data->line);
      }
      
      else if(nod->n_child > 0 && nod->child[0]->isActivation == 0)
      {
        if ((INTEGER_T != root->node_data->datatype)){
          printf("ERRO SEMÂNTICO: retorno da função %s inconsistente com a definição. LINHA: %d\n",
            root->node_data->lexem, nod->node_data->line);
        }
      }
    }
    for(int i = 0; i < nod->n_child; i++){
      ConsistentFRet(root, nod->child[i], tbl);
    }
    nod = nod->sibling;
  }
} 


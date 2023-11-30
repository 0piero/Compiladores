%{
  #define YYPARSER

  #include "./parser/syntax_tree.h"
  #define YYSTYPE syntax_tree *
  
  #include "./parse.tab.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"

  int lineno = 0;
  char lex[40];

  static int yylex(void);
  TokenNode* next_token();
  syntax_tree* tree;            /* raiz da syntax_tree */
  syntax_tree* R_mst_decl_node; /* (utilizado para as regras 2 e 3 da CFG) mantem um ponteiro pro nó declaracao
                                   mais a esquerda corrente na arvore 
                                */
  syntax_tree* R_mst_param;     /* (utilizado para as regras 8 e 9 da CFG) mantem um ponteiro pro nó param
                                   mais a esquerda corrente na arvore que se origina de param-list 
                                */
  syntax_tree* L_var_decl;                                
  syntax_tree* L_stmt;
  syntax_tree* L_mst_expr;


  int tok_to_num(char *);
  void yyerror(char *);
%}

%start programa
%token IF ELSE WHILE INT VOID RETURN
%token NUMBER ID
%token ASS EQL NEQL LT GT LET GET PLUS MINUS TIMES DIV
%token LPAREN RPAREN LBRA RBRA LKEY RKEY COMMA SEMICOLON
%token ERR END

%%
  programa: decl-lista {tree = $1;}
            ;

  decl-lista: decl-lista decl {
                $$ = $1;            
                if($$ != NULL){
                   while ($$->sibling != NULL) $$ = $$->sibling; 
                   $$->sibling = $2;
                   $$ = $1;
                }else{
                  $$ = $2;
                }
              }
            | decl { $$ = $1; }
            ;

  decl: var-decl {$$ = $1;}
      | fun-decl {$$ = $1;}
      ;

  id: ID {
      $$ = syntax_tree_alloc_node(0);
      $$->node_data->token = "ID";
      $$->node_data->lexem = lex;
    }
    ;

  num: NUMBER {
    $$ = syntax_tree_alloc_node(0);
    $$->node_data->token = "NUMBER";
    $$->node_data->lexem = lex;
    $$->node_data->datatype = INTEGER_T;
  }
  ;

  var-decl: INT id SEMICOLON {
              $$ = syntax_tree_alloc_node(1);
              $$->node_data->token = "INT";
              $$->node_data->lexem = "int";
              $$->n_child = 1;
              $$->child[0] = $2;
              $2->node_data->nodetype = VARIAVEL;
              $2->node_data->datatype = INTEGER_T;
            }
            | INT id LBRA num RBRA SEMICOLON {
              $$ = syntax_tree_alloc_node(1);
              $$->node_data->token = "INT";
              $$->node_data->lexem = "int";
              $$->n_child = 1;
              $$->child[0] = $2;
              $2->node_data->nodetype = VARIAVEL;
              $2->node_data->datatype = INTEGER_T;
              $2->node_data->len = $4->node_data->lexem;
            }
            ;
  
  fun-decl: INT id LPAREN params RPAREN composto-decl {
              $$ = syntax_tree_alloc_node(3);
              $$->node_data->token = "INT";
              $$->node_data->lexem = "int";
              $$->node_data->datatype = INTEGER_T;
              $$->n_child = 1;
              $$->child[0] = $1;
              $2->child[0] = $4;
              $2->child[1] = $6;
              $2->child[0]->node_data->scope = $2->node_data->lexem;
              $2->child[1]->node_data->scope = $2->node_data->lexem;
              $2->n_child = 2;
              $2->node_data->nodetype = FUNCAO;
            }
          | VOID id LPAREN params RPAREN composto-decl {
              $$ = syntax_tree_alloc_node(3);
              $$->node_data->token = "VOID";
              $$->node_data->lexem = "void";
              $$->node_data->datatype = VOID_T;
              $$->n_child = 1;
              $$->child[0] = $1;
              $2->child[0] = $4;
              $2->child[1] = $6;
              $2->child[0]->node_data->scope = $2->node_data->lexem;
              $2->child[1]->node_data->scope = $2->node_data->lexem;
              $2->n_child = 2;
              $2->node_data->nodetype = FUNCAO;
            }
          ;

  params: param-lista {
            $$ = $1;
          }
          | VOID {
            $$ = syntax_tree_alloc_node(0);
            $$->node_data->token = "VOID";
            $$->node_data->lexem = "void";
          }
        ;

  param-lista:  param-lista COMMA param {
                  $$ = $1;
                  if($$ != NULL){
                    while($$->sibling != NULL) $$ = $$->sibling;
                    $$->sibling = $3;
                    $$ = $1;
                  }
                  else $$ = $3;
              }
              | param {
                $$ = $1;
              }
             ;

  param:  INT id {
            $$ = syntax_tree_alloc_node(1);
            $$->node_data->token = "INT";
            $$->node_data->lexem = "int";
            $$->node_data->datatype = INTEGER_T;
            $$->n_child = 1;
            $$->child[0] = $2;
            $2->node_data->nodetype = VARIAVEL;
            $2->node_data->datatype = INTEGER_T;
          }
          | INT id LBRA RBRA
          {
            $$ = syntax_tree_alloc_node(1);
            $$->node_data->token = "INT";
            $$->node_data->lexem = "int";
            $$->node_data->datatype = INTEGER_T;
            $$->n_child = 1;
            $$->child[0] = $2;
            $2->node_data->nodetype = VARIAVEL;
            $2->node_data->datatype = INTEGER_T;
          }
          ;




  CONTINUAR DAQUI




  composto-decl:  LKEY local-decls statement-lista RKEY {
                    enum composto_decl_enum {lcl_dcls, stmnt_lst};
                    $$ = syntax_tree_alloc_node(2);
                    $$->child[lcl_dcls] = $2;
                    $$->child[stmnt_lst] = $3;
                    $$->n_child = 2;
                  }
               ;

  local-decls:  local-decls var-decl {
                  $$ = $1;              
                  $2->sibling = L_var_decl;
                  L_var_decl = $2; /* atualiza o novo nó var_decl mais a esquerda da arvore */
                }
             |  {
                  $$ = L_var_decl; /* ver se isso faz sentido */
                }
             ;

  statement-lista:  statement-lista statement {
                      $$ = $1;              
                      $2->sibling = L_stmt;
                      L_stmt = $2; /* atualiza o novo nó var_decl mais a esquerda da arvore */
                    }
                 |  {
                      $$ = L_stmt;
                    }
                 ;

  statement:  expr-decl {
                $$ = $1;
              }
           |  composto-decl {
                $$ = $1;
              }
           |  selec-decl {
                $$ = $1;
              }
           |  iter-decl {
                $$ = $1;
              }
           |  retorno-decl {
                $$ = $1;
              }
           ;

  expr-decl:  expr SEMICOLON {
                $$ = $1;
              }
           |  SEMICOLON {
                $$ = NULL;
              }
           ;

  selec-decl: IF LPAREN expr RPAREN statement { /* ver se é desse jeito a arvore pra declaracoes if*/
                enum selec_decl_enum {if_expr, if_stmt};
                syntax_tree* if_node = syntax_tree_alloc_node(2);
                $$ = if_node;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5;
                $$->n_child = 2;
                /* node_data */
                char tkn[3] = {'I', 'F', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | IF LPAREN expr RPAREN statement ELSE statement {
                enum selec_decl_enum_if_else {if_expr, if_stmt, else_stmt};
                syntax_tree* if_node = syntax_tree_alloc_node(3);
                $$ = if_node;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5;
                $$->child[else_stmt] = $7;
                $$->n_child = 3;
                /* node_data */
                char tkn[3] = {'I', 'F', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            ;

  iter-decl:  WHILE LPAREN expr RPAREN statement {
                enum iter_decl_enum {while_expr, while_stmt};
                syntax_tree* while_node = syntax_tree_alloc_node(2);
                $$ = while_node;
                $$->child[while_expr] = $3;
                $$->child[while_stmt] = $5;
                $$->n_child = 2;
                /* node_data */
                char tkn[6] = {'W', 'H', 'I', 'L', 'E', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
           ;

  retorno-decl: RETURN SEMICOLON {
                  enum retorno_decl_enum {ret_expr};
                  syntax_tree* ret_node = syntax_tree_alloc_node(1);
                  $$ = ret_node;
                  $$->child[ret_expr] = NULL;
                  $$->n_child = 1;
                  /* node_data */
                  char tkn[7] = {'R', 'E', 'T', 'U', 'R', 'N', '\0'};
                  $$->node_data->token = tkn;
                  /* node_data */
                }
              | RETURN expr SEMICOLON {
                  enum retorno_decl_enum {ret_expr};
                  syntax_tree* ret_node = syntax_tree_alloc_node(1);
                  $$ = ret_node;
                  $$->child[ret_expr] = $1;
                  $$->n_child = 1;
                  /* node_data */
                  char tkn[7] = {'R', 'E', 'T', 'U', 'R', 'N', '\0'};
                  $$->node_data->token = tkn;
                  /* node_data */
                }
              ;

  expr: var ASS expr {
          enum ass_expr_enum {asgn_var, asgn_expr};
          syntax_tree* asgn_node = syntax_tree_alloc_node(2);
          $$ = asgn_node;
          $$->child[asgn_var] = $1;
          $$->child[asgn_expr] = $3;
          $$->n_child = 2;
          /* node_data */
          char tkn[7] = {'=', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
      | simples-expr {
          $$ = $1;
        }
      ;

  var:  ID {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[7] = {'R', 'E', 'T', 'U', 'R', 'N', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
     |  ID LBRA expr RBRA {
          $$ = syntax_tree_alloc_node(1); /* ID node */
          $$->child[0] = $3; /* ID->child[0] = expr */
          $$->n_child = 1;
          /* node_data */
          char tkn[3] = {'I', 'D', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
     ;

  simples-expr: soma-expr relacional soma-expr {
                  $$ = $2;

                  enum simpl_expr_enum {soma_expr1, soma_expr2};
                  $2->child[soma_expr1] = $1;
                  $2->child[soma_expr2] = $3;
                  $$->n_child = 2;
                }
              | soma-expr {
                  $$ = $1;
                }
              ;

  relacional: LET {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[4] = {'L', 'E', 'T', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | LT {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[3] = {'L', 'T', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | GT {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[3] = {'G', 'T', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | GET {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[4] = {'G', 'E', 'T', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | EQL {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[4] = {'E', 'Q', 'L', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            | NEQL {
                $$=syntax_tree_alloc_node(0);
                /* node_data */
                char tkn[5] = {'N', 'E', 'Q', 'L', '\0'};
                $$->node_data->token = tkn;
                /* node_data */
              }
            ;

  soma-expr: soma-expr soma termo {
                $$ = $2;

                enum soma_expr_enum {soma_expr, soma_termo};
                $2->child[soma_expr] = $1;
                $2->child[soma_termo] = $3;
                $$->n_child = 2;
              }
           |  termo {
                $$ = $1;
              }
           ;

  soma: PLUS {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[2] = {'+', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
      | MINUS {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[2] = {'-', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
      ;

  termo:  termo mult fator {
            $$ = $2;

            enum mult_enum {mult_termo, mult_fator};
            $2->child[mult_termo] = $1;
            $2->child[mult_fator] = $3;
            $$->n_child = 2;
  }
       |  fator {
            $$ = $1;}
       ;

  mult: TIMES {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[2] = {'*', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
      | DIV {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[2] = {'/', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
        }
      ;
  
  fator:  LPAREN expr RPAREN {$$ = $2;}
       |  var {$$ = $1;}
       |  ativacao {$$ = $1;}
       |  NUMBER {
          $$ = syntax_tree_alloc_node(0);
          /* node_data */
          char tkn[7] = {'N', 'U', 'M', 'B', 'E', 'R', '\0'};
          $$->node_data->token = tkn;
          /* node_data */
          }
       ;
  
  ativacao: ID LPAREN args RPAREN {
              $$ = syntax_tree_alloc_node(1);
              enum ativacao_enum {ativacao_args};
              $$->child[ativacao_args] = $3;
              $$->n_child = 1;
              /* node_data */
              char tkn[3] = {'I', 'D', '\0'};
              $$->node_data->token = tkn;
              /* node_data */
            }
          ;

  args: arg-list {
          $$ = $1;
        }
      |
      ;

  arg-list: arg-list COMMA expr {
              $$ = $1;                
              $3->sibling = L_mst_expr;
              L_mst_expr = $3; /* atualiza o novo nó decl mais a esquerda da arvore */
            }
           |  expr {
                $$ = $1;
                $1->sibling = L_mst_expr;
                L_mst_expr = $1;
              }
           ;
%%

static int yylex(){
  TokenNode* curr_token = next_token();
  int tok_num = END;
  char *tok;
  if(curr_token){
    lineno = curr_token->line;
    tok = curr_token->token;
    strcpy(lex, curr_token->lexem);
    tok_num = tok_to_num(tok);
  }else{
   //printf("Last token received!\n");
  }
  //if(lex) printf("Current Token: %s Lexem: %s Num: %d\n", tok, lex, tok_num);
  //else printf("Current Token: %s\n", tok);
   
  return tok_num;
}

int tok_to_num(char* tok){
  if(!strcmp(tok, "ID")) return ID;
  if(!strcmp(tok, "IF")) return IF;
  if(!strcmp(tok, "ELSE"))return ELSE;
  if(!strcmp(tok, "INT"))return INT;
  if(!strcmp(tok, "VOID"))return VOID;
  if(!strcmp(tok, "WHILE"))return WHILE;
  if(!strcmp(tok, "RETURN"))return RETURN;

  if(!strcmp(tok, "="))return ASS;
  if(!strcmp(tok, "=="))return EQL;
  if(!strcmp(tok, "!="))return NEQL;
  if(!strcmp(tok, ">"))return GT;
  if(!strcmp(tok, "<"))return LT;
  if(!strcmp(tok, "<="))return LET;
  if(!strcmp(tok, ">="))return GET;
  if(!strcmp(tok, "+"))return PLUS;
  if(!strcmp(tok, "-"))return MINUS;
  if(!strcmp(tok, "*"))return TIMES;
  if(!strcmp(tok, "/"))return DIV;
  if(!strcmp(tok, "["))return LBRA;
  if(!strcmp(tok, "]"))return RBRA;
  if(!strcmp(tok, "("))return LPAREN;
  if(!strcmp(tok, ")"))return RPAREN;
  if(!strcmp(tok, "{"))return LKEY;
  if(!strcmp(tok, "}")) return RKEY;
  if(!strcmp(tok, ","))return COMMA;
  if(!strcmp(tok, ";"))return SEMICOLON;

  if(!strcmp(tok, "NUMBER"))return NUMBER;
  
  if(!strcmp(tok, "END"))return END;
  //printf("Token not found: %s\n", tok);
  return ERR;
}

int main(int argv, char **argc){
  return yyparse();
}

void yyerror(char *c){
  if(yychar != ERR && yychar != END){
    printf("ERRO SINTATICO: %s LINHA: %d\n", c, lineno);
    exit(1);
  }
}
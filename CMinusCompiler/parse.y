%{
  #define YYPARSER

  #include "./parser/syntax_tree.h"
  #define YYSTYPE syntax_tree *
  
  #include "./parse.tab.h"
  #include <stdio.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"

  int lineno = 0;

  static int yylex(void);
  TokenNode* next_token();
  syntax_tree* tree;            /* raiz da syntax_tree/
  syntax_tree* R_mst_decl_node; /* (utilizado para as regras 2 e 3 da CFG) mantem um ponteiro pro nó declaracao
                                   mais a direita corrente na arvore 
                                */
  syntax_tree* R_mst_param;     /* (utilizado para as regras 8 e 9 da CFG) mantem um ponteiro pro nó param
                                   mais a direita corrente na arvore que se origina de param-list 
                                */
  syntax_tree* L_var_decl;                                
  syntax_tree* L_stmt;


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
                $2->sibling = R_mst_decl_node;
                R_mst_decl_node = $2; /* atualiza o novo nó decl mais a esquerda da arvore */
              }
            | decl {
                $$ = $1;
                $1->sibling = R_mst_decl_node;
                R_mst_decl_node = $1; /* seta o no mais a esquerda no caso base de decl-lista */
              }
            ;

  decl: var-decl {$$ = $1;}
      | fun-decl {$$ = $1; printf("fun-decl\n");}
      ;

  var-decl: tipo-especificador ID SEMICOLON {
              enum var_decl_enum {espc_type, id};

              $$ = syntax_tree_alloc_node(2);

              $$->child[espc_type] = $1;
              $$->child[id] = syntax_tree_alloc_node(0);
            }
          | tipo-especificador ID LBRA NUMBER RBRA SEMICOLON {
              enum var_decl_enum {espc_type, id, num};

              $$ = syntax_tree_alloc_node(3);

              $$->child[espc_type] = $1;
              $$->child[id] = syntax_tree_alloc_node(0);
              $$->child[num] = syntax_tree_alloc_node(0);
            }
          ;

  tipo-especificador: INT {
                        $1 = syntax_tree_alloc_node(0);
                        $$ = $1;
                      }
                    | VOID {
                        $1 = syntax_tree_alloc_node(0);
                        $$ = $1;
                      }
                    ;
  
  fun-decl: tipo-especificador ID LPAREN params RPAREN composto-decl {
              enum fun_decl_enum {espc_type, id, params, comp_decl};

              $$ = syntax_tree_alloc_node(4);
              
              $$->child[espc_type] = $1;
              $$->child[id] = syntax_tree_alloc_node(0);
              $$->child[params] = $4;
              $$->child[comp_decl] = $6;
            }
          ;

  params: param-lista {
            $$ = $1;
          }
        | VOID {
            $1 = syntax_tree_alloc_node(0);
            $$ = $1;
          }
        ;

  param-lista:  param-lista COMMA param {

                  $$ = $1;                
                  $3->sibling = R_mst_param;
                  R_mst_param = $3; /* atualiza o novo nó decl mais a esquerda da arvore */
                }
            | param {
                $$ = $1;
                $1->sibling = R_mst_param;
                R_mst_param = $1; /* seta o no mais a esquerda no caso base de param-lista */
              }
            ;

  param:  tipo-especificador ID {
            enum param_enum {espc_type, id};
            $$ = syntax_tree_alloc_node(2);
            $$->child[espc_type] = $1;
            $$->child[id] = syntax_tree_alloc_node(0);
          }
       |  tipo-especificador ID LBRA RBRA {
            enum param_enum {espc_type, id, lbra, rbra};
            $$ = syntax_tree_alloc_node(4);
            $$->child[espc_type] = $1;
            $$->child[id] = syntax_tree_alloc_node(0);
            $$->child[lbra] = syntax_tree_alloc_node(0);
            $$->child[rbra] = syntax_tree_alloc_node(0);
          }
       ;

  composto-decl:  LKEY local-decls statement-lista RKEY {
                    enum composto_decl_enum {lcl_dcls, stmnt_lst};
                    $$ = syntax_tree_alloc_node(2);
                    $$->child[lcl_dcls] = $2;
                    $$->child[stmnt_lst] = $3;
                  }
               ;

  local-decls:  local-decls var-decl {
                  $$ = $1;
                  $1->sibling = $2;              
                  $2->sibling = L_var_decl;
                  L_var_decl = $2; /* atualiza o novo nó var_decl mais a esquerda da arvore */
                }
             |  {
                  $$ = L_var_decl; /* ver se isso faz sentido */
                }
             ;

  statement-lista:  statement-lista statement {
                      $$ = $1;
                      $1->sibling = $2;              
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
                enum selec_decl_enum {if_expr, if_stmt, else_stmt};
                syntax_tree* if_node = syntax_tree_alloc_node(3);
                $$ = if_node;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5;
                $$->child[else_stmt] = NULL;
              }
            | IF LPAREN expr RPAREN statement ELSE statement {
                enum selec_decl_enum {if_expr, if_stmt, else_stmt};
                syntax_tree* if_node = syntax_tree_alloc_node(3);
                $$ = if_node;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5;
                $$->child[else_stmt] = $7;
              }
            ;

  iter-decl:  WHILE LPAREN expr RPAREN statement {
                enum iter_decl_enum {while_expr, while_stmt};
                syntax_tree* while_node = syntax_tree_alloc_node(2);
                $$ = while_node;
                $$->child[while_expr] = $3;
                $$->child[while_stmt] = $5;
              }
           ;

  retorno-decl: RETURN SEMICOLON {
                  enum retorno_decl_enum {ret_expr};
                  syntax_tree* ret_node = syntax_tree_alloc_node(1);
                  $$ = ret_node;
                  $$->child[ret_expr] = NULL;
                }
              | RETURN expr SEMICOLON {
                  enum retorno_decl_enum {ret_expr};
                  syntax_tree* ret_node = syntax_tree_alloc_node(1);
                  $$ = ret_node;
                  $$->child[ret_expr] = $1;
                }
              ;

  expr: var ASS expr {
          enum ass_expr_enum {asgn_var, asgn_expr};
          syntax_tree* asgn_node = syntax_tree_alloc_node(2);
          $$ = asgn_node;
          $$->child[asgn_var] = $1;
          $$->child[asgn_expr] = $3;
        }
      | simples-expr {
          $$ = $1;
        }
      ;

  var:  ID {
          $$ = syntax_tree_alloc_node(0);
          $$->child = NULL;
        }
     |  ID LBRA expr RBRA {
          enum var_enum {asgn_var, asgn_expr};
          $$ = syntax_tree_alloc_node(1); /* ID node */
          $$->child[0] = expr; /* ID->child[0] = expr */
        }
     ;

  simples-expr: soma-expr relacional soma-expr {
                  $$ = $2;

                  enum simpl_expr_enum {soma_expr1, soma_expr2};
                  $2->child[soma_expr1] = $1;
                  $2->child[soma_expr2] = $3;
                }
              | soma-expr {
                  $$ = $1;
                }
              ;

  relacional: LET {
                $$=$1;
              }
            | LT {
                $$=$1;
              }
            | GT {
                $$=$1;
              }
            | GET {
                $$=$1;
              }
            | EQL {
                $$=$1;
              }
            | NEQL {
                $$=$1;
              }
            ;

  soma-expr: soma-expr soma termo {
                $$ = $2;

                enum soma_expr_enum {soma_expr, soma_termo};
                $2->child[soma_expr1] = $1;
                $2->child[soma_expr2] = $3;
              }
           |  termo {
                $$ = $1;
              }
           ;

  soma: PLUS {$$ = $1;}
      | MINUS {$$ = $1;}
      ;

  termo:  termo mult fator {
            $$ = $2;

            enum mult_enum {mult_termo, mult_fator};
            $2->child[mult_termo] = $1;
            $2->child[mult_fator] = $3;
  }
       |  fator {
            $$ = $1;
          }
       ;

  mult: TIMES {$$ = $1;}
      | DIV {$$ = $1;}
      ;
  
  fator: LPAREN expr RPAREN {$$ = $2;}
       | var {$$ = $1;}
       | ativacao {$$ = $1;}
       | NUMBER { $$ = $1;}
       ;
  
  ativacao: ID LPAREN args RPAREN {

              $$ = syntax_tree_alloc_node(2);
              enum ativacao_enum {ativacao_id, ativacao_args};
              $$->child[ativacao_id] = syntax_tree_alloc_node(0);
              $$->child[ativacao_args] = $3;
            }
          ;

  args: arg-list {
          $$ = $1;
        }
      |
      ;

  arg-list: arg-list COMMA expr {
              $$ = L_mst_expr;
              $$ = $1;                
              $3->sibling = L_mst_expr;
              L_mst_expr = $3; /* atualiza o novo nó decl mais a esquerda da arvore */
            }
           | expr {}
           ;

%%

static int yylex(){
  TokenNode* curr_token = next_token();
  int tok_num = END;
  char *tok, *lex;
  if(curr_token){
    lineno = curr_token->line;
    tok = curr_token->token;
    lex = curr_token->lexem;
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
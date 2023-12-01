%{
  #define YYPARSER

  #include "./parser/syntax_tree.h"
  #define YYSTYPE syntax_tree *
  
  #include "./parse.tab.h"
  #include <stdio.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"


  static int yylex(void);
  TokenNode* next_token();
  syntax_tree* tree;            /* raiz da syntax_tree */
  TokenNode* _curr_token;       /* struct do token atual retornado pela yylex contendo os metadados */
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

  decl-lista: decl-lista decl { /* corrigido com o esquema de reducao do bison */
                $$ = $1;
                R_mst_decl_node->sibling = $2;
                R_mst_decl_node = $2;               
                $2->sibling = NULL;
              }
            | decl {
                $$ = $1;
                R_mst_decl_node = $1; /* seta o no mais a direita da lista no caso base de decl-lista */
                $1->sibling = NULL;
              }
            ;

  decl: var-decl {$$ = $1;}
      | fun-decl {$$ = $1;}
      ;

  /*
    chamando a alloc_node pra malocar com 0 filhos,
    precisa dar o malloc pro numero certo de filhos na regra que ela foi chamada depois
  */
  id: ID {
        $$ = syntax_tree_alloc_node(0);
        $$->node_data->token = "ID";
        $$->node_data->lexem = _curr_token->lexem;
        $$->node_data->line = _curr_token->line;
      }
    ;

  num:  NUMBER {
          $$ = syntax_tree_alloc_node(0);
          $$->node_data->token = "NUMBER";
          $$->node_data->lexem = _curr_token->lexem;
          $$->node_data->datatype = INTEGER_T; /* ver de onde saiu esse INTEGER_T */
        }
      ;


  var-decl: tipo-especificador id SEMICOLON {
              enum var_decl_enum {espc_type};

              $$ = $2; /* passando o token node do terminal id*/
              $$->child = (syntax_tree**) malloc(sizeof(syntax_tree*));
              $$->child[espc_type] = $1;
              $$->n_child = 1;
            }
          | tipo-especificador id LBRA num RBRA SEMICOLON {
              enum var_decl_enum {espc_type, num};

              $$ = $2;
              $$->child = (syntax_tree**) malloc(2 * sizeof(syntax_tree*));

              $$->child[espc_type] = $1;
              $$->child[num] = $4;
              $$->n_child = 2;
            }
          ;

  tipo-especificador: INT {
                        $$ = syntax_tree_alloc_node(0);
                        $$->node_data->token = "INT";
                        $$->node_data->line = _curr_token->line;
                      }
                    | VOID {
                        $$ = syntax_tree_alloc_node(0);
                        $$->node_data->token = "VOID";
                        $$->node_data->line = _curr_token->line;
                      }
                    ;
  
  fun-decl: tipo-especificador id LPAREN params RPAREN composto-decl {
              enum fun_decl_enum {espc_type, params, comp_decl};

              $$ = $2;
              $$->child = (syntax_tree**) malloc(3 * sizeof(syntax_tree*));              
              $$->child[espc_type] = $1;
              $$->child[params] = $4;
              $$->child[comp_decl] = $6;
              $$->n_child = 3;
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
                  R_mst_param->sibling = $3;
                  R_mst_param = $3;
                  $3->sibling = NULL;         
                }
            | param {
                $$ = $1;
                R_mst_param = $1;
                $$->sibling = NULL;
              }
            ;

  param:  tipo-especificador id {
            enum param_enum {espc_type};
            $$ = $2;
            $$->child = (syntax_tree**) malloc(sizeof(syntax_tree*));
            $$->child[espc_type] = $1;
            $$->n_child = 1;
          }
        | tipo-especificador id LBRA RBRA {
            enum param_enum {espc_type};
            $$ = $2;
            $$->child = (syntax_tree**) malloc(sizeof(syntax_tree*));
            $$->child[espc_type] = $1;
            $$->n_child = 1;
          }
       ;

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
                  L_var_decl->sibling = $2;
                  L_var_decl = $2;
                  $2->sibling = NULL;
                }
             |  { /* ver o comportamento disso */
                  $$ = syntax_tree_alloc_node(0); // nó vazio
                  L_var_decl = $$;
                  $$->sibling = NULL;
                }
             ;

  statement-lista:  statement-lista statement {
                      $$ = $1;
                      L_stmt->sibling = $2;
                      L_stmt = $2;
                      $2->sibling = NULL;
                    }
                 |  {

                      $$ = syntax_tree_alloc_node(0); // nó vazio
                      L_stmt = $$;
                      $$->sibling = NULL;
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

  selec-decl: IF LPAREN expr RPAREN statement { /* ver se é desse jeito a arvore pra declaracoes if */
                enum selec_decl_enum {if_expr, if_stmt};

                $$ = syntax_tree_alloc_node(2);
                $$->node_data->token = "IF";
                $$->n_child = 2;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5;
              }
            | IF LPAREN expr RPAREN statement ELSE statement {
                
                $$ = syntax_tree_alloc_node(3);
                $$->node_data->token = "IF-ELSE";
                $$->n_child = 3;
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[2] = $7;
              }
            ;

  iter-decl:  WHILE LPAREN expr RPAREN statement {
                enum iter_decl_enum {while_expr, while_stmt};

                $$ = syntax_tree_alloc_node(2);
                $$->node_data->token = "WHILE";
                $$->n_child = 2;
                $$->child[while_expr] = $3;
                $$->child[while_stmt] = $5;
              }
           ;

  retorno-decl: RETURN SEMICOLON {
                  $$ = syntax_tree_alloc_node(0);
                  $$->node_data->token = "RETURN";
                  $$->n_child = 0;
                  $$->node_data->datatype = VOID_T;
                }
              | RETURN expr SEMICOLON {
                  enum retorno_decl_enum {ret_expr};
                  
                  $$ = syntax_tree_alloc_node(1);
                  $$->node_data->token = "RETURN";
                  $$->child[ret_expr] = $2;
                  $$->n_child = 1;
                }
              ;

  expr: var ASS expr {
          enum ass_expr_enum {asgn_var, asgn_expr};
          
          $$ = syntax_tree_alloc_node(2);
          $$->node_data->token = "ASSIGN";
          $$->child[asgn_var] = $1;
          $$->child[asgn_expr] = $3;
          $$->n_child = 2;
        }
      | simples-expr {
          $$ = $1;
        }
      ;

  var:  id {
          $$ = $1;
        }
     |  id LBRA expr RBRA {
          $$ = $1; /* ID node */
          $$->child = (syntax_tree**) malloc(sizeof(syntax_tree*));
          $$->child[0] = $3; /* ID->child[0] = expr */
          $$->n_child = 1;
          $$->node_data->datatype = VARIAVEL;
          $$->node_data->datatype = INTEGER_T;
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
                $$->node_data->token = "<=";
                $$->node_data->lexem = "<=";
              }
            | LT {
                $$=syntax_tree_alloc_node(0);
                $$->node_data->token = "<";
                $$->node_data->lexem = "<";
              }
            | GT {
                $$=syntax_tree_alloc_node(0);
                $$->node_data->token = ">";
                $$->node_data->lexem = ">";
              }
            | GET {
                $$=syntax_tree_alloc_node(0);
                $$->node_data->token = ">=";
                $$->node_data->lexem = ">=";
              }
            | EQL {
                $$=syntax_tree_alloc_node(0);
                $$->node_data->token = "==";
                $$->node_data->lexem = "==";
              }
            | NEQL {
                $$=syntax_tree_alloc_node(0);
                $$->node_data->token = "!=";
                $$->node_data->lexem = "!=";
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
          $$->node_data->token = "+";
          $$->node_data->lexem = "+";
        }
      | MINUS {
          $$ = syntax_tree_alloc_node(0);
          $$->node_data->token = "-";
          $$->node_data->lexem = "-";
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
          $$->node_data->token = "*";
          $$->node_data->lexem = "*";
        }
      | DIV {
          $$ = syntax_tree_alloc_node(0);
          $$->node_data->token = "/";
          $$->node_data->lexem = "/";
        }
      ;
  
  fator:  LPAREN expr RPAREN {$$ = $2;}
       |  var {$$ = $1;}
       |  ativacao {$$ = $1;}
       |  num {
          $$ = $1;
          }
       ;
  
  ativacao: id LPAREN args RPAREN {
              $$ = $1;
              enum ativacao_enum {ativacao_args};
              $$->child = (syntax_tree**) malloc(sizeof(syntax_tree*));
              $$->child[ativacao_args] = $3;
              $$->n_child = 1;
            }
          ;

  args: arg-list {
          $$ = $1;
        }
      | {$$ = NULL;}
      ;

  arg-list: arg-list COMMA expr {
              $$ = $1;                
              L_mst_expr->sibling = $3;
              L_mst_expr = $3; /* atualiza o novo nó decl mais a esquerda da arvore */
              $3->sibling = NULL;
            }
           |  expr {
                $$ = $1;
                L_mst_expr = $1;
                $$->sibling = NULL;
              }
           ;

%%

static int yylex(){
  TokenNode* curr_token = next_token();
  int tok_num = END;
  char *tok;
  if(curr_token){
    tok = curr_token->token;
    /* strcpy(lex, curr_token->lexem); */
    /* salvando todo o struct do token ao inves de copiar so o lexema */
    _curr_token = curr_token; /* tomar cuidado pra nao dar free depois em curr_token */
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
  tree = (syntax_tree*) malloc(sizeof(syntax_tree));
  R_mst_decl_node = syntax_tree_alloc_node(0);
  R_mst_param = syntax_tree_alloc_node(0);
  L_var_decl = syntax_tree_alloc_node(0);
  L_stmt = syntax_tree_alloc_node(0);
  L_mst_expr = syntax_tree_alloc_node(0);
  yyparse();
  //syntax_tree_display(tree);
  
  printTokenNode(tree->node_data);
  printTokenNode(tree->child[0]->node_data);
  printTokenNode(tree->child[1]->node_data);
  printTokenNode(tree->child[1]->child[0]->node_data);
  printTokenNode(tree->child[1]->sibling->node_data);
  printTokenNode(tree->child[1]->sibling->child[0]->node_data);
  printTokenNode(tree->child[2]->node_data);
  printTokenNode(tree->child[2]->child[1]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[0]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[0]->child[1]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[1]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[1]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[1]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[1]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[1]->child[1]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[1]->child[0]->child[0]->node_data);
  printTokenNode(tree->child[2]->child[1]->sibling->child[2]->child[0]->child[0]->sibling->child[1]->child[0]->child[1]->node_data);
  
  //printTokenNode(tree->child[2]->node_data);


}

void yyerror(char *c){
  if(yychar != ERR && yychar != END){
    printf("ERRO SINTATICO: %s LINHA: %d\n", c, _curr_token->line);
    exit(1);
  }
}
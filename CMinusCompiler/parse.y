%{
  #define YYPARSER

  #include "./parser/syntax_tree.h"
  #define YYSTYPE syntax_tree *
  
  #include "./parse_tree.h"
  #include "./parse.tab.h"
  #include <stdio.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"
  #include "./parser/stack.h"

  static int yylex(void);
  TokenNode* next_token();
  static syntax_tree* tree;            /* raiz da syntax_tree */
  TokenNode* _curr_token;       /* struct do token atual retornado pela yylex contendo os metadados */
  stack* pseudo_stack_R_mst_decl_node;                                

  stack* pseudo_stack_R_mst_param;
  stack* pseudo_stack_L_var_decl;                                
  stack* pseudo_stack_L_stmt;
  stack* pseudo_stack_L_mst_expr;


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
  programa: decl-lista {
              //printf("programa <- decl-lista\n");
              tree = $1;
              stack_pop(pseudo_stack_R_mst_decl_node);
            }
            ;

  decl-lista: decl-lista decl {
                //printf("decl-lista <- decl-lista decl\n");
                $$ = $1;
                stack_node* nod_R_mst = stack_pop(pseudo_stack_R_mst_decl_node);
                nod_R_mst->ptr->sibling = $2;
                nod_R_mst->ptr = $2;               
                $2->sibling = NULL;
                stack_push(pseudo_stack_R_mst_decl_node, nod_R_mst);

              }
            | decl {
                //printf("decl-lista <- decl\n");
                $$ = $1;
                $1->sibling = NULL;
                //R_mst_decl_node = $1;
                stack_node* nod = stack_alloc_node();
                nod->ptr = $1;
                stack_push(pseudo_stack_R_mst_decl_node, nod);
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
              //printf("var-decl <- tipo-especificador id SEMICOLON\n");
              enum var_decl_enum {espc_type};

              $$ = $2; /* passando o token node do terminal id*/
              $$->child = syntax_tree_alloc_node(1);
              $$->child[espc_type] = $1;
              $$->n_child = 1;
              $$->node_data->nodetype = VARIAVEL;
              $$->node_data->datatype = $1->node_data->datatype;
              $$->isVarDecl = 1;

              if($1->node_data->datatype == VOID_T) yyerror($1->node_data->token);
            }
          | tipo-especificador id LBRA num RBRA SEMICOLON {
              //printf("var-decl <- tipo-especificador id LBRA num RBRA SEMICOLON\n");
              enum var_decl_enum {espc_type, num};

              $$ = $2;
              $$->child = syntax_tree_alloc_node(1);

              $$->child[espc_type] = $1;
              $$->child[num] = $4;
              $$->n_child = 2;
              $$->node_data->nodetype = VARIAVEL;
              $$->node_data->datatype = INTEGER_ARR;
              $$->isVarDecl = 1;
              if($1->node_data->datatype == VOID_T) yyerror($1->node_data->token);
              if(atoi($4->node_data->lexem) < 0) yyerror($4->node_data->token);
            }
          ;

  tipo-especificador: INT {
                        //printf("tipo-especificador <- INT\n");
                        $$ = syntax_tree_alloc_node(0);
                        $$->node_data->token = "INT";
                        $$->node_data->line = _curr_token->line;
                        $$->node_data->datatype = INTEGER_T;
                      }
                    | VOID {
                        //printf("tipo-especificador <- VOID\n");
                        $$ = syntax_tree_alloc_node(0);
                        $$->node_data->token = "VOID";
                        $$->node_data->line = _curr_token->line;
                        $$->node_data->datatype = VOID_T;
                      }
                    ;
  
  fun-decl: tipo-especificador id LPAREN params RPAREN composto-decl {
              //printf("fun-decl <- tipo-especificador id LPAREN params RPAREN composto-decl\n");
              enum fun_decl_enum {espc_type, params, comp_decl};

              $$ = $2;
              $$->child = syntax_tree_alloc_node(3);             
              $$->child[espc_type] = $1;
              $$->child[params] = $4;
              $$->child[comp_decl] = $6;
              $$->n_child = 3;
              $$->node_data->nodetype = FUNCAO;
              $$->isVarDecl = 1;
              $$->node_data->datatype = $1->node_data->datatype;
              $$->isFunDecl = 1;

              update_scope($4, $2->node_data->lexem);
              update_scope($6, $2->node_data->lexem);
            }
          ;

  params: param-lista {
            //printf("params <- param-lista\n");
            $$ = $1;
            stack_pop(pseudo_stack_R_mst_param);
          }
        | VOID {
            //printf("params <- VOID\n");
            $$ = syntax_tree_alloc_node(0);
            $$->node_data->token = "VOID";
            $$->node_data->lexem = "void";
          }
        ;

  param-lista:  param-lista COMMA param {
                  //printf("param-lista <- param-lista COMMA param\n");
                  $$ = $1;
                  stack_node* nod_R_mst_param = stack_pop(pseudo_stack_R_mst_param);
                  nod_R_mst_param->ptr->sibling = $3;
                  nod_R_mst_param->ptr = $3;
                  $3->sibling = NULL;         
                  stack_push(pseudo_stack_R_mst_param, nod_R_mst_param);
                }
            | param {
                //printf("param-lista <- param\n");
                $$ = $1;
                //R_mst_param = $1;
                $$->sibling = NULL;

                stack_node* nod = stack_alloc_node();
                nod->ptr = $1;
                stack_push(pseudo_stack_R_mst_param, nod);
              }
            ;

  param:  tipo-especificador id {
            //printf("param <- tipo-especificador id\n");
            enum param_enum {espc_type};
            $$ = $2;
            $$->child = syntax_tree_alloc_node(1);
            $$->child[espc_type] = $1;
            $$->n_child = 1;
            $$->isVarDecl = 1;
            $$->node_data->nodetype = VARIAVEL;
            $$->node_data->datatype = $1->node_data->datatype;
          }
        | tipo-especificador id LBRA RBRA {
            //printf("param <- id LBRA RBRA\n");
            enum param_enum {espc_type};
            $$ = $2;
            $$->child = syntax_tree_alloc_node(1);
            $$->child[espc_type] = $1;
            $$->n_child = 1;
            $$->isVarDecl = 1;
            $$->node_data->nodetype = VARIAVEL;
            $$->node_data->datatype = INTEGER_ARR;
          }
       ;

  composto-decl:  LKEY local-decls statement-lista RKEY {
                    //printf("composto-decl <- LKEY local-decls statement-lista RKEY\n");
                    enum composto_decl_enum {lcl_dcls, stmnt_lst};
                    $$ = syntax_tree_alloc_node(2);
                    /* resolvendo o esquema de tirar o primeiro no vazio da lista */
                    syntax_tree* head_local_decls = $2->sibling;

                    syntax_tree* head_statement_list = $3->sibling;
                    /* */
                    
                    /* os callers esvaziam a pilha */
                    stack_pop(pseudo_stack_L_var_decl);
                    stack_pop(pseudo_stack_L_stmt);
                  
                    /* */

                    $$->child[lcl_dcls] = head_local_decls;
                    $$->child[stmnt_lst] = head_statement_list;
                    $$->n_child = 2;
                  }
               ;

  local-decls:  local-decls var-decl {
                  //printf("local-decls <- local-decls var-decl\n");
                  $$ = $1;
                  stack_node* nod_L_var_decl = stack_pop(pseudo_stack_L_var_decl);
                  nod_L_var_decl->ptr->sibling = $2;
                  nod_L_var_decl->ptr = $2;
                  $2->sibling = NULL;
                  stack_push(pseudo_stack_L_var_decl, nod_L_var_decl);
                }
             |  {
                  //printf("local-decls <- vazio\n");
                  $$ = syntax_tree_alloc_node(0); // nó vazio
                  //L_var_decl = $$;
                  $$->sibling = NULL;

                  stack_node* nod = stack_alloc_node();
                  nod->ptr = $$;
                  stack_push(pseudo_stack_L_var_decl, nod);
                }
             ;

  statement-lista:  statement-lista statement {
                      //printf("statement-lista <- statement-lista statement\n");
                      $$ = $1;
                      stack_node* nod_L_stmt = stack_pop(pseudo_stack_L_stmt);
                      nod_L_stmt->ptr->sibling = $2;
                      nod_L_stmt->ptr = $2;
                      $2->sibling = NULL;
                      stack_push(pseudo_stack_L_stmt, nod_L_stmt);
                      
                    }
                 |  {
                      //printf("statement-lista <- vazio\n");
                      $$ = syntax_tree_alloc_node(0); // nó vazio
                      //L_stmt = $$;
                      $$->sibling = NULL;

                      stack_node* nod = stack_alloc_node();
                      nod->ptr = $$;
                      stack_push(pseudo_stack_L_stmt, nod);
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
                //printf("expr-decl <- expr SEMICOLON\n");
                $$ = $1;
              }
           |  SEMICOLON {
                //printf("expr-decl <- SEMICOLON\n");
                $$ = NULL;
              }
           ;

  selec-decl: IF LPAREN expr RPAREN statement { /* ver se é desse jeito a arvore pra declaracoes if */
                enum selec_decl_enum {if_expr, if_stmt};
                //printf("selec-decl <- IF LPAREN expr RPAREN statement\n");

                $$ = syntax_tree_alloc_node(2);
                $$->node_data->token = "IF";
                $$->n_child = 2;
                $$->child[if_expr] = $3;
                $$->child[if_stmt] = $5; /* isso pode ser NULL */
              }
            | IF LPAREN expr RPAREN statement ELSE statement {
                //printf("selec-decl <- IF LPAREN expr RPAREN statement ELSE statement\n");
                $$ = syntax_tree_alloc_node(3);
                $$->node_data->token = "IF-ELSE";
                $$->n_child = 3;
                $$->child[0] = $3;
                $$->child[1] = $5; /* isso pode ser NULL */
                $$->child[2] = $7; /* isso pode ser NULL */
              }
            ;

  iter-decl:  WHILE LPAREN expr RPAREN statement {
                //printf("iter-decl <- WHILE LPAREN expr RPAREN statement\n");
                $$ = syntax_tree_alloc_node(2);
                $$->node_data->token = "WHILE";
                $$->n_child = 2;
                $$->child[0] = $3;
                $$->child[1] = $5; /* isso pode ser NULL */
                $$->sibling = NULL;
              }
           ;

  retorno-decl: RETURN SEMICOLON {
                  //printf("retorno-decl <- RETURN SEMICOLON\n");
                  $$ = syntax_tree_alloc_node(0);
                  $$->node_data->token = "RETURN";
                  $$->n_child = 0;
                  $$->node_data->datatype = VOID_T;
                  $$->node_data->line = _curr_token->line;
                }
              | RETURN expr SEMICOLON {
                  //printf("retorno-decl <- RETURN expr SEMICOLON\n");
                  enum retorno_decl_enum {ret_expr};
                  
                  $$ = syntax_tree_alloc_node(1);
                  $$->node_data->token = "RETURN";
                  $$->child[ret_expr] = $2;
                  $$->n_child = 1;
                  $$->node_data->line = _curr_token->line;
                }
              ;

  expr: var ASS expr {
          //printf("expr <- var ASS expr\n");
          enum ass_expr_enum {asgn_var, asgn_expr};
          
          $$ = syntax_tree_alloc_node(2);
          $$->node_data->token = "ASSIGN";
          $$->child[asgn_var] = $1;
          $$->child[asgn_expr] = $3;
          $$->n_child = 2;
        }
      | simples-expr {
          //printf("expr <- simples-expr\n");
          $$ = $1;
        }
      ;

  var:  id {
          //printf("var <- id\n");
          $$ = $1;
          $$->node_data->nodetype = VARIAVEL;
          $$->node_data->datatype = INTEGER_T;
        }
     |  id LBRA expr RBRA {
          //printf("var <- id LBRA expr RBRA\n");
          $$ = $1; /* ID node */
          $$->child = syntax_tree_alloc_node(1);
          $$->child[0] = $3; /* ID->child[0] = expr */
          $$->n_child = 1;
          $$->node_data->nodetype = VARIAVEL;
          $$->node_data->datatype = INTEGER_T;
          if(!strcmp($3->node_data->token, "NUMBER")){
            printf("%s\n", $3->node_data->lexem);
            if(atoi($3->node_data->lexem) < 0) yyerror($4->node_data->token);
          }
        }
     ;

  simples-expr: soma-expr relacional soma-expr {
                  //printf("simples-expr <- soma-expr relacional soma-expr\n");
                  $$ = $2;

                  enum simpl_expr_enum {soma_expr1, soma_expr2};
                  $2->child[soma_expr1] = $1;
                  $2->child[soma_expr2] = $3;
                  $$->n_child = 2;
                }
              | soma-expr {
                  //printf("simples-expr <- soma-expr\n");
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
                //printf("soma-expr <- soma-expr soma termo\n");
                $$ = $2;

                enum soma_expr_enum {soma_expr, soma_termo};
                $2->child[soma_expr] = $1;
                $2->child[soma_termo] = $3;
                $$->n_child = 2;
                $$->node_data->datatype = $3->node_data->datatype;
              }
           |  termo {
                //printf("soma-expr <- termo\n");
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
            //printf("termo <- termo mult fator\n");
            $$ = $2;

            enum mult_enum {mult_termo, mult_fator};
            $2->child[mult_termo] = $1;
            $2->child[mult_fator] = $3;
            $$->n_child = 2;
            $$->node_data->datatype = $3->node_data->datatype;
  }
       |  fator {
            //printf("termo <- fator\n");
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
  
  fator:  LPAREN expr RPAREN {
            //printf("fator <- LPAREN expr RPAREN\n");
            $$ = $2;
          }
       |  var {
            //printf("fator <- var\n");
            $$ = $1;
            $$->node_data->datatype = INTEGER_T;
          }
       |  ativacao {
            //printf("fator <- ativacao\n");
            $$ = $1;
            $$->node_data->datatype = VOID_T;
            if(!strcmp($1->node_data->lexem, "input")) $$->node_data->datatype = INTEGER_T;
          }
       |  num {
            //printf("fator <- num\n");
            $$ = $1;
            $$->node_data->datatype = INTEGER_T;
          }
       ;
  
  ativacao: id LPAREN args RPAREN {
              //printf("ativacao <- id LPAREN args RPAREN\n");
              $$ = $1;
              enum ativacao_enum {ativacao_args};
              $$->child = syntax_tree_alloc_node(1);
              $$->child[ativacao_args] = $3; /* isso pode ser NULL */
              $$->n_child = 1;
              $$->node_data->nodetype = FUNCAO;
              $$->isActivation = 1;
              if(!strcmp($1->node_data->lexem, "input")) $$->isActivation = 0;
              if(!strcmp($1->node_data->lexem, "output")) $$->isActivation = 0;
            }
          ;

  args: arg-list {
          //printf("args <- arg-list\n");
          $$ = $1;
        }
      | {
          //printf("args <- vazio\n");
          $$ = NULL;
        }
      ;

  arg-list: arg-list COMMA expr {
              //printf("arg-list <- arg-list COMMA expr\n");
              $$ = $1;                
              stack_node* nod_L_mst_expr = stack_pop(pseudo_stack_L_mst_expr);
              nod_L_mst_expr->ptr->sibling = $3;
              nod_L_mst_expr->ptr = $3; /* atualiza o novo nó decl mais a esquerda da arvore */
              $3->sibling = NULL;
              stack_push(pseudo_stack_L_mst_expr, nod_L_mst_expr);
            }
           |  expr {
                //printf("arg-list <- expr\n");
                $$ = $1;
                //L_mst_expr = $1;
                $$->sibling = NULL;

                stack_node* nod = stack_alloc_node();
                nod->ptr = $$;
                stack_push(pseudo_stack_L_mst_expr, nod);
              }
           ;

%%

static int yylex(){
  TokenNode* curr_token = next_token();
  int tok_num = END;
  char *tok;
  if(curr_token){
    tok = curr_token->token;
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

syntax_tree*  parseTree(){
  tree = syntax_tree_alloc_node(3);
  pseudo_stack_R_mst_decl_node = stack_alloc();                                
  pseudo_stack_R_mst_param = stack_alloc();
  pseudo_stack_L_var_decl = stack_alloc();                                
  pseudo_stack_L_stmt = stack_alloc();
  pseudo_stack_L_mst_expr = stack_alloc();
  yyparse();

  return tree;
}

void yyerror(char *c){
  if(yychar != ERR && yychar != END){
    printf("ERRO SINTATICO: %s LINHA: %d\n", _curr_token->token, _curr_token->line);
    exit(1);
  }
}
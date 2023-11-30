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
  syntax_tree* tree;

  int tok_to_num(char *);
  char* deepCopy(char *);
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
      $$ = syntax_tree_alloc_node(3);
      $$->node_data->token = "ID";
      $$->node_data->lexem = deepCopy(lex);
      $$->node_data->line = lineno;
    }
    ;

  num: NUMBER {
    $$ = syntax_tree_alloc_node(3);
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
              $$ = syntax_tree_alloc_node(1);
              $$->node_data->token = "INT";
              $$->node_data->lexem = "int";
              $$->node_data->datatype = INTEGER_T;
              $$->n_child = 1;
              $$->child[0] = $2;
              $2->child[0] = $4;
              $2->child[1] = $6;
              $2->child[0]->node_data->scope = $2->node_data->lexem;
              $2->child[1]->node_data->scope = $2->node_data->lexem;
              $2->n_child = 2;
              $2->node_data->nodetype = FUNCAO;
            }
          | VOID id LPAREN params RPAREN composto-decl {
              $$ = syntax_tree_alloc_node(1);
              $$->node_data->token = "VOID";
              $$->node_data->lexem = "void";
              $$->node_data->datatype = VOID_T;
              $$->n_child = 1;
              $$->child[0] = $2;
              $2->child[0] = $4;
              $2->child[1] = $6;
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

  composto-decl:  LKEY local-decls statement-lista RKEY {
                  $$ = $2;
                  if($$ != NULL){
                    while($$->sibling != NULL) $$ = $$->sibling;
                    $$->sibling = $3;
                    $$ = $2;
                  }
                  else $$ = $3;
                }
                | LKEY local-decls RKEY { $$ = $2; }
                | LKEY statement-lista RKEY { $$ = $2; }
                | LKEY RKEY { $$ = NULL; }
                ;

  local-decls:  local-decls var-decl {
                  $$ = $1;      
                  if($$ != NULL){
                    while($$->sibling != NULL) $$ = $$->sibling;
                    $$->sibling = $2;
                    $$ = $1;
                  }   
                  else $$ = $2;     
                }
             |  var-decl { $$ = $1; }
             ;

  statement-lista:  statement-lista statement {
                    $$ = $1;      
                    if($$ != NULL){
                      while($$->sibling != NULL) $$ = $$->sibling;
                      $$->sibling = $2;
                      $$ = $1;
                    }   
                    else $$ = $2;     
                 }
                 | statement{ $$ = $1; }
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

  selec-decl: IF LPAREN expr RPAREN statement { 
                $$ = syntax_tree_alloc_node(2);
                $$->n_child = 2;
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
            | IF LPAREN expr RPAREN statement ELSE statement {
                $$ = syntax_tree_alloc_node(3);
                $$->n_child = 3;
                $$->child[0] = $3;
                $$->child[1] = $5;
                $$->child[1] = $7;
              }
            ;

  iter-decl:  WHILE LPAREN expr RPAREN statement {
                $$ = syntax_tree_alloc_node(2);
                $$->n_child = 2;
                $$->child[0] = $3;
                $$->child[1] = $5;
              }
           ;

  retorno-decl: RETURN SEMICOLON {
                 $$ = syntax_tree_alloc_node(0);
                 $$->n_child = 0;
                 $$->node_data->datatype = VOID_T;
              }
              | RETURN expr SEMICOLON {
                $$ = syntax_tree_alloc_node(1);
                $$->n_child = 1;
                $$->child[0] = $2;
              }
              ;

  expr: var ASS expr {
          syntax_tree* asgn_node = syntax_tree_alloc_node(2);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->n_child = 2;
        }
      | simples-expr {
          $$ = $1;
        }
      ;

  var:  id { $$ = $1; }
     |  id LBRA expr RBRA {
          $$ = $1;
          $$->n_child = 1;
          $$->node_data->datatype = VARIAVEL;
          $$->node_data->datatype = INTEGER_T;
          $$->child[0] = $3;
        }
     ;

  simples-expr: soma-expr relacional soma-expr {
                  $$ = $2;
                  $$->n_child = 2;
                  $2->child[0] = $1;
                  $2->child[1] = $3;
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
                $$->n_child = 2;
                $2->child[0] = $1;
                $2->child[1] = $3;
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
            $$->n_child = 2;
            $2->child[0] = $1;
            $2->child[1] = $3;
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
       |  num {$$ = $1; }
       ;
  
  ativacao: id LPAREN args RPAREN {
            $$ = $1;
            $$->n_child = 1;
            $$->child[0] = $3;
          }
          ;

  args: arg-list {
          $$ = $1;
        }
      |
      ;

  arg-list: arg-list COMMA expr {
            $$ = $1;
            if($$ != NULL){
              while($$->sibling != NULL) $$ = $$->sibling;
              $$->sibling = $3;
              $$ = $1;
            }
            else $$ = $3;
           }
           |  expr { $$ = $1;}
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

char * deepCopy(char * source){ 
    if (source==NULL) return NULL;
    int n = strlen(source)+1;
    char* target = malloc(sizeof(char) * n);
    if (target==NULL) printf("Out of Memory\n");
    else strcpy(target,source);

    return target;
}

int main(int argv, char **argc){
  yyparse();
  syntax_tree *t = tree;
  printTokenNode(t->node_data);
  printTokenNode(t->child[0]->child[0]->child[0]->node_data);
  t = t->sibling;
  if(!t) printf("NULL\n");
  printTokenNode(t->node_data);

  return 0;
}

void yyerror(char *c){
  if(yychar != ERR && yychar != END){
    printf("ERRO SINTATICO: %s LINHA: %d\n", c, lineno);
    exit(1);
  }
}
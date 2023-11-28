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
  syntax_tree* tree;            /* raiz da syntax_tree*/
  syntax_tree* R_mst_decl_node; /* (utilizado para as regras 2 e 3 da CFG) mantem um ponteiro pro nó declaracao
                                   mais a direita corrente na arvore 
                                */
  syntax_tree* R_mst_param;     /* (utilizado para as regras 8 e 9 da CFG) mantem um ponteiro pro nó param
                                   mais a direita corrente na arvore que se origina de param-list 
                                */


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
                R_mst_decl_node->sibling = $2;
                $2->sibling = NULL;
                R_mst_decl_node = $2; /* atualiza o novo nó decl mais a direita da arvore */
              }
            | decl {
                $$ = $1;
                R_mst_decl_node = $1; /* seta o no mais a direita no caso base de decl-lista */
              }
            ;

  decl: var-decl {$$ = $1;}
      | fun-decl {$$ = $1;}
      ;

  var-decl: tipo-especificador ID SEMICOLON {
              enum var_decl_enum {espc_type, id, skol};

              $$ = syntax_tree_alloc_node(3);

              $$->child[espc_type] = $1;
              $$->child[id] = syntax_tree_alloc_node(0);
              $$->child[skol] = syntax_tree_alloc_node(0);
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
              $$->child[params] = syntax_tree_alloc_node(0);
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
                  R_mst_param->sibling = $3;
                  $3->sibling = NULL;
                  R_mst_param = $3; /* atualiza o novo nó param mais a direita da arvore */
                }
            | param {
                $$ = $1;
                R_mst_param = $1; /* seta o no mais a direita no caso base de param-lista */
              }
            ;

  param: tipo-especificador ID { printf("tipo ID\n"); }
       | tipo-especificador ID LBRA RBRA { printf("tipo ID []\n"); }
       ;

  composto-decl: LKEY local-decls statement-lista RKEY { printf("composto-decl\n"); }
               ;

  local-decls: local-decls var-decl {}
             | {}
             ;

  statement-lista: statement-lista statement {}
                 | {}
                 ;

  statement: expr-decl {}
           | composto-decl {}
           | selec-decl {}
           | iter-decl {}
           | retorno-decl {}
           ;

  expr-decl: expr SEMICOLON {}
           | SEMICOLON {}
           ;

  selec-decl: IF LPAREN expr RPAREN statement {}
            | IF LPAREN expr RPAREN statement ELSE statement {}
            ;

  iter-decl: WHILE LPAREN expr RPAREN statement {}
           ;

  retorno-decl: RETURN SEMICOLON {}
              | RETURN expr SEMICOLON { printf("return expr;\n"); }
              ;

  expr: var ASS expr {}
      | simples-expr {}
      ;

  var: ID {}
     | ID LBRA expr RBRA {}
     ;

  simples-expr: soma-expr relacional soma-expr {}
              | soma-expr
              ;

  relacional: LET {}
            | LT {}
            | GT {}
            | GET {}
            | EQL {}
            | NEQL {}
            ;

  soma-expr: soma-expr soma termo {}
           | termo {}
           ;

  soma: PLUS {}
      | MINUS {}
      ;

  termo: termo mult fator {}
       | fator {}
       ;

  mult: TIMES {}
      | DIV {}
      ;
  
  fator: LPAREN expr RPAREN {}
       | var {}
       | ativacao {}
       | NUMBER { printf("number\n"); }
       ;
  
  ativacao: ID LPAREN args RPAREN { printf("ativacao\n"); }
          ;

  args: arg-list {}
      |
      ;

  arg-list: arg-list COMMA expr {}
           | expr {}
           ;

%%

static int yylex(){
  TokenNode* curr_token = next_token();
  int tok_num = END;
  char *tok, *lex;
  if(curr_token){
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
  printf("Token not found: %s\n", tok);
  return -1;
}

int main(int argv, char **argc){
  return yyparse();
}

void yyerror(char *c){
  printf("ERRO SINTATICO: %s\n", c);
}
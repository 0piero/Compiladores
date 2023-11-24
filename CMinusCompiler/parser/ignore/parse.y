%{
  #include <stdio.h>
  #include <string.h>
  #include "./lexical_analyzer/get_token.h"
  #include "./parse.tab.h"

  static int yylex(void);
  TokenNode* next_token();
  int tok_to_num(char *);
  void yyerror(char *);
%}

%start program
%token IF ELSE WHILE INT VOID RETURN
%token NUMBER ID
%token EQL
%token ERR END

%%
  program: IF program { printf("IF\n"); }
          | ELSE { printf("ELSE\n"); }
          | WHILE { printf("WHILE\n"); }
          | 
%%

static int yylex(){
  char* tok = next_token()->token;
  int tok_num = tok_to_num(tok);
  printf("Current token: %s - %d\n", tok, tok_num);
  return tok_num;
}

int tok_to_num(char* tok){
  if(!strcmp(tok, "IF")) return IF;
  if(!strcmp(tok, "ELSE"))return ELSE;
  if(!strcmp(tok, "WHILE"))return WHILE;
  printf("Token not found: %s\n", tok);
  return -1;
}

int main(int argv, char **argc){
  return yyparse();
}

void yyerror(char *c){
  printf("ERRO SINTATICO: %s\n", c);
}
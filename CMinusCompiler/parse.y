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

%start programa
%token IF ELSE WHILE INT VOID RETURN
%token NUMBER ID
%token EQL
%token LPAREN RPAREN LBRA RBRA LKEY RKEY SEMICOLON
%token ERR END

%%
  programa: decl-lista {}
            ;

  decl-lista: decl-lista decl {}
            | decl {}
            ;

  decl: var-decl {}
      | fun-decl {}
      ;

  var-decl: tipo-especificador ID SEMICOLON {}
          | tipo-especificador ID LBRA NUMBER RBRA SEMICOLON {}
          ;

  tipo-especificador: INT {printf("int\n");}
                    | VOID {printf("void\n");}
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
    printf("Last token received!\n");
  }
  if(lex)
   printf("Current Token: %s Lexem: %s\n", tok, lex);
  else
   printf("Current Token: %s\n", tok);
   
  return tok_num;
}

int tok_to_num(char* tok){
  if(!strcmp(tok, "ID")) return ID;
  if(!strcmp(tok, "IF")) return IF;
  if(!strcmp(tok, "ELSE"))return ELSE;
  if(!strcmp(tok, "INT"))return INT;
  if(!strcmp(tok, "VOID"))return VOID;
  if(!strcmp(tok, "WHILE"))return WHILE;
  if(!strcmp(tok, "["))return LBRA;
  if(!strcmp(tok, "]"))return RBRA;
  if(!strcmp(tok, ";"))return SEMICOLON;
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
%{
    #include <stdio.h>
    #include <stdlib.h>

    int curr_line = 1;

    void run_comment();
%}
ESPECIAL_CHAR [\+\*-/=<\(\);]
ATTRIBUTION :=
IF if
ELSE else
THEN then
END end
REPEAT reapeat
UNTIL until
READ read
WRITE write
NUMERO [0-9]+
IDENTIFICADOR [a-zA-Z]+
COMENTARIO \{
BLANK_SPACE [ \t]
%%
{COMENTARIO}         {run_comment();}
{BLANK_SPACE}        {}
{ESPECIAL_CHAR}      {printf("Line: %d - Lexem: %s - Token: ESPECIAL CHAR\n", curr_line, yytext);}
{ATTRIBUTION}        {printf("Line: %d - Lexem: %s - Token: ATTRIBUTION\n", curr_line, yytext);}
{IF}                 {printf("Line: %d - Lexem: %s - Token: IF\n", curr_line, yytext);}
{ELSE}               {printf("Line: %d - Lexem: %s - Token: ELSE\n", curr_line, yytext);}
{THEN}               {printf("Line: %d - Lexem: %s - Token: THEN\n", curr_line, yytext);}
{END}                {printf("Line: %d - Lexem: %s - Token: END\n", curr_line, yytext);}
{REPEAT}             {printf("Line: %d - Lexem: %s - Token: REPEAT\n", curr_line, yytext);}
{UNTIL}              {printf("Line: %d - Lexem: %s - Token: UNTIL\n", curr_line, yytext);}
{WRITE}              {printf("Line: %d - Lexem: %s - Token: WRITE\n", curr_line, yytext);}
{READ}               {printf("Line: %d - Lexem: %s - Token: READ\n", curr_line, yytext);}
{NUMERO}             {printf("Line: %d - Lexem: %s - Token: NUMBER\n", curr_line, yytext);}
{IDENTIFICADOR}      {printf("Line: %d - Lexem: %s - Token: IDENTIFIER\n", curr_line, yytext);}

\n              {curr_line++;}
<<EOF>>         {return 0;}
%%  
int yywrap(){}

void run_comment(){
    while(1){
        char c = input();
        if(c == '\n') curr_line++;
        if(c == '}') return;
    }
}

int main(int argc, char* argv[]){

    if(argc == 2){
        FILE * fp; 
        fp = fopen(argv[1], "r");   
        yyin = fp;    
    }else{
        printf("Uso incorreto\n");
        exit(1);
    }

    
    yylex();
    return 0;
}

%{
    #include <stdio.h>
    #include <stdlib.h>

    int expr();
    int termo();
    int fator();
    int eat(int token);

    int token = 0;
%}

NUM [0-9]
SOMA [\+-]
MULT [\*/]
PARENTESES \(|\)

%%

{NUM}           {return 1;}
{SOMA}          {return 2;}
{MULT}          {return 3;}
{PARENTESES}    {return 4;}

<<EOF>>         {return 0;}
%%  
int yywrap(){}

int expr(){
    int firstTemp, secondTemp;

    firstTemp = termo();
    while(token == 2){
        int op = eat(token);
        secondTemp = termo();
        int result;
        if(op == (int)'+'){
            printf("Soma: %d + %d = %d\n", firstTemp, secondTemp, firstTemp+secondTemp);
            result = firstTemp+secondTemp;
        }
        if(op == (int)'-'){
            printf("Subtracao: %d - %d = %d\n", firstTemp, secondTemp, firstTemp-secondTemp);
            result = firstTemp-secondTemp;
        }
        firstTemp = result;
    }

    return firstTemp;
}

int termo(){
    int firstTemp, secondTemp;

    firstTemp = fator();
    while(token == 3){
        int op = eat(token);
        secondTemp = fator();
        int result;
        if(op == (int)'*'){
            printf("Mult: %d * %d = %d\n", firstTemp, secondTemp, firstTemp*secondTemp);
            result = firstTemp*secondTemp;
        }
        if(op == (int)'/'){
            printf("Divisao: %d / %d = %d\n", firstTemp, secondTemp, firstTemp/secondTemp);
            result = firstTemp/secondTemp;
        }
        firstTemp = result;
    }

    return firstTemp;
}

int fator(){
    if(token == 1){
        return eat(token);
    }

    int num;

    eat(token);
    num = expr();
    eat(token);

    return num;
}

int eat(int local_token){
    printf("Casamento: %d com %s\n", local_token, yytext);

    int num = -1;

    if(local_token == 1) num = atoi(yytext);
    else num = (int) yytext[0];
    
    token = yylex();
    
    return num;
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

//    while(token){
//       token = yylex();
//    }

    token = yylex();
    expr();


    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "funcs.h"

#define BUFFER_SIZE 8
#define FILE_EOF -1

void clear_buffer(buffer buff){
    int i = 0;
    for(i = 0; i < BUFFER_SIZE; i++){
        buff.word_buffer[i] = '\0';
    }
}

void clear_lex(char* lex){
    for(int i = 0; i < 65; i++) lex[i] = '\0';
}

buffer allocate_buffer(FILE * fptr){
    buffer buff;
    buff.fp = fptr;
    buff.curr_char_pos = 0;
    buff.curr_line = 1;
    buff.word_buffer = (char*) malloc(BUFFER_SIZE);
    clear_buffer(buff);
    printf("[+] allocated buffer\n");
    return buff;
}

lexema allocate_lexema(){
    lexema lex;
    lex.line = 0;
    lex.lexema = (char*) malloc(65);
    lex.token = 0;
    printf("[+] allocated lexem!\n");
    return lex;
}

char get_next_char (buffer* buffer, int flag){
    char curr_char = buffer->word_buffer[buffer->curr_char_pos];

    if(buffer->word_buffer[buffer->curr_char_pos] == '\n'){
        buffer->curr_line += 1;
    }

    if(flag) buffer->curr_char_pos += 1;
    // printf("[!] get_next_char returned: %c - %d - %d\n", curr_char, buffer->curr_char_pos, buffer->curr_line);

    return curr_char;
}

void deallocate_buffer(buffer* ptr){
    free(ptr->word_buffer);
}


void deallocate_lexema(lexema* ptr){
    free(ptr->lexema);
}

int strcmp(const char *X, const char *Y){
    while (*X)
    {
        if (*X != *Y) {
            break;
        }
        X++;
        Y++;
    }

    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int isSpecialChar(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' ||
        c == '=' || c == '<' || c == '(' || c == ')' ||
        c == ';')
        return 1;
    return 0;
}

int updateLexem(char c, lexema* lex, int state, int pos){
    switch (state){
        case 1:
            if(c != '\n') lex->lexema[pos] = c;
            lex->token = 1;
            return -1;
        case 2:
            if(c != '\n') lex->lexema[pos] = c;
            lex->token = 2;
            return 3;
        case 3:
            if(c != '\n') lex->lexema[pos] = c;
            lex->token = 2;
            return -1;
        case 4:
            lex->token = 3;
            return 4;
        case 5:
            lex->token = 3;
            return 0;
        case 6:
            if(isalpha(c)) lex->lexema[pos] = c;
            lex->token = 4;
            return 6;
        case 7:
            lex->token = 4;
            return -1;
        case 8:
            lex->token = 5;
            return -1;
        case 9:
            if(c != '\n') lex->lexema[pos] = c;
            lex->token = 6;
            return 9;
        case 10:
            if(c != '\n') lex->lexema[pos] = c;
            lex->token = 6;
            return -1;
        
        return -1;
    }
}

void print_tiny_token(int token, char* lexem){
    // printf("inside func: %d\n", token);
    switch (token){
        case 1:
            printf("SPECIAL CHAR\n");
            break;
        case 2:
            printf("ATRIBUITTION\n");
            break;
        case 3:
            printf("LOL\n");
            break;
        case 4:
            printf("IDENTIFIER\n");
            break;
        case 5:
            if(!strcmp(lexem, "if")){
                printf("IF\n");
            } else if(!strcmp(lexem, "else")){
                printf("ELSE\n");
            } else if(!strcmp(lexem, "then")){
                printf("THEN\n");
            } else if(!strcmp(lexem, "repeat")){
                printf("REPEAT\n");
            } else if(!strcmp(lexem, "until")){
                printf("UNTIL\n");
            } else if(!strcmp(lexem, "read")){
                printf("READ\n");
            } else if(!strcmp(lexem, "write")){
                printf("WRITE\n");
            } else if(!strcmp(lexem, "end")){
                printf("END\n");
            }            break;
        case 6:
            printf("DIGIT\n");
            break;
        default:
            printf("NOT FOUND\n");
            break;
    }
}

// int get_token(lexema * lexema){
//     if(!strcmp(lexema->lexema, "if")) {
//         lexema->token = IF;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "else")){
//         lexema->token = ELSE;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "auto")){
//         lexema->token = AUTO;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "break")){
//         lexema->token = BREAK;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "case")){
//         lexema->token = CASE;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "char")){
//         lexema->token = CHAR;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "const")){
//         lexema->token = CONST;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "continue")){
//         lexema->token = CONTINUE;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "default")){
//         lexema->token = DEFAULT;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "do")){
//         lexema->token = DO;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "double")){
//         lexema->token = DOUBLE;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "enum")){
//         lexema->token = ENUM;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "extern")){
//         lexema->token = EXTERN;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "float")){
//         lexema->token = FLOAT;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "for")){
//         lexema->token = FOR;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "goto")){
//         lexema->token = GOTO;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "int")){
//         lexema->token = INT;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "long")){
//         lexema->token = LONG;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "register")){
//         lexema->token = REGISTER;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "return")){
//         lexema->token = RETURN;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "short")){
//         lexema->token = SHORT;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "signed")){
//         lexema->token = SIGNED;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "sizeof")){
//         lexema->token = SIZEOF;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "static")){
//         lexema->token = STATIC;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "struct")){
//         lexema->token = STRUCT;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "switch")){
//         lexema->token = SWITCH;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "typedef")){
//         lexema->token = TYPEDEF;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "union")){
//         lexema->token = UNION;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "unsigned")){
//         lexema->token = UNSIGNED;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "void")){
//         lexema->token = VOID;
//         return 1;
//     }else if(!strcmp(lexema->lexema, "while")){
//         lexema->token = WHILE;
//         return 1;
//     }else if(isdigit(lexema->lexema[0])){
//         lexema->token = NUM;
//         return 1;
//     }


//     return 0;
// }

// void print_token(int token){
//     switch(token){
//         case IF:
//             printf("IF\n");
//             break;
//         case ELSE:
//             printf("ELSE\n");
//             break;
//         case AUTO:
//             printf("AUTO\n");
//             break;
//         case BREAK:
//             printf("BREAK\n");
//             break;
//         case CASE:
//             printf("CASE\n");
//             break;
//         case CHAR:
//             printf("CHAR\n");
//             break;
//         case CONST:
//             printf("CONST\n");
//             break;
//         case CONTINUE:
//             printf("CONTINUE\n");
//             break;
//         case DEFAULT:
//             printf("DEFAULT\n");
//             break;
//         case DO:
//             printf("DO\n");
//             break;
//         case DOUBLE:
//             printf("DOUBLE\n");
//             break;
//         case ENUM:
//             printf("ENUM\n");
//             break;
//         case EXTERN:
//             printf("EXTERN\n");
//             break;
//         case FLOAT:
//             printf("FLOAT\n");
//             break;
//         case FOR:
//             printf("FOR\n");
//             break;
//         case GOTO:
//             printf("GOTO\n");
//             break;
//         case INT:
//             printf("INT\n");
//             break;
//         case LONG:
//             printf("LONG\n");
//             break;
//         case REGISTER:
//             printf("REGISTER\n");
//             break;
//         case RETURN:
//             printf("RETURN\n");
//             break;
//         case SHORT:
//             printf("SHORT\n");
//             break;
//         case SIGNED:
//             printf("SIGNED\n");
//             break;
//         case SIZEOF:
//             printf("SIZEOF\n");
//             break;
//         case STATIC:
//             printf("STATIC\n");
//             break;
//         case STRUCT:
//             printf("STRUCT\n");
//             break;
//         case SWITCH:
//             printf("SWITCH\n");
//             break;
//         case TYPEDEF:
//             printf("TYPEDEF\n");
//             break;
//         case UNION:
//             printf("UNION\n");
//             break;
//         case UNSIGNED:
//             printf("UNSIGNED\n");
//             break;
//         case VOID:
//             printf("VOID\n");
//             break;
//         case VOLATILE:
//             printf("VOLATILE\n");
//             break;
//         case WHILE:
//             printf("WHILE\n");
//             break;
//         case NUM:
//             printf("NUM\n");
//             break;
//     }
// }

int isKeyword(lexema* lexema, int pos, char curr_char){
    if(!strcmp(lexema->lexema, "if")) {
        lexema->token = IF;
        return 1;
    }else if(!strcmp(lexema->lexema, "then")){
        lexema->token = THEN;
        return 1;
    }else if(!strcmp(lexema->lexema, "else")){
        lexema->token = ELSE;
        return 1;
    }else if(!strcmp(lexema->lexema, "end")){
        lexema->token = END;
        return 1;
    }else if(!strcmp(lexema->lexema, "repeat")){
        lexema->token = REPEAT;
        return 1;
    }else if(!strcmp(lexema->lexema, "until")){
        lexema->token = UNTIL;
        return 1;
    }else if(!strcmp(lexema->lexema, "read")){
        lexema->token = READ;
        return 1;
    }else if(!strcmp(lexema->lexema, "write")){
        lexema->token = WRITE;
        return 1;
    }
    return 0;
}

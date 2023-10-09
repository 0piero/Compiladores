#include "funcs.c"

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("usage: main.c [filename]\n");
        return 0;
    }

    FILE *fptr = fopen(argv[1], "r");
    if(fptr == NULL){
        printf("error while opening file.\n");
        return 0;
    }

    buffer buff = allocate_buffer(fptr);
    lexema lex = allocate_lexema();

    char c, curr_char = 'k';
    int curr_line = buff.curr_line;
    int state = 0;
    int pos = 0;
    do {
        char * p_str = fgets(buff.word_buffer, BUFFER_SIZE, fptr);
        
        if(curr_line == buff.curr_line){
            // printf("[%d]", buff.curr_line);
            curr_line++;
        }

        while(buff.curr_char_pos != BUFFER_SIZE - 1){
            curr_char = get_next_char(&buff, 1);
            // if(curr_char == '\0') printf("curr_char: /0 | %d\n", state);
            // printf("curr_char: %c | %d\n", curr_char, state);

            // especiais

            if(isSpecialChar(curr_char) && state == 0){
                state = 1;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line;
                continue;
            }

            // atribuicao

            if(curr_char == ':' && state == 0){
                state = 2;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line;
            }

            if(curr_char == '=' && state == 3){
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line;
                continue;
            }

            // comentarios

            if(curr_char ==  '{' && state == 0){
                state = 4;
                state = updateLexem(curr_char, &lex, state, pos);
                continue;
            }

            if(curr_char ==  '}' && state == 4){
                state = 5;
                state = updateLexem(curr_char, &lex, state, pos);
                continue;
            }

            if(state == 4){
                state = updateLexem(curr_char, &lex, state, pos);
                continue;
            }

            // palavras chaves

            if(isalpha(curr_char) && state == 0){
                state = 6;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line ;
                if(!isalpha(get_next_char(&buff, 0))){
                    printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                    print_tiny_token(lex.token, lex.lexema);
                    pos = 0;
                    clear_lex(lex.lexema);
                    lex.token = 0;
                    state = 0;
                    continue;
                }
                continue;
            }

            if(!isalpha(curr_char) && state == 6){
                if(isKeyword(&lex, pos, curr_char)) state = 8;
                else state = 7;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                if(state == -1){
                    printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                    print_tiny_token(lex.token, lex.lexema);
                    pos = 0;
                    clear_lex(lex.lexema);
                    lex.token = 0;
                    state = 0;
                    continue;
                }
                continue;
            }

            if(state == 6){
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line;
                continue;
            }

            // numeros

            if(isdigit(curr_char) && state == 0){
                state = 9;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line ;
                if(!isdigit(get_next_char(&buff, 0))){
                    printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                print_tiny_token(lex.token, lex.lexema);
                    pos = 0;
                    clear_lex(lex.lexema);
                    lex.token = 0;
                    state = 0;
                    continue;
                }
                continue;
            }

            if(!isdigit(curr_char) && state == 9){
                state = 10;
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                continue;
            }

            if(state == 9){
                state = updateLexem(curr_char, &lex, state, pos);
                pos++;
                lex.line = buff.curr_line;
                continue;
            }


            if(state == -1){
                printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                print_tiny_token(lex.token, lex.lexema);
                pos = 0;
                clear_lex(lex.lexema);
                lex.token = 0;
                state = 0;
                continue;
            }

            // if(isalpha(curr_char) && (state == 0 || state == 1)) {
            //     lex.lexema[pos] = curr_char;
            //     pos++;
            //     state = 1;
            // } 
            
            // if(isdigit(curr_char) && (state == 0 || state == 2)) {
            //     lex.lexema[pos] = curr_char;
            //     pos++;
            //     state = 2;
            // }
        }

        buff.curr_char_pos = 0;
        clear_buffer(buff);
        if(!p_str) break;
    } while(1);
    deallocate_lexema(&lex);
    deallocate_buffer(&buff);
    fclose(fptr);

    return 0;
}
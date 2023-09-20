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

        if(!p_str) break;
        
        if(curr_line == buff.curr_line){
            // printf("[%d]", buff.curr_line);
            curr_line++;
        }

        while(buff.curr_char_pos != BUFFER_SIZE - 1){
            curr_char = get_next_char(&buff);
            // printf("curr_char: %c | %d\n", curr_char, state);
            if(isalpha(curr_char) && (state == 0 || state == 1)) {
                lex.lexema[pos] = curr_char;
                pos++;
                state = 1;
            } 

            if(state == 1){
                if(!isalpha(curr_char) ){
                    lex.line = buff.curr_line;
                    int isValidToken = get_token(&lex);
                    if(isValidToken){
                        printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                        print_token(lex.token);
                    }
                    pos = 0;
                    clear_lex(lex.lexema);
                    state = 0;
                    lex.token = 0;
                }
            }
            
            if(isdigit(curr_char) && (state == 0 || state == 2)) {
                lex.lexema[pos] = curr_char;
                pos++;
                state = 2;
            };

            if(state == 2){
                if(!isdigit(curr_char)){
                    lex.line = buff.curr_line;
                    int isValidToken = get_token(&lex);
                    if(isValidToken){
                        printf("Linha: %d - Lexema: %s - Token: ", lex.line, lex.lexema);
                        print_token(lex.token);
                    }
                    pos = 0;
                    clear_lex(lex.lexema);
                    state = 0;
                    lex.token = 0;
                }
            }
        }

        buff.curr_char_pos = 0;
        clear_buffer(buff);
    } while(1);
    deallocate_lexema(&lex);
    deallocate_buffer(&buff);
    fclose(fptr);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "./utils/input_reader.h"
#include "./utils/lexem.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"


int main(){

    // run_tests();

    FILE *fp = fopen("input.txt", "r");
    input_buffer input_buff = create_and_allocate_input_buffer();
    lexem_buffer lexem_buff = create_and_allocate_lexem_buffer();
    table dfa_table = create_and_allocate_table(11, 9); // (row, col)
    default_table_init(dfa_table);

    /* Initial state  */
    int state = 0; 
    int curr_char_idx = -1;

    do {
        char * p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
        char curr_char;
        boolean update_char_num = TRUE, update_line_num = TRUE;

        while(input_buff.curr_char_pos != BUFFER_SIZE - 1){
            curr_char = get_next_char(&input_buff, update_char_num, update_line_num);
            if(curr_char == '\n') break; // Caso contrário, ele cai nesse if(curr_char == '\0') return 0;
            
            /* 
                Esse trecho aqui é bem rabisco mesmo, a gente 
                precisa pensar o jeito certinho de fazer.

                Sugestões:
                - Criar função para tratar o estado final.
            */

            curr_char_idx = get_current_char_idx(curr_char, state);
            // printf("char: %c state-1: %d idx: %d ", curr_char, state, curr_char_idx);

            if(curr_char_idx == INVALID_CHAR){
                printf("ERRO LÉXICO: %c", curr_char);
                printf("LINHA: %d", input_buff.curr_line);
                exit(1);                
            }

            state = dfa_table[state][curr_char_idx];
            // printf("state-2: %d\n", state);

            if(state == SA){
                // printf("Code: %d ", atoi(code));
                print_lexem(&lexem_buff, atoi(code));
                state = 0;
                input_buff.curr_char_pos--; // Funciona como um não inclui [other], manter o continue.
                reset_code();
                if(curr_char == '\0') {
                    free(lexem_buff.word_buffer);
                    free(input_buff.word_buffer);
                    for(int k = 0; k < 10; k++){
                        free(dfa_table[k]);
                    }
                    free(dfa_table);
                    fclose(fp);
                    return 0;
                }
                continue;
            }
            if (state == 0){
                // printf("<CLEAR>\n");
                lexem_buff.curr_char_pos = 0;
                clear_lexem_buffer(lexem_buff);
                reset_code();
                continue;
            }

            update_lexem_buffer(&lexem_buff, curr_char, input_buff.curr_line, state);        
        }

        input_buff.curr_char_pos = 0;
        clear_input_buffer(input_buff);
        if(!p_str) break;
    } while(1);

    free(lexem_buff.word_buffer);
    free(input_buff.word_buffer);
    for(int k = 0; k < 11; k++){
        free(dfa_table[k]);
    }
    free(dfa_table);
    fclose(fp);
    return 0;
}
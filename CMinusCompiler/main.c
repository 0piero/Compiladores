#include <stdio.h>
#include "./utils/input_reader.h"
#include "./utils/lexem.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"


int main(){

    run_tests();

    FILE *fp = fopen("input.txt", "r");
    input_buffer input_buff = create_and_allocate_input_buffer();
    lexem_buffer lexem_buff = create_and_allocate_lexem_buffer();
    table dfa_table = create_and_allocate_table(4, 4);
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

            // printf("Previous state: %d\n", state);

            state = dfa_table[state][curr_char_idx];
            if(curr_char=='\0') state = SA;

            if(state == SA){
                print_lexem(&lexem_buff);
                state = 0;
                input_buff.curr_char_pos--; // Funciona como um não inclui [other], manter o continue.
                if(curr_char == '\0') return 0;
                continue;
            }

            update_lexem_buffer(&lexem_buff, curr_char, input_buff.curr_line, state);        
        }

        input_buff.curr_char_pos = 0;
        clear_input_buffer(input_buff);
        if(!p_str) break;
    } while(1);

    return 0;
}
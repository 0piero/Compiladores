#include <stdio.h>
#include "./utils/input_reader.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"

int main(){

    run_tests();

    FILE *fp = fopen("input.txt", "r");
    input_buffer input_buff = create_and_allocate_buffer();
    table dfa_table = create_and_allocate_table(3, 3);
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

            /* 
                Esse trecho aqui é bem rabisco mesmo, a gente 
                precisa pensar o jeito certinho de fazer.

                Sugestões:
                - Criar função que retorne o curr_char_idx correto.
                - Adicionar estados de aceitação na tabela.
                - Criar função para traatar o estado final.
            */
           if(is_digit(curr_char)) curr_char_idx = 0;
           if(is_alpha(curr_char)) curr_char_idx = 1;
           if(is_special_char(curr_char)) curr_char_idx = 2;

            state = dfa_table[state][curr_char_idx];

            if(curr_char=='\0') state = SA;

            if(state == SA){
                printf("Lex accepted!\n");
                state = 0;
                input_buff.curr_char_pos--; 
                if(curr_char == '\0') return 0;
                continue;
            }

            printf("Char: %c Line: %d State: %d\n", curr_char, input_buff.curr_line, state);
        }

        input_buff.curr_char_pos = 0;
        clear_buffer(input_buff);
        if(!p_str) break;
    } while(1);

    return 0;
}
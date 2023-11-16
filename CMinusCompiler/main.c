#include <stdio.h>
#include <stdlib.h>
#include "./utils/input_reader.h"
#include "./utils/lexem.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"

static FILE *fp = NULL;
static input_buffer input_buff;
static lexem_buffer lexem_buff;
static table dfa_table;
static int state = 0; 
static int curr_char_idx = -1;
static char *p_str;
static char curr_char;

char* next_token() {
    if (!fp) {
        fp = fopen("input.txt", "r");
        input_buff = create_and_allocate_input_buffer();
        lexem_buff = create_and_allocate_lexem_buffer();
        dfa_table = create_and_allocate_table(11, 9);
        default_table_init(dfa_table);
        p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
    }
    
    boolean update_char_num = TRUE, update_line_num = TRUE;

    if (input_buff.curr_char_pos == BUFFER_SIZE - 1 || curr_char == '\n') {
        input_buff.curr_char_pos = 0;
        clear_input_buffer(input_buff);
        p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
        if (!p_str) return NULL;
    }

    while(input_buff.curr_char_pos != BUFFER_SIZE - 1){
        curr_char = get_next_char(&input_buff, update_char_num, update_line_num);
        curr_char_idx = get_current_char_idx(curr_char, state);

        if(curr_char_idx == INVALID_CHAR){
            printf("ERRO LÉXICO: %c", curr_char);
            printf("LINHA: %d\n", input_buff.curr_line);
            exit(1);                
        }

        state = dfa_table[state][curr_char_idx];

        if(state == SA) {
            char* token = strdup(lxm_to_token((&lexem_buff)->word_buffer));
            state = 0;
            input_buff.curr_char_pos--; 
            lexem_buff.curr_char_pos = 0;
            clear_lexem_buffer(lexem_buff);
            reset_code();
            if(curr_char == '\0') {
                free(lexem_buff.word_buffer);
                free(input_buff.word_buffer);
                for(int k = 0; k < 10; k++){
                    free(dfa_table[k]);
                }
                free(dfa_table);
                fclose(fp);
                return token;
            }
            return token;
        }

        if (state == 0){
            lexem_buff.curr_char_pos = 0;
            clear_lexem_buffer(lexem_buff);
            reset_code();
            continue;
        }

        update_lexem_buffer(&lexem_buff, curr_char, input_buff.curr_line, state);        
    }

    return NULL;
}

int main() {
    char *token;

    printf("Running...\n");

    while ((token = next_token()) != NULL) {
        printf("Token: %s\n", token);
        free(token);
    }

    free(lexem_buff.word_buffer);
    free(input_buff.word_buffer);
    for(int k = 0; k < 11; k++){
        free(dfa_table[k]);
    }
    free(dfa_table);
    fclose(fp);
    return 0;
}


// int main(){

//     // run_tests();

//     FILE *fp = fopen("input.txt", "r");
//     FILE *output = fopen("output.txt", "w");

//     

//     /* Initial state  */
//     int state = 0; 
//     int curr_char_idx = -1;

//     do {
//         char * p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
//         char curr_char;
//         boolean update_char_num = TRUE, update_line_num = TRUE;



//         input_buff.curr_char_pos = 0;
//         clear_input_buffer(input_buff);
//         if(!p_str) break;
//     } while(1);

  
// }
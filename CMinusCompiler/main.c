#include <stdio.h>
#include "./utils/input_reader.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"

int main(){

    FILE *fp = fopen("input.txt", "r");
    input_buffer input_buff = create_and_allocate_buffer();
    table dfa_table = create_and_allocate_table();

    test_char_type_checker();

    /* Initial state  */
    int state = 0; 

    do {
        char * p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
        char curr_char;
        boolean update_char_num = TRUE, update_line_num = TRUE;

        while(input_buff.curr_char_pos != BUFFER_SIZE - 1){
            curr_char = get_next_char(&input_buff, update_char_num, update_line_num);
            if(curr_char == '\0') break;
            printf("Char: %c Line: %d\n", curr_char, input_buff.curr_line);
        }

        input_buff.curr_char_pos = 0;
        clear_buffer(input_buff);
        if(!p_str) break;
    } while(1);

    return 0;
}
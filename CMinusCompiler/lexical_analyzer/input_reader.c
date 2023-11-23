#include "input_reader.h"

void clear_input_buffer(input_buffer buff){
    int i = 0;
    for(i = 0; i < BUFFER_SIZE; i++){
        buff.word_buffer[i] = '\0';
    }
}

input_buffer create_and_allocate_input_buffer(){
    input_buffer buff;
    buff.curr_char_pos = 0;
    buff.curr_line = 1;
    buff.word_buffer = (char*) malloc(BUFFER_SIZE);
    clear_input_buffer(buff);
    // printf("[+] allocated buffer\n");
    return buff;
}

char get_next_char(input_buffer *buffer, boolean update_char_flag, boolean update_line_flag){
    char curr_char = buffer->word_buffer[buffer->curr_char_pos];

    if(buffer->word_buffer[buffer->curr_char_pos] == '\n' && update_line_flag)buffer->curr_line += 1;
    if(update_char_flag) buffer->curr_char_pos += 1;

    return curr_char;
}
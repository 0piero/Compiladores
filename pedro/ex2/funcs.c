#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

#define BUFFER_SIZE 256
#define FILE_EOF -1

void clear_buffer(buffer buff){
    int i = 0;
    for(i = 0; i < BUFFER_SIZE; i++){
        buff.word_buffer[i] = '\0';
    }
}

buffer allocate_buffer(FILE * fptr){
    buffer buff;
    buff.fp = fptr;
    buff.curr_char_pos = 0;
    buff.curr_line = 1;
    buff.word_buffer = (char*) malloc(BUFFER_SIZE);
    clear_buffer(buff);
    printf("[+] allocated with success!\n");
    return buff;
}

char get_next_char (buffer* buffer){
    char curr_char = buffer->word_buffer[buffer->curr_char_pos];

    if(buffer->word_buffer[buffer->curr_char_pos] == '\n'){
        buffer->curr_line += 1;
    }

    buffer->curr_char_pos += 1;

    // printf("[!] get_next_char returned: %c - %d - %d\n", curr_char, buffer->curr_char_pos, buffer->curr_line);

    return curr_char;
}

buffer deallocate_buffer(buffer* ptr){
    free(ptr->word_buffer);
}
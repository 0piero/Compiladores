#include <stdlib.h>
#include <stdio.h>
#include "funcs.h"

void clear_buffer(buffer buff, int buff_size){
    int i = 0;
    for(i = 0; i < buff_size; i++){
        buff.word_buffer[i] = '\0';
    }
    // buff.word_buffer[buff_size+1] = '\0';
}

buffer allocate_buffer(int buff_size){
    buffer buff;
    buff.buff_size = buff_size;
    buff.word_buffer = (char*) malloc(buff_size);
    clear_buffer(buff, buff_size);
    // printf("buff size: %d - last char: %c\n", buff.buff_size, buff.word_buffer[buff_size+1]);
    return buff;
}

void replace_print(buffer buffer){
    int i;
    char ch;
    for(i = 0; i < buffer.buff_size; i++){
        if(buffer.word_buffer[i]=='a' ||buffer.word_buffer[i]=='e' ||buffer.word_buffer[i]=='i' ||buffer.word_buffer[i]=='o' ||buffer.word_buffer[i]=='u')
            buffer.word_buffer[i]=buffer.word_buffer[i]-32;
        else if(buffer.word_buffer[i]=='A' ||buffer.word_buffer[i]=='E' ||buffer.word_buffer[i]=='I' ||buffer.word_buffer[i]=='O' ||buffer.word_buffer[i]=='U')
            buffer.word_buffer[i]=buffer.word_buffer[i]+32;
        fputc(buffer.word_buffer[i], stdout);
    }
    // clear_buffer(buffer, buffer.buff_size);
    // printf("\nlast char: %d\n", buffer.word_buffer[buffer.buff_size+1]);
}

buffer deallocate_buffer(buffer* ptr){
    free(ptr->word_buffer);
}
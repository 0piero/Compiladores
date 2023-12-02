#include "lexem.h"
#include "token.h"

void clear_lexem_buffer(lexem_buffer buff){
    int i = 0;
    for(i = 0; i < LEX_BUFF_SIZE; i++){
        buff.word_buffer[i] = '\0';
    }
}

lexem_buffer create_and_allocate_lexem_buffer(){
    lexem_buffer buff;
    buff.state = -1;
    buff.curr_line = 1;
    buff.curr_char_pos = 0;
    buff.word_buffer = (char*) malloc(LEX_BUFF_SIZE);
    clear_lexem_buffer(buff);
    return buff;
}

void update_lexem_buffer(lexem_buffer *lexem_buff, char curr_char, int curr_line, int code){
    lexem_buff->word_buffer[lexem_buff->curr_char_pos] = curr_char;
    lexem_buff->curr_line = curr_line;
    lexem_buff->state = code;
    lexem_buff->curr_char_pos++;
}

void print_lexem(lexem_buffer *lexem_buff){
    printf("Line: %d Token: %s Lexem: [%s]\n", 
                lexem_buff->curr_line, 
                lxm_to_token(lexem_buff->word_buffer), 
                lexem_buff->word_buffer
        );
    lexem_buff->curr_char_pos = 0;
    clear_lexem_buffer(*lexem_buff);
}
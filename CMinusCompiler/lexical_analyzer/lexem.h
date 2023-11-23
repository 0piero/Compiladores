#ifndef LEXEM_H
#define LEXEM_H

#include <stdlib.h>
#include <stdio.h>
#include "generic_types.h"
#include "token.h"

#define LEX_BUFF_SIZE 1024

void clear_lexem_buffer(lexem_buffer buff);
lexem_buffer create_and_allocate_lexem_buffer();
void update_lexem_buffer(lexem_buffer *lexem_buff, char curr_char, int curr_line, int state);
void print_lexem(lexem_buffer *lexem_buff);

#endif
#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdlib.h>
#include <stdio.h>
#include "generic_types.h"


#define BUFFER_SIZE 128

void clear_input_buffer(input_buffer buff);
input_buffer create_and_allocate_input_buffer();
char get_next_char(input_buffer* buffer, boolean update_char_flag, boolean update_line_flag);

#endif
#ifndef INPUT_READER_H
#define INPUT_READER_H

#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/* Put it here since its related to input size, not buffer structure itself. */
#define BUFFER_SIZE 32

void clear_buffer(input_buffer buff);
input_buffer create_and_allocate_buffer();
char get_next_char(input_buffer* buffer, boolean update_char_flag, boolean update_line_flag);

#endif
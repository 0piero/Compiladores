#ifndef TYPES_H
#define TYPES_H

#define TRUE 1
#define FALSE 0

typedef int boolean;

struct buff {
    int curr_char_pos;
    int curr_line;
    char * word_buffer;
};
typedef struct buff input_buffer;

#endif
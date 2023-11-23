#ifndef GENERIC_TYPES_H
#define GENERIC_TYPES_H

#define TRUE 1
#define FALSE 0

typedef int boolean;
typedef int** table;

struct buff {
    int curr_char_pos;
    int curr_line;
    char * word_buffer;
};
typedef struct buff input_buffer;

struct lexem {
    int state;
    int curr_line;
    int curr_char_pos;
    char * word_buffer;
};
typedef struct lexem lexem_buffer;

#endif
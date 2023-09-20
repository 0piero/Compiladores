struct buff {
    FILE *fp;
    int curr_char_pos;
    int curr_line;
    char * word_buffer;
};

typedef struct buff buffer;
#define IF 1
#define THEN 2
#define ELSE 3
#define REPEAT 4
#define UNTIL 5
#define READ 6
#define WRITE 7
#define END 8

struct buff {
    FILE *fp;
    int curr_char_pos;
    int curr_line;
    char * word_buffer;
};
typedef struct buff buffer;

struct lexema {
    int line;
    char* lexema;
    int token;
};
typedef struct lexema lexema;
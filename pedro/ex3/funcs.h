#define IF 1
#define ELSE 2
#define AUTO 3
#define BREAK 4
#define CASE 5
#define CHAR 6
#define CONST 7
#define CONTINUE 8
#define DEFAULT 9 
#define DO 10
#define DOUBLE 11
#define ENUM 12
#define EXTERN 13
#define FLOAT 14
#define FOR 15
#define GOTO 16
#define INT 17
#define LONG 18
#define REGISTER 19
#define RETURN 20
#define SHORT 21
#define SIGNED 22
#define SIZEOF 23
#define STATIC 24
#define STRUCT 25
#define SWITCH 26
#define TYPEDEF 27
#define UNION 28
#define UNSIGNED 29
#define VOID 30
#define VOLATILE 31
#define WHILE 32


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
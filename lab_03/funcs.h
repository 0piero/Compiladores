#ifndef FUNCUTILS_H
#define FUNCUTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct token token;
typedef struct Buffer Buffer;
typedef struct token_list token_list;

struct Buffer{
	char buf[256];
	int next_char;
	int num_line;
	int* ptr_token;
	token_list* token_list;
	int curr_read;
	token* hdy;
};

struct token{
	int line;
	token* next;
	char* typ;
};

struct token_list{
	token* hdy;
	int len;
};

void insert_tkn(token_list* tkl, token* tkn);
char get_next_char(Buffer* buf, FILE* fptr);
Buffer* allocate_buffer(void);
int deallocate_buffer(Buffer* buf);
char ctch_token(Buffer* buf, FILE* fptr);
void display_tkn_list(token_list* tkl);

#endif
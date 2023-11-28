#ifndef GET_TOKEN_H
#define GET_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include "./input_reader.h"
#include "./lexem.h"
#include "./char_type_checker.h"
#include "./table.h"
#include "../common/types.h"

static FILE *fp = NULL;
static input_buffer input_buff;
static lexem_buffer lexem_buff;
static table dfa_table;
static int state = 0; 
static int flag = 0;
static int curr_char_idx = -1;
static char *p_str;
static char curr_char;

int isBufferWhitespace(char *buffer);
int isSubBufferWhitespace(char *buffer, int start);
TokenNode* next_token();
void clean_buffers();
#endif
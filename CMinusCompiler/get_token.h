#ifndef GET_TOKEN_H
#define GET_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include "./utils/input_reader.h"
#include "./utils/lexem.h"
#include "./utils/char_type_checker.h"
#include "./utils/table.h"
#include "./tests/tests.h"

static FILE *fp = NULL;
static input_buffer input_buff;
static lexem_buffer lexem_buff;
static table dfa_table;
static int state = 0; 
static int curr_char_idx = -1;
static char *p_str;
static char curr_char;

char* next_token();
void clean_buffers();
#endif
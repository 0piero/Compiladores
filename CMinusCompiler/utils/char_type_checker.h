#ifndef CHAR_TYPE_CHECKER_H
#define CHAR_TYPE_CHECKER_H

#include "generic_types.h"
#include "table.h"

char previous_symbol;

boolean is_digit(char curr_char);
boolean is_alpha(char curr_char);
boolean is_special_char(char curr_char);
boolean is_special_symbol(char first_char, char second_char);
int get_current_char_idx(char c, int state);

#endif
#ifndef CHAR_TYPE_CHECKER_H
#define CHAR_TYPE_CHECKER_H

#include "types.h"

boolean is_digit(char curr_char);
boolean is_alpha(char curr_char);
boolean is_special_char(char curr_char);
boolean is_special_symbol(char first_char, char second_char);

#endif
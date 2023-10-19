#ifndef CHAR_TYPE_CHECKER_H
#define CHAR_TYPE_CHECKER_H

#include "generic_types.h"
#include "table.h"
#include "code.h"
#define INVALID_CHAR -1

boolean is_digit(char curr_char);
boolean is_alpha(char curr_char);
boolean is_alpha_grp1(char curr_char);
boolean is_i_char(char curr_char);
boolean is_f_char(char curr_char);
boolean is_special_char(char curr_char);
boolean is_special_symbol(char first_char, char second_char);
boolean is_special_char_grp1(char curr_char);
boolean is_special_char_grp2(char curr_char);
boolean is_right_bar(char curr_char);
boolean is_star(char curr_char);
boolean is_equal_sgn(char curr_char);
boolean is_valid(char curr_char);
boolean is_white(char curr_char);
int get_current_char_idx(char c, int state);

#endif
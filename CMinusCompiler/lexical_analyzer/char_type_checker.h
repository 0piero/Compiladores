#ifndef CHAR_TYPE_CHECKER_H
#define CHAR_TYPE_CHECKER_H

#include <string.h>
#include <stdio.h>
#include "generic_types.h"
#include "table.h"
#define INVALID_CHAR -1
#define WHITE_SPACE_CHAR -2
#define UNFINISHED_COOMENT -3

boolean is_digit(char curr_char);
boolean is_alpha(char curr_char);
boolean is_alpha_grp1(char curr_char);

boolean is_i_char(char curr_char);
boolean is_f_char(char curr_char);
boolean is_e_char(char curr_char);
boolean is_l_char(char curr_char);
boolean is_s_char(char curr_char);
boolean is_n_char(char curr_char);
boolean is_t_char(char curr_char);
boolean is_r_char(char curr_char);
boolean is_u_char(char curr_char);
boolean is_v_char(char curr_char);
boolean is_o_char(char curr_char);
boolean is_d_char(char curr_char);
boolean is_w_char(char curr_char);
boolean is_h_char(char curr_char);

boolean is_special_char(char curr_char);
boolean is_special_symbol(char first_char, char second_char);
boolean is_special_char_grp1(char curr_char);
boolean is_special_char_grp2(char curr_char);
boolean is_right_bar(char curr_char);
boolean is_star(char curr_char);
boolean is_equal_sgn(char curr_char);
boolean is_valid(char curr_char, int curr_state);
boolean is_white(char curr_char);
int get_current_char_idx(char c, int state);

#endif
#include "char_type_checker.h"
#include <ctype.h>
#include <stdio.h>

boolean is_digit(char curr_char){
    if(isdigit(curr_char)) return TRUE;
    return FALSE;
}

boolean is_alpha(char curr_char){
    if(isalpha(curr_char)) return TRUE;
    return FALSE;
}

boolean is_alpha_grp1(char curr_char){
    if(
        isalpha(curr_char) && 
        curr_char != 'i' &&
        curr_char != 'e' &&
        curr_char != 'r' &&
        curr_char != 'v' &&
        curr_char != 'w'
    ) return TRUE;
    return FALSE;
}

boolean is_i_char(char curr_char){
    if(curr_char == 'i') return TRUE;
    return FALSE;
}

boolean is_f_char(char curr_char){
    if(curr_char == 'f') return TRUE;
    return FALSE;
}

boolean is_e_char(char curr_char){
    if(curr_char == 'e') return TRUE;
    return FALSE;
}

boolean is_l_char(char curr_char){
    if(curr_char == 'l') return TRUE;
    return FALSE;
}

boolean is_s_char(char curr_char){
    if(curr_char == 's') return TRUE;
    return FALSE;
}

boolean is_n_char(char curr_char){
    if(curr_char == 'n') return TRUE;
    return FALSE;
}

boolean is_t_char(char curr_char){
    if(curr_char == 't') return TRUE;
    return FALSE;
}

boolean is_r_char(char curr_char){
    if(curr_char == 'r') return TRUE;
    return FALSE;
}

boolean is_u_char(char curr_char){
    if(curr_char == 'u') return TRUE;
    return FALSE;
}

boolean is_v_char(char curr_char){
    if(curr_char == 'v') return TRUE;
    return FALSE;
}

boolean is_o_char(char curr_char){
    if(curr_char == 'o') return TRUE;
    return FALSE;
}

boolean is_d_char(char curr_char){
    if(curr_char == 'd') return TRUE;
    return FALSE;
}

boolean is_w_char(char curr_char){
    if(curr_char == 'w') return TRUE;
    return FALSE;
}

boolean is_h_char(char curr_char){
    if(curr_char == 'h') return TRUE;
    return FALSE;
}

boolean is_special_char(char curr_char){
    if(
        curr_char == '+' ||
        curr_char == '-' ||
        curr_char == '*' ||
        curr_char == '/' ||
        curr_char == '<' ||
        curr_char == '=' ||
        curr_char == '>' ||
        curr_char == '!' ||
        curr_char == ';' ||
        curr_char == ',' ||
        curr_char == '(' ||
        curr_char == ')' ||
        curr_char == ')' ||
        curr_char == '[' ||
        curr_char == ']' ||
        curr_char == '{' ||
        curr_char == '}'
    ) return TRUE;
    return FALSE;
}

boolean is_special_char_grp1(char curr_char){ /* grupo 1 só dos que formam tokens de tamanho 1 exceto '/' */
    if(
        curr_char == '+' ||
        curr_char == '-' ||
        curr_char == '*' ||
        curr_char == ';' ||
        curr_char == ',' ||
        curr_char == '(' ||
        curr_char == ')' ||
        curr_char == ')' ||
        curr_char == '[' ||
        curr_char == ']' ||
        curr_char == '{' ||
        curr_char == '}'
    ) return TRUE;
    return FALSE;   
}

boolean is_special_char_grp2(char curr_char){ /* grupo 2 só dos que podem formar tokens de tamanho 2
                                                exceto '/' */
    if(
        curr_char == '<' ||
        curr_char == '=' ||
        curr_char == '>' ||
        curr_char == '!'
    ) return TRUE;
    return FALSE;
}

boolean is_right_bar(char curr_char){
    if (curr_char == '/') return TRUE;
    return FALSE;
}

boolean is_star(char curr_char){
    if (curr_char == '*') return TRUE;
    return FALSE;
}

boolean is_equal_sgn(char curr_char){
    if (curr_char == '=') return TRUE;
    return FALSE;
}

boolean is_white(char curr_char){
    if (
        curr_char == ' '  ||
        curr_char == '\n' ||
        curr_char == '\t' ||
        curr_char == '\0'
        ) return TRUE;
    return FALSE;
}

boolean is_valid(char curr_char){
    if (is_white(curr_char)) return TRUE;
    if (is_alpha(curr_char)) return TRUE;
    if (is_digit(curr_char)) return TRUE;
    if (is_special_char(curr_char)) return TRUE;
    return FALSE;
}

/* Double char symbols */
boolean is_special_symbol(char first_char, char second_char){
    if(
        (first_char == '<' && second_char == '=') ||
        (first_char == '>' && second_char == '=') ||
        (first_char == '=' && second_char == '=') ||
        (first_char == '!' && second_char == '=') 
    ) return TRUE;
    return FALSE;
}

boolean is_open_comment(char first_char, char second_char){
    if(
        (first_char == '/' && second_char == '*')
    ) return TRUE;
    return FALSE;
}

boolean is_close_comment(char first_char, char second_char){
    if(
        (first_char == '*' && second_char == '/')
    ) return TRUE;
    return FALSE;
}

int get_current_char_idx(char c, int state){
    if (!is_valid(c)) return INVALID_CHAR;
    switch (state){
        case 0:
            if(is_white(c)) return WHITE_SPACE_COL;
            if(is_digit(c)){
                reset_code();
                add_digit_code('8');
                return DIGIT_COL;
            }
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_COL;
            }
            if(is_special_char_grp1(c)){
                reset_code();
                add_digit_code('9');
                return SYMBOL1_COL;
            } // vai pra S3
            if(is_special_char_grp2(c)){
                reset_code();
                add_digit_code('9');
                return SYMBOL2_COL;
            }  // vai pra S4
            if(is_right_bar(c)) {
                reset_code();
                add_digit_code('9');
                return BAR_COL;
            } // vai pra S5
        case 1:
            if(is_digit(c)) return DIGIT_COL;
            if(!is_digit(c)) return CHAR_COL; // Estado de aceitação
        case 2:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_COL ;
            } // ID que ainda não terminou (exemploe: iABC)
            if(!is_alpha(c)) return DIGIT_COL; // Estado de aceitação
        case 3:
            return DIGIT_COL; // qualquer character vai p aceitacao
        case 4:
            if(is_equal_sgn(c)) return EQUAL_SGN_COL; // vai pra S3
            return DIGIT_COL;
        case 5:
            if(is_star(c)) return STAR_COL; //vai pra S6
            return DIGIT_COL; // aceita
        case 6:
            if(is_star(c)) return STAR_COL; //vai pra S7
            return DIGIT_COL; // vai pra S6
        case 7:
            if(is_right_bar(c)) return BAR_COL; //vai pra S0
            if(is_star(c)) return STAR_COL;
            return DIGIT_COL;
    }
    return -1;
}

int get_word_token(char *lexem){
    int state = 0;

    for(int i = 0; i < strlen(lexem)+1; i++){
        switch(state){
        case 0:
            if(is_alpha_grp1(lexem[i])) return 6;
            else if(is_i_char(lexem[i])) state = 1;
            break;
        case 1:
            if(is_f_char(lexem[i])) state = 2;
            else if(is_n_char(lexem[i])) state = 3;
            else return 6;
            break;
        case 2:
            if(lexem[i] == '\0') return 1;
            else return 6;
            break;
        case 3:
            if(is_t_char(lexem[i])) state = 4;
            else return 6;
            break;
        case 4:
            if(lexem[i] == '\0') return 2;
            else return 6;
            break;
        case 5:
            break;
        }
    }

    return 6;
}
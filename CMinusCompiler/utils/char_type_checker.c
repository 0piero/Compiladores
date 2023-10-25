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
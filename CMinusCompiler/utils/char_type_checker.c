#include "char_type_checker.h"
#include <ctype.h>

boolean is_digit(char curr_char){
    if(isdigit(curr_char)) return TRUE;
    return FALSE;
}

boolean is_alpha(char curr_char){
    if(isalpha(curr_char)) return TRUE;
    return FALSE;
}

/* Single char symbols */
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

/* Double char symbols */
boolean is_special_symbol(char first_char, char second_char){
    if(
        (first_char == '<' && second_char == '=') ||
        (first_char == '>' && second_char == '=') ||
        (first_char == '=' && second_char == '=') ||
        (first_char == '!' && second_char == '=') ||
        (first_char == '/' && second_char == '*') ||
        (first_char == '*' && second_char == '/')
    ) return TRUE;
    return FALSE;
}

int get_current_char_idx(char c, int state){
    switch (state){
        case 0:
            if(is_digit(c)) return DIGIT_COL;
            if(is_alpha(c)) return CHAR_COL;
            if(is_special_char(c)) {
                previous_symbol = c;
                return SYMBOL_COL;
            }
        case 1:
            if(is_digit(c)) return DIGIT_COL;
            if(!is_digit(c)) return CHAR_COL; // Estado de aceitação
        case 2:
            if(is_alpha(c)) return CHAR_COL;
            if(!is_alpha(c)) return DIGIT_COL; // Estado de aceitação
        case 3:
            if(is_special_symbol(previous_symbol, c)) return SYMBOL_COL; // Estado de aceitação
            if(!is_special_char(c)) return DIGIT_COL; // Estado de aceitação
            if(is_special_char(c)) return DIGIT_COL; // Estado de aceitação
    }

    return -1; // Retorna -1 porque não deveria chegar neste ponto.
}
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
            if(is_alpha_grp1(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            if(is_i_char(c)){
                add_digit_code('2');
                return I_CHAR_COL;
            }
            if(is_e_char(c)){
                add_digit_code('1');
                return E_CHAR_COL;
            }
            if(is_r_char(c)){
                add_digit_code('4');
                return R_CHAR_COL;
            }
            if(is_v_char(c)){
                add_digit_code('7');
                return V_CHAR_COL;
            }
            if(is_w_char(c)){
                add_digit_code('5');
                return W_CHAR_COL;
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
            if(!is_digit(c)) return CHAR_GRP1_COL; // Estado de aceitação
        case 2:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
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
        case 8:
            if(is_f_char(c)){ // Palavra reservada IF
                add_digit_code('0');
                return F_CHAR_COL;
            } 
            if(is_n_char(c)){ // Palavra reservada INT
                add_digit_code('1');
                return N_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 9:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            reset_code();
            add_digit_code('2');
            return DIGIT_COL;
        case 10:
            if(is_l_char(c)){ // Palavra reservada ELSE
                add_digit_code('0');
                return L_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 11:
            if(is_s_char(c)){ // Palavra reservada ELSE
                add_digit_code('0');
                return S_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 12:
            if(is_e_char(c)){ // Palavra reservada ELSE
                add_digit_code('0');
                return E_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 13:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            reset_code();
            add_digit_code('1');
            return DIGIT_COL;
        case 14:
            if(is_t_char(c)){ // Palavra reservada INT
                add_digit_code('1');
                return T_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 15:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            reset_code();
            add_digit_code('3');
            return DIGIT_COL;
        case 16:
            if(is_e_char(c)){ // Palavra reservada RETURN
                add_digit_code('0');
                return E_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 17:
            if(is_t_char(c)){ // Palavra reservada RETURN
                add_digit_code('1');
                return T_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 18:
            if(is_u_char(c)){ // Palavra reservada RETURN
                add_digit_code('1');
                return U_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 19:
            if(is_r_char(c)){ // Palavra reservada RETURN
                add_digit_code('0');
                return R_CHAR_COL;
            } 
            if(is_alpha(c)) {
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 20:
            if(is_n_char(c)){ // Palavra reservada RETURN
                add_digit_code('0');
                return N_CHAR_COL;
            } 
            if(is_alpha(c)) {
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 21:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            reset_code();
            add_digit_code('5');
            return DIGIT_COL;
        case 22:
            if(is_o_char(c)){ // Palavra reservada VOID
                add_digit_code('0');
                return O_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } 
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 23:
            if(is_i_char(c)){ // Palavra reservada VOID
                add_digit_code('0');
                return I_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } 
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 24:
            if(is_d_char(c)){ // Palavra reservada VOID
                add_digit_code('2');
                return D_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 25:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            }
            reset_code();
            add_digit_code('4');
            return DIGIT_COL;
        case 26:
            if(is_h_char(c)){ // Palavra reservada WHILE
                add_digit_code('0');
                return H_CHAR_COL;
            } 
            if(is_alpha(c)) {
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 27:
            if(is_i_char(c)){ // Palavra reservada WHILE
                add_digit_code('0');
                return I_CHAR_COL;
            } 
            if(is_alpha(c)) {
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 28:
            if(is_l_char(c)){ // Palavra reservada WHILE
                add_digit_code('7');
                return L_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 29:
            if(is_e_char(c)){ // Palavra reservada WHILE
                add_digit_code('1');
                return E_CHAR_COL;
            } 
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            return DIGIT_COL; // ID que terminou (exemplo: i%)
        case 30:
            if(is_alpha(c)){
                reset_code();
                add_digit_code('7');
                return CHAR_GRP1_COL;
            } // ID que ainda não terminou (exemploe: iABC)
            reset_code();
            add_digit_code('6');
            return DIGIT_COL;
    }
    return -1;
}
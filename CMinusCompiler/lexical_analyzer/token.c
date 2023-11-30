#include "token.h"
#include "hash.h"

int str_to_int(char* lxm){
    int s_lxm = strlen(lxm);
    int key = 0;
    key += (int) lxm[0];

    if (isupper(lxm[0])) key -= 64;
    else key -= 70;

    if (s_lxm > 1){
        int c = (int) lxm[1];
        if (isupper(lxm[1])) c -= 64;
        else c -= 70;
        key += 53 * c;
    }
    return key;
}

char* lxm_to_token(char* lxm){
    if(is_digit(lxm[0])) return "NUMBER";
    if(!is_digit(lxm[0]) && !is_alpha(lxm[0])) return symbol_to_token(lxm);

	int int_repr = str_to_int(lxm);
	int idx = hash_func(int_repr);
	if (idx >= 6) return "ID";
	else if (!strcmp(__rsv_word_tbl[idx], lxm)) return __token_tbl[idx];
	else return "ID";
}

char* symbol_to_token(char* symbol){
    if(strlen(symbol) == 1){
        if(symbol[0] == '+') return "+";
        if(symbol[0] == '-') return "-";
        if(symbol[0] == '*') return "*";
        if(symbol[0] == '/') return "/";
        if(symbol[0] == '=') return "=";
        if(symbol[0] == '<') return ">";
        if(symbol[0] == '>') return ">";
        if(symbol[0] == ';') return ";";
        if(symbol[0] == ',') return ",";
        if(symbol[0] == '(') return "(";
        if(symbol[0] == ')') return ")";
        if(symbol[0] == '[') return "[";
        if(symbol[0] == ']') return "]";
        if(symbol[0] == '{') return "{";
        if(symbol[0] == '}') return "}";
    }
    
    if(strlen(symbol) == 2){
        if(symbol[0] == '<' && symbol[1] == '=') return "<=";
        if(symbol[0] == '>' && symbol[1] == '=') return ">=";
        if(symbol[0] == '=' && symbol[1] == '=') return "==";
        if(symbol[0] == '!' && symbol[1] == '=') return "!=";
    }
}
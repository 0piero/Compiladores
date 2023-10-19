#include "code.h"
#include <stdio.h>

void reset_code(){
    curr_code_pos = 0;
    for(int i = 0; i < MAX_CODE_SIZE; i++){
        code[i] = '\0';
    }
}

void add_digit_code(char c){
    code[curr_code_pos] = c;
    curr_code_pos++;
}
#ifndef CODE_H
#define CODE_H

#define MAX_CODE_SIZE 9

char code[MAX_CODE_SIZE];
int curr_code_pos;

void reset_code();
void add_digit_code(char c);

#endif
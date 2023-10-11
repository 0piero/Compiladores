#include <stdio.h>
#include "tests.h"

void test_char_type_checker(){
    if(
        is_special_char('/') &&
        is_special_symbol('*', '/') &&
        !is_special_char('%') &&
        !is_special_symbol('x', '/') &&
        is_digit('9') &&
        !is_digit('x') &&
        is_alpha('x')&&
        !is_alpha('9')
    ) {
        printf("[+] test_char_type_checker: PASS!\n");
        return;
    }
    else {
        printf("[-] test_char_type_checker: FAIL!\n");
        exit(1);
    }
}

void test_input_reader(){
    input_buffer buffer = create_and_allocate_buffer();
    buffer.word_buffer[0] = 'a';

    char c = get_next_char(&buffer, TRUE, TRUE);

    if(
        c == 'a' &&
        buffer.curr_char_pos == 1 &&
        buffer.curr_line == 1
    ) {
        printf("[+] test_input_reader: PASS!\n");
        return;
    }
    else {
        printf("[-] test_input_reader: FAIL!\n");
        exit(1);
    }
}

void test_table(){
    if(
       create_and_allocate_table()
    ) {
        printf("[+] test_table: PASS!\n");
        return;
    }
    else {
        printf("[-] test_table: FAIL!\n");
        exit(1);
    }
}
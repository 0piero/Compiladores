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

}

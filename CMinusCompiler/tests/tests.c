#include <stdio.h>
#include "tests.h"

void test_char_type_checker(){
    if(
        is_special_char('/') &&
        is_special_symbol('*', '/') &&
        !is_special_char('%') &&
        !is_special_symbol('x', '/')
    ) printf("[+] test_char_type_checker: PASS!\n");
    else printf("[-] test_char_type_checker: FAIL!\n");
}
#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

struct TokenNode {
    char * token;
    char * lexem;
    int line;
};
typedef struct TokenNode TokenNode;

TokenNode* allocate_token_node();

#endif
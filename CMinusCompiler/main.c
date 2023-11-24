#include "./lexical_analyzer/get_token.h"

int main() {
    TokenNode *node;

    printf("Running...\n");

    while ((node = next_token()) != NULL) {
        printf("Token: %s - %s - %d\n", node->token, node->lexem, node->line);
        free(node);
    }

    return 0;
}
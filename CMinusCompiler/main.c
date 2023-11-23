#include "./lexical_analyzer/get_token.h"

int main() {
    char *token;

    printf("Running...\n");

    while ((token = next_token()) != NULL) {
        printf("Token: %s\n", token);
        free(token);
    }

    clean_buffers();
    return 0;
}
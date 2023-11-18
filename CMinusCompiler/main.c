#include "get_token.h"

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


// int main(){

//     // run_tests();

//     FILE *fp = fopen("input.txt", "r");
//     FILE *output = fopen("output.txt", "w");

//     

//     /* Initial state  */
//     int state = 0; 
//     int curr_char_idx = -1;

//     do {
//         char * p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
//         char curr_char;
//         boolean update_char_num = TRUE, update_line_num = TRUE;



//         input_buff.curr_char_pos = 0;
//         clear_input_buffer(input_buff);
//         if(!p_str) break;
//     } while(1);

  
// }
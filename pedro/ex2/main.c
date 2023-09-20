#include "funcs.c"

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("usage: main.c [filename]\n");
        return 0;
    }

    FILE *fptr = fopen(argv[1], "r");
    if(fptr == NULL){
        printf("error while opening file.\n");
        return 0;
    }

    buffer buff = allocate_buffer(fptr);

    char c, curr_char = 'k';
    do {
        char * p_str = fgets(buff.word_buffer, BUFFER_SIZE, fptr);
        // printf("[!] p_str: %s", p_str);
        // printf("[!] word_buffer: %s", buff.word_buffer);

        if(!p_str){
            // printf("[%d]", buff.curr_line);

            while(curr_char != '\0'){
                curr_char = get_next_char(&buff);
                printf("%c", curr_char);
            }
            printf("\n");
            break;
        }
        printf("[%d]", buff.curr_line);
        while(buff.curr_char_pos != BUFFER_SIZE){
            curr_char = get_next_char(&buff);
            printf("%c", curr_char);
        }

        buff.curr_char_pos = 0;
        clear_buffer(buff);
    } while(1);
    deallocate_buffer(&buff);
    fclose(fptr);

    return 0;
}
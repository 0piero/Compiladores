#include "funcs.c"

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: main.c [filename] [buff_size]\n");
        return 0;
    }

    FILE *fptr = fopen(argv[1], "r");
    if(fptr == NULL){
        printf("error while opening file.\n");
        return 0;
    }

    buffer buff = allocate_buffer(atoi(argv[2]));

    char c;
    int i = 0;
    do {
        c = fgetc(fptr);
        if( feof(fptr) ) {
            replace_print(buff);
            break ;
        }   
      if(i == buff.buff_size){
        replace_print(buff);
        i = 0;
      }
     buff.word_buffer[i] = c;
     i++;   
    } while(1);
    deallocate_buffer(&buff);
    fclose(fptr);

    return 0;
}
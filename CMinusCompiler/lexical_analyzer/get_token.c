#include "get_token.h"

int isBufferWhitespace(char *buffer) {
    if (buffer == NULL) {
        return 0;
    }

    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0') {
            return 0;
        }
    }

    return 1;
}


int isSubBufferWhitespace(char *buffer, int start) {
    if (buffer == NULL) {
        return 0;
    }

    for (int i = start; buffer[i] != '\0'; ++i) {
        if (buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\0') {
            return 0;
        }
    }

    return 1;
}

TokenNode* next_token() {
    if(flag){
        TokenNode *node = allocate_token_node();
        node->lexem = NULL;
        node->token = "END";
        return node;
    }
    if (!fp) {
        fp = fopen("input.txt", "r");
        input_buff = create_and_allocate_input_buffer();
        lexem_buff = create_and_allocate_lexem_buffer();
        dfa_table = create_and_allocate_table(11, 9);
        default_table_init(dfa_table);
        p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
        if(!p_str) return NULL;
    }
    
    boolean update_char_num = TRUE, update_line_num = TRUE;

    TokenNode *node = allocate_token_node();
    
    if (input_buff.curr_char_pos == BUFFER_SIZE - 1 || curr_char == '\n') {
        input_buff.curr_char_pos = 0;
        clear_input_buffer(input_buff);
        p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
        if (!p_str){
            printf("EOF\n");
            return NULL;
        }
        // printf("Line: %s", input_buff.word_buffer);
        while(isBufferWhitespace(input_buff.word_buffer)){
            clear_input_buffer(input_buff);
            p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
            if (!p_str){
                printf("EOF\n");
                return NULL;
            }
            input_buff.curr_line++;
        }        
    }

    while(input_buff.curr_char_pos != BUFFER_SIZE - 1){
        curr_char = get_next_char(&input_buff, update_char_num, update_line_num);
        curr_char_idx = get_current_char_idx(curr_char, state);

        if(curr_char_idx == INVALID_CHAR && state != 6){
            printf("ERRO LÉXICO: %c - %d ", curr_char, input_buff.curr_char_pos);
            printf("LINHA: %d\n", input_buff.curr_line);
            exit(1);                
        }

        if(curr_char_idx == UNFINISHED_COOMENT){
            input_buff.curr_char_pos = 0;
            clear_input_buffer(input_buff);
            p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
            if (!p_str){
                //printf("EOF\n");
                return NULL;
            }
            // printf("State: %d\n", state);
            // printf("%s\n", input_buff.word_buffer);
            continue;
        }

        state = dfa_table[state][curr_char_idx];

        // if(curr_char ==  '\0'){
        //     printf("Char: \\0 State: %d\n", state);
        // }
        // printf("Char: %c State: %d\n", curr_char, state);


        if(state == SA) {
            node->token = strdup(lxm_to_token((&lexem_buff)->word_buffer));
            node->lexem = strdup((&lexem_buff)->word_buffer);
            node->line = (&lexem_buff)->curr_line;
            state = 0;
            input_buff.curr_char_pos--; 
            lexem_buff.curr_char_pos = 0;
            clear_lexem_buffer(lexem_buff);
            if(isSubBufferWhitespace(input_buff.word_buffer, input_buff.curr_char_pos)) {
                input_buff.curr_char_pos = BUFFER_SIZE -1;
            }
            if(curr_char == '\0') {
                flag = 1;
                free(lexem_buff.word_buffer);
                free(input_buff.word_buffer);
                for(int k = 0; k < 10; k++){
                    free(dfa_table[k]);
                }
                free(dfa_table);
                fclose(fp);
                return node;
            }
            return node;
        }

        if (state == 0){
            lexem_buff.curr_char_pos = 0;
            clear_lexem_buffer(lexem_buff);

            if(curr_char ==  '\0'){
                input_buff.curr_char_pos = 0;
                clear_input_buffer(input_buff);
                p_str = fgets(input_buff.word_buffer, BUFFER_SIZE, fp);
                if (!p_str){
                    printf("EOF\n");
                    return NULL;
                }
                continue;
            }

            continue;
        }

        update_lexem_buffer(&lexem_buff, curr_char, input_buff.curr_line, state);        
    }
    
    return NULL;
}

void clean_buffers(){
  free(lexem_buff.word_buffer);
  free(input_buff.word_buffer);
  for(int k = 0; k < 11; k++){
      free(dfa_table[k]);
  }
  free(dfa_table);
  fclose(fp);
}
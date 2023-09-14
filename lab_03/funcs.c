#include "funcs.h"


Buffer* allocate_buffer(void){
	Buffer* buf = (Buffer*) malloc(sizeof(Buffer));
	buf->next_char = 1;
	buf->curr_read = 0;
	buf->token_list = (token_list*) malloc(sizeof(token_list));
	buf->token_list->hdy = NULL;
	return buf;
}

int deallocate_buffer(Buffer* buf){
	return 0;
}

char get_next_char(Buffer* buf, FILE* fptr){

	char ret_char;
	/* n sei pq precisou >=*/
	if (buf->next_char >= buf->curr_read){

		char* ret = fgets(buf->buf, 256, fptr);
		if (ret == NULL) {printf("RET NULL\n"); return '\0';} /* verifica se o arquivo terminou */

		buf->curr_read = strlen(buf->buf);
		ret_char = (buf->buf)[0];
		buf->next_char = 1;
	}
	else {
		ret_char = (buf->buf)[buf->next_char];
		buf->next_char = buf->next_char + 1;
	}
	return ret_char;
}

char ctch_token(Buffer* buf, FILE* fptr){
	int i=0;
	char curr_char;
	int chr_cnt=0;
	char* lexema;
	int j=0;
	while(curr_char = get_next_char(buf, fptr)){
		if (isalpha(curr_char)){
			if (chr_cnt == 0) {
				lexema = (char*) malloc(sizeof(char));
				lexema[i] = curr_char;
				chr_cnt++;
				i = 1;
			}
			else {
				lexema = (char*) realloc(lexema, (i+1)); /* gambiarra */
				lexema[i] = curr_char;
				chr_cnt++;
				i++;
			}

		}
		else{
			if (chr_cnt != 0){
				chr_cnt = 0;
				lexema = (char*) realloc(lexema, (i+1)); /* gambiarra */
				lexema[i+1] = '\0';

				token* tkn = (token*) malloc((size_t) sizeof(token));
				tkn->typ = lexema;
				insert_tkn((token_list*) buf->token_list, tkn);
				i = 0;
			}
		}
		j++;
	}
}

void insert_tkn(token_list* tkl, token* tkn){
	if (tkl->hdy==NULL){tkl->hdy = tkn; tkn->next = NULL; tkl->len = 1;}
	else{		
		token* tmp = tkl->hdy;
		tkl->hdy = tkn;
		tkn->next = tmp;
		tkl->len++;
	}
}

void display_tkn_list(token_list* tkl){
	token* t = tkl->hdy;
	do{
		printf("%s\n", t->typ);
	}while(t = t->next);
}



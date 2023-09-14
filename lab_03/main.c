#include "funcs.h"


int main(int argc, char** argv){
	
	FILE* fptr = fopen(argv[1], "r");

	Buffer* buf = allocate_buffer();
	/*
	int i;
	for (i=0;i<15000;i++){
		char ret = get_next_char(&buf, fptr);
		printf("%c", ret);
	}
	*/
	ctch_token(buf, fptr);
	/* Mostra todos os tokens */
	display_tkn_list(buf->token_list);














}

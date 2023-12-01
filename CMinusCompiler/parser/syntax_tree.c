#include "./syntax_tree.h"
#include <stdlib.h>

int ident = 0;

syntax_tree* syntax_tree_alloc_node(int n_child){
	syntax_tree* t = (syntax_tree*) malloc(sizeof(syntax_tree));
	t->n_child = n_child;
	t->child = (syntax_tree**) malloc(n_child * sizeof(syntax_tree*));
	t->sibling = (syntax_tree*) malloc(sizeof(syntax_tree));
	t->node_data = allocate_token_node();
	t->n_child = 0;
	return t;
}

void syntax_tree_display(syntax_tree* root){
	root;
	while(root != NULL){
		//for(int i = 0; i < ident; i++){
		//	printf(" ");
		//}
		for(int i = 0; i < ident; i++){
			printf("__");
		}
		
		if(root->node_data){
			printf("([%d],%s,%s)", ident/2, root->node_data->token, root->node_data->lexem);
		}
		printf("\n");
		//printTokenNode(root->node_data);
		//Filhos
		ident += 2;
		for(int i = 0; i < root->n_child; i++){
			syntax_tree_display(root->child[i]);
		}
		ident -= 2;
		root = root->sibling;
	}
}







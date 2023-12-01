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
	ident += 1;
	if(ident>11) return;
	while(root != NULL){
		for(int i = 0; i < ident; i++){
			printf(" ");
		}
		if(root->node_data->token != '\0')
			printf("[%d]%s: %s\n", ident, root->node_data->token, root->node_data->lexem);
		//Filhos
		for(int i = 0; i < 3; i++){
			syntax_tree_display(root->child[i]);
		}
			root = root->sibling;
	}
	ident -= 1;
}







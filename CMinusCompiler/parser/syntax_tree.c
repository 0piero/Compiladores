#include "./syntax_tree.h"
#include <stdlib.h>


syntax_tree* syntax_tree_alloc_node(int n_child){
	syntax_tree* t = (syntax_tree*) malloc(sizeof(syntax_tree));
	t->n_child = n_child;
	t->child = (syntax_tree**) malloc(n_child * sizeof(syntax_tree*));
	t->sibling = NULL;
	t->node_data = allocate_token_node();
	t->n_child = 0;
	return t;
}

void syntax_tree_display(syntax_tree* root){
	root;



}


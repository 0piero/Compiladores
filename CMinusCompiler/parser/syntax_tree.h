#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "../common/types.h"


typedef struct syntax_tree syntax_tree;
struct syntax_tree {
	syntax_tree** child;
	syntax_tree* sibling;
	int n_child;
	TokenNode* node_data;
	int isActivation;
	int isFunDecl;
	int isVarDecl;
};

syntax_tree* syntax_tree_alloc_node(int n_child);
void syntax_tree_display(syntax_tree* root);
void update_scope(syntax_tree* root, char* scope);

#endif
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H



typedef struct syntax_tree syntax_tree;
struct syntax_tree {
	syntax_tree** child;
	syntax_tree* sibling;
	int n_child;
	void* node_data;
};

syntax_tree* syntax_tree_alloc_node(int n_child);










#endif
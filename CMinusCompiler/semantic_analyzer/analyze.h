#ifndef ANALYZE_H
#define ANALYZE_H

#include "./symbol_table_node.h"
#include "../parser/syntax_tree.h"

void semanticAnalyze(syntax_tree* tree, symbol_table_node* table);


#endif
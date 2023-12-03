#ifndef ANALYZE_H
#define ANALYZE_H

#include "./symbol_table.h"
#include "../parser/syntax_tree.h"

void semanticAnalyze(syntax_tree* tree, symbol_table* table);


#endif
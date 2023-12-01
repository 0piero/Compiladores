#include "./parse.tab.h"
#include "./common/types.h"
#include "./parser/syntax_tree.h"
#include "./parse_tree.h"

#include <stdio.h>

int main(){
  syntax_tree *st = parseTree();
  printf("Generated tree...\n");
  syntax_tree_display(st);
}
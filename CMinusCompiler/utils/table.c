#include "table.h"

int **create_and_allocate_table(){
  int **table = (int**)malloc(NUM_STATES * sizeof(int*));

  for(int i = 0; i < NUM_STATES; i++){
    table[i] = (int*)calloc(NUM_COLUMNS , sizeof(int));
  }

  return table;
}
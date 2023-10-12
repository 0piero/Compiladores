#include "table.h"

int **create_and_allocate_table(int num_states, int num_chrs){
  int **table = (int**)malloc(num_states * sizeof(int*));

  for(int i = 0; i < num_states; i++){
    table[i] = (int*)calloc(num_chrs + 1, sizeof(int));
  }
  TABLE_NUM_COLUMNS = num_chrs + 1;

  return table;
}

void insert_transition_table(int from_state_num, int to_state_num, int char_idx_trns, int** tbl){
  tbl[from_state_num][char_idx_trns] = to_state_num;
}

void set_acc_state_table(int state_num, int** tbl){
  tbl[state_num][TABLE_NUM_COLUMNS - 1] = 1;
}
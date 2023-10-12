#include "table.h"

int **create_and_allocate_table(int num_states, int num_chrs){
  int **table = (int**)malloc(num_states * sizeof(int*));

  for(int i = 0; i < num_states; i++){
    table[i] = (int*)calloc(num_chrs + 1, sizeof(int));
  }
  TABLE_NUM_COLUMNS = num_chrs + 1;

  return table;
}

void default_table_init(table tbl){
  /* S0 */
  insert_transition_table(0, DIGIT_COL , 1, tbl);
  insert_transition_table(0, CHAR_COL  , 2, tbl);
  insert_transition_table(0, SYMBOL_COL, 3, tbl);

  /* S1 */
  insert_transition_table(1, DIGIT_COL ,   1, tbl);
  insert_transition_table(1, CHAR_COL  ,  SA, tbl);
  insert_transition_table(1, SYMBOL_COL,  SA, tbl);

  /* S2 */
  insert_transition_table(2, DIGIT_COL ,  SA, tbl);
  insert_transition_table(2, CHAR_COL  ,   2, tbl);
  insert_transition_table(2, SYMBOL_COL,  SA, tbl);

  /* S3 */
  insert_transition_table(3, DIGIT_COL ,  SA, tbl);
  insert_transition_table(3, CHAR_COL  ,  SA, tbl);
  insert_transition_table(3, SYMBOL_COL,   3, tbl);
}

void insert_transition_table(int from_state_num, int char_idx_trns, int to_state_num, table tbl){
  tbl[from_state_num][char_idx_trns] = to_state_num;
}

void set_acc_state_table(int state_num, table tbl){
  tbl[state_num][TABLE_NUM_COLUMNS - 1] = 1;
}
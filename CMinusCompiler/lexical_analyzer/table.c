#include "table.h"

int **create_and_allocate_table(int num_states, int num_chrs){
  int **table = (int**)malloc(num_states * sizeof(int*));

  for(int i = 0; i < num_states; i++){
    table[i] = (int*)calloc(num_chrs + 1, sizeof(int));
  }

  return table;
}

void default_table_init(table tbl){
  /* S0 */
  insert_transition_table(0, WHITE_SPACE_COL , 0, tbl);
  insert_transition_table(0, DIGIT_COL , 1, tbl);
  insert_transition_table(0, CHAR_COL  , 2, tbl);
  insert_transition_table(0, SYMBOL1_COL, 3, tbl);
  insert_transition_table(0, SYMBOL2_COL, 4, tbl);
  insert_transition_table(0, BAR_COL, 5, tbl);

  /* S1 */
  insert_transition_table(1, DIGIT_COL ,   1, tbl);
  insert_transition_table(1, CHAR_COL  ,  SA, tbl);

  /* S2 */
  insert_transition_table(2, DIGIT_COL ,  SA, tbl);
  insert_transition_table(2, CHAR_COL  ,   2, tbl);

  /* S3 */
  insert_transition_table(3, DIGIT_COL ,  SA, tbl);

  /* S4 */
  insert_transition_table(4, DIGIT_COL ,  SA, tbl);
  insert_transition_table(4, EQUAL_SGN_COL,  3, tbl);

  /* S5 */
  insert_transition_table(5, STAR_COL  ,  6, tbl);
  insert_transition_table(5, DIGIT_COL ,  SA, tbl);

  /* S6 */
  insert_transition_table(6, STAR_COL  ,   7, tbl);
  insert_transition_table(6, DIGIT_COL ,   6, tbl);

  /* S7 */
  insert_transition_table(7, BAR_COL   , 0, tbl);
  insert_transition_table(7, STAR_COL  , 7, tbl);
  insert_transition_table(7, DIGIT_COL , 6, tbl);

  /* S8 */
  insert_transition_table(8, CHAR_COL, 2, tbl);
  insert_transition_table(8, DIGIT_COL    , SA, tbl);

  /* S9 */
  insert_transition_table(9, CHAR_COL,  2, tbl);
  insert_transition_table(9, DIGIT_COL    , SA, tbl);
}

void insert_transition_table(int from_state_num, int char_idx_trns, int to_state_num, table tbl){
  tbl[from_state_num][char_idx_trns] = to_state_num;
}
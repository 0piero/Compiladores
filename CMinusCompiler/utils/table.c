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
  insert_transition_table(0, CHAR_GRP1_COL  , 2, tbl);
  insert_transition_table(0, SYMBOL1_COL, 3, tbl);
  insert_transition_table(0, SYMBOL2_COL, 4, tbl);
  insert_transition_table(0, BAR_COL, 5, tbl);
  insert_transition_table(0, I_CHAR_COL, 8, tbl);
  insert_transition_table(0, E_CHAR_COL, 10, tbl);
  insert_transition_table(0, R_CHAR_COL, 16, tbl);

  /* S1 */
  insert_transition_table(1, DIGIT_COL ,   1, tbl);
  insert_transition_table(1, CHAR_GRP1_COL  ,  SA, tbl);

  /* S2 */
  insert_transition_table(2, DIGIT_COL ,  SA, tbl);
  insert_transition_table(2, CHAR_GRP1_COL  ,   2, tbl);

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
  insert_transition_table(8, F_CHAR_COL   ,  9, tbl);
  insert_transition_table(8, N_CHAR_COL   ,  14, tbl);
  insert_transition_table(8, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(8, DIGIT_COL    , SA, tbl);

  /* S9 */
  insert_transition_table(9, CHAR_GRP1_COL,  2, tbl);
  insert_transition_table(9, DIGIT_COL    , SA, tbl);

  /* S10 */
  insert_transition_table(10, L_CHAR_COL   ,  11, tbl);
  insert_transition_table(10, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(10, DIGIT_COL    , SA, tbl);

  /* S11 */
  insert_transition_table(11, S_CHAR_COL   ,  12, tbl);
  insert_transition_table(11, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(11, DIGIT_COL    , SA, tbl);

  /* S12 */
  insert_transition_table(12, E_CHAR_COL   ,  13, tbl);
  insert_transition_table(12, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(12, DIGIT_COL    , SA, tbl);

  /* S13 */
  insert_transition_table(13, CHAR_GRP1_COL,  2, tbl);
  insert_transition_table(13, DIGIT_COL    , SA, tbl);

  /* S14 */
  insert_transition_table(14, T_CHAR_COL   ,  15, tbl);
  insert_transition_table(14, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(14, DIGIT_COL    , SA, tbl);

  /* S15 */
  insert_transition_table(15, CHAR_GRP1_COL,  2, tbl);
  insert_transition_table(15, DIGIT_COL    , SA, tbl);

  /* S16 */
  insert_transition_table(16, E_CHAR_COL   ,  17, tbl);
  insert_transition_table(16, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(16, DIGIT_COL    , SA, tbl);

  /* 17 */
  insert_transition_table(17, T_CHAR_COL   ,  18, tbl);
  insert_transition_table(17, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(17, DIGIT_COL    , SA, tbl);

  /* S18 */
  insert_transition_table(18, U_CHAR_COL   ,  19, tbl);
  insert_transition_table(18, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(18, DIGIT_COL    , SA, tbl);

  /* S19 */
  insert_transition_table(19, R_CHAR_COL   ,  20, tbl);
  insert_transition_table(19, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(19, DIGIT_COL    , SA, tbl);

  /* S20 */
  insert_transition_table(20, N_CHAR_COL   ,  21, tbl);
  insert_transition_table(20, CHAR_GRP1_COL, 2, tbl);
  insert_transition_table(20, DIGIT_COL    , SA, tbl);

  /* S21 */
  insert_transition_table(21, CHAR_GRP1_COL,  2, tbl);
  insert_transition_table(21, DIGIT_COL    , SA, tbl);
}

void insert_transition_table(int from_state_num, int char_idx_trns, int to_state_num, table tbl){
  tbl[from_state_num][char_idx_trns] = to_state_num;
}
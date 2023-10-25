#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include "generic_types.h"

#define DIGIT_COL 0
#define CHAR_COL 1
#define SYMBOL1_COL 2
#define SYMBOL2_COL 3
#define BAR_COL 4
#define STAR_COL 5
#define EQUAL_SGN_COL 6
#define WHITE_SPACE_COL 7


#define SA 999

int **create_and_allocate_table(int num_states, int num_chrs);
void default_table_init(table tbl);
void insert_transition_table(int from_state_num, int to_state_num, int char_trns, table tbl);


#endif
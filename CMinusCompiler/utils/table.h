#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include "generic_types.h"

#define DIGIT_COL 0
#define CHAR_COL 1
#define SYMBOL_COL 2

#define SA 999

int TABLE_NUM_COLUMNS;

int **create_and_allocate_table(int num_states, int num_chrs);
void default_table_init(table tbl);
void insert_transition_table(int from_state_num, int to_state_num, int char_trns, table tbl);
void set_acc_state_table(int state_num, table tbl);


#endif
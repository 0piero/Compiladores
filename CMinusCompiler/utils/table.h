#ifndef TABLE_H
#define TABLE_H

#define DIGIT 0
#define CHARACTER 1
#define SYMBOL 2

int TABLE_NUM_COLUMNS;

typedef int** table;

#include <stdlib.h>

int **create_and_allocate_table(int num_states, int num_chrs);
void insert_transition_table(int from_state_num, int to_state_num, int char_trns, int** tbl);
void set_acc_state_table(int state_num, int** tbl);

#endif
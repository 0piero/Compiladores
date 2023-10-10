#ifndef TABLE_H
#define TABLE_H

#define DIGIT 0
#define CHARACTER 1
#define SYMBOL 2

#define NUM_STATES 4
#define NUM_COLUMNS 3

typedef int** table;

#include <stdlib.h>

int **create_and_allocate_table();

#endif
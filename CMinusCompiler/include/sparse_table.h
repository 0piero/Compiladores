#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

typedef struct sparse_table sparse_table;
struct sparse_table{
	int* idx;
	void* data;
};

#endif

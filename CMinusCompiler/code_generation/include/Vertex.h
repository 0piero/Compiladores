#ifndef VERTEX_H
#define VERTEX_H

#include "List.h"

typedef struct Vertex Vertex;
struct Vertex{
	List* adj_list;
	void* data;
	int num_nbrs;
	int color;
};

Vertex* alloc_vtx(void);

#endif

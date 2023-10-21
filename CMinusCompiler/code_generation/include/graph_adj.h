#ifndef GRAPH_ADJ_H
#define GRAPH_ADJ_H

#include "Vertex.h"

typedef struct Graph_adj Graph_adj;
struct Graph_adj{
	Vertex** vtx;
	int num_vtx;
};

Graph_adj* alloc_graph_adj(void);
void graph_adj_insert_vtx(Graph_adj* g, Vertex* v);
void graph_adj_make_edge(Graph_adj* g, Vertex* u, Vertex* v); /* make edge (u,v) */
void graph_adj_delete_edge(Graph_adj* g, Vertex* u, int idx); /* delete edge (u,u->adj_list[idx]) */
unsigned int dfs(Graph_adj* g, void* arg);
void dfs_visit(Graph_adj* g, Vertex* u, void* arg);


#endif

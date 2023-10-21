#include "Vertex.h"
#include "List.h"
#include <stdlib.h>

typedef struct Vertex Vertex;

Vertex* alloc_vtx(void){
	Node* nod = (Node*) malloc(sizeof(Node));
	Vertex* vtx = (Vertex*) malloc(sizeof(Vertex));
	List* adj_list = list_alloc();

	vtx->adj_list = adj_list;
	vtx->num_nbrs = 0;
	vtx->data = (void*) malloc(sizeof(void));
	return vtx;
}




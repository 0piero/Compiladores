#include "Node.h"
#include "Vertex.h"
#include <stdlib.h>

typedef struct Node Node;

Node* alloc_node(void* item){
	Node* nod = (Node*) malloc(sizeof(Node));
	nod->item = item;
	nod->next = NULL;
	return nod;
}
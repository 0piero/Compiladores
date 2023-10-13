#include "graph_adj.h"
#include "Queue.h"
#include "ptr_array.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph_adj Graph_adj;

Graph_adj* alloc_graph_adj(){
	Graph_adj* g = (Graph_adj*) malloc(sizeof(Graph_adj));
	g->vtx = (Vertex**) malloc(sizeof(Vertex*));
	g->num_vtx = 0;
	return g;		
}

void graph_adj_insert_vtx(Graph_adj* g, Vertex* v){
	g->vtx = (Vertex**) realloc(g->vtx, (g->num_vtx+1) * sizeof(Vertex*));
	(g->vtx)[g->num_vtx] = v;
	g->num_vtx++;
}

void graph_adj_make_edge(Graph_adj* g, Vertex* u, Vertex* v){
	Node* nod = (Node*) malloc(sizeof(Node));
	nod->item = (void*) v;
	nod->next = NULL;
	list_append(u->adj_list, nod);
}

void graph_adj_delete_edge(Graph_adj* g, Vertex* u, int idx){
	Node* nod = list_remove(u->adj_list, idx);
}

unsigned int dfs(Graph_adj* g, void* arg){
	int i;
	for(i=0;i<g->num_vtx;i++){
		g->vtx[i]->color = 0;
	}
	for(i=0;i<g->num_vtx;i++){
		Vertex* u = g->vtx[i];
		if (u->color == 0){
			u->data = (void*) list_alloc();
			dfs_visit(g, u, arg);
		}
	}
	return 0;
}

void dfs_visit(Graph_adj* g, Vertex* u, void* arg){
	u->color = 1;
	int* i = (int*) malloc(sizeof(int));
	*i = 0;
	List* adj_u = u->adj_list;
	Node* hdy = u->adj_list->head;


	while (hdy){
		Vertex* v = (Vertex*) hdy->item;
		*((List*) v->data) = *((List*) u->data);
		Node* nod = alloc_node((void*) i);
		list_append(((List*) v->data), nod);

		dfs_visit(g, v, arg);

		hdy = hdy->next;
		int j = *i;
		i = (int*) malloc(sizeof(int));
		*i = j+1;
	}

	if (u->adj_list->s_list==0){
		Node* head =  ((List*) u->data)->head;
		int siz_code_arr = ((List*) u->data)->s_list;
		int* code_arr = (int*) malloc(siz_code_arr * sizeof(int));
		int i = 0;
		while(head){
			code_arr[i] = *((int*) head->item);
			head = head->next;
			i++;
		}
		ptr_array* code_data = (ptr_array*) malloc(sizeof(ptr_array));
		code_data->arr = (void*) code_arr;
		code_data->size = siz_code_arr;
		Node* nod = alloc_node((void*) code_data);
		list_append((List*) arg, nod);
	}

	u->color = 2;	
}

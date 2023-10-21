#ifndef LIST_H
#define LIST_H

#include "Node.h"

typedef struct List List;
struct List{
	Node* head;
	Node* tail;
	int s_list;
};

Node* list_getittem(List* l, int idx);
Node* list_remove(List* l, int idx);
void list_free(List* l);
void list_append(List* l, Node* nod); /* l->tail->next <- nod*/
unsigned int list_insert(List* l, Node* nod, int idx);
List* list_alloc(void);


#endif

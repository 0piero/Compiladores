#include "Queue.h"
#include "Vertex.h"
#include "Node.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Queue Queue;

void q_enqueue(Queue* q, Node* nod){
	Node *p, *r;
	p = q->top;
	nod->next = NULL;
	if(q_empty(q)){
		q->top = nod;
	}
	else{
		while(p != NULL){
			r = p;
			p = p->next;
		}
		r->next = nod;
	}
	q->s_queue++;
}
/* Queue must not be empty */
Node* q_dequeue(Queue* q){
	q->s_queue--;
	if(q_empty(q)){
		return NULL;
	}
	Node* p = q->top;
	q->top = p->next;
	return p;
}

unsigned int q_empty(Queue* q){
	if(q->top == NULL){
		return 1;
	}
	else {return 0;}
}

Queue* q_alloc(void){
	Queue* q = (Queue*) malloc(sizeof(Queue));
	q->top = NULL;
	q->s_queue = 0;
	return q;
}



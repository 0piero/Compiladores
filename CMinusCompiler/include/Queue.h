#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

typedef struct Queue Queue;
struct Queue{
	int s_queue;
	Node* top;
};

Queue* q_alloc(void);
void q_enqueue(Queue* q, Node* nod);
Node* q_dequeue(Queue* q);
unsigned int q_empty(Queue* q);

#endif

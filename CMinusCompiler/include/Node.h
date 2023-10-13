#ifndef NODE_H
#define NODE_H

typedef struct Node Node;
struct Node{
        void* item;
        Node* next;
};

Node* alloc_node(void* item);

#endif

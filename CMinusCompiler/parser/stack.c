#include "stack.h"
#include <stdlib.h>

stack* stack_alloc(){
	stack* s = (stack*) malloc(sizeof(stack));
	s->top = NULL;
	return s;
}
stack_node* stack_pop(stack* s){
	if (s->top == NULL){return NULL;}

	stack_node* ret = s->top;
	s->top = s->top->prev;
	return ret;

}
void stack_push(stack* s, stack_node* nod){
	if (s->top == NULL){
		s->top = nod;
		nod->prev = NULL;
		return ;
	}
	stack_node* top = s->top;
	s->top = nod;
	nod->prev = top;
}

stack_node* stack_alloc_node(void){
	stack_node* nod = (stack_node*) malloc(sizeof(stack_node));
	nod->prev = NULL;
	return nod;
}
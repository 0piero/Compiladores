#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Node.h"

typedef struct List List;

Node* list_getittem(List* l, int idx){
	int i;
	Node* p = l->head;
	for(i=0;i<idx;i++){
		p = p->next;
	}
	return p;
}
Node* list_remove(List* l, int idx){

	if(idx==0){
		Node* p = l->head;
		l->head = p->next;
		if(idx==l->s_list-1){
			l->tail = p->next;
		}
		l->s_list--;
		return p;
	}
	int i;
	Node* p = l->head;
	Node* q = p->next;
	for(i=0;i<idx-1;i++){
		p = p->next;
		q = q->next;
	}
	if(idx==l->s_list-1){
		l->tail = p;
	}
	p->next = q->next;
	l->s_list--;
	return q;
}

unsigned int list_insert(List* l, Node* nod, int idx){
	/*
	idx in {0,1,...,s_list - 1}: inserts into list[idx] and shifts right all further items;
	idx=s_list: appends to the list;
	*/
	if(idx==l->s_list){
		l->tail = nod;
	}
	if(idx==0){
		nod->next = l->head;
		l->head = nod;
	}
	else{
		int i;
		Node* p = l->head; Node* q = p->next;
		for(i=0;i<idx-1;i++){
			p = p->next;
			q = q->next;
		}
		nod->next = q;
		p->next = nod;
	}
	l->s_list++;
	return 0;
}

List* list_alloc(void){
	List* l = (List*) malloc(sizeof(List));
	l->s_list = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}
void list_append(List* l, Node* nod){
	if(l->s_list == 0){
		l->tail = nod;
		l->head = nod;
	}
	else{		
		nod->next = NULL;
		l->tail->next = nod;
		l->tail = nod;
	}
	l->s_list++;
}
void list_free(List* l){
	Node* hdy = l->head;
	while(hdy){
		Node* to_fr = hdy;
		hdy = hdy->next;
		free(to_fr);
	}
}
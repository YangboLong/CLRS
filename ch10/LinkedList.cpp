#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList(){
	head = NULL;
}

LinkedList::~LinkedList(){
/*	Item* next;
	while(head != NULL){
		next = head->next;
		delete head;
		head = next;
	}*/
}

Item* LinkedList::ListSearch(int k){
	Item* x;
	x = head;
	while(x != NULL && x->key != k)
		x = x->next;

	return x;
}

void LinkedList::ListInsert(Item& x){
	x.next = head;
	if(head != NULL)
		head->prev = &x;
	head = &x;
	x.prev = NULL;
}

void LinkedList::ListDelete(Item& x){
	if(x.prev != NULL)
		x.prev->next = x.next;
	else
		head = x.next;
	if(x.next != NULL)
		x.next->prev = x.prev;
}
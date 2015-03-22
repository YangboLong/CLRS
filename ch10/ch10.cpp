#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"

int main(){
	Stack S(7);
	//S.pop();
	S.push(15);
	S.push(6);
	int s = S.pop();

	Queue Q(12);
	//Q.Dequeue();
	Q.Enqueue(15);
	Q.Enqueue(6);
	int q = Q.Dequeue();

	LinkedList L;
	Item* l = L.ListSearch(9);
	Item item1 = {1, NULL, NULL};
	L.ListInsert(item1);
	Item item2 = {4, NULL, NULL};
	L.ListInsert(item2);
	Item item3 = {16, NULL, NULL};
	L.ListInsert(item3);
	Item item4 = {9, NULL, NULL};
	L.ListInsert(item4);
	Item item5 = {25, NULL, NULL};
	L.ListInsert(item5);
	L.ListDelete(item2);

	return 0;
}
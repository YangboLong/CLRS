#include <iostream>
#include <cstdlib>
#include "Queue.h"

Queue::Queue(int size){
	length = size;
	head = 0;
	tail = 0;
	items = new int [length];
}

Queue::~Queue(){
	delete [] items;
}

void Queue::Enqueue(int a){
	if((head == 0 && tail == length - 1) || head == tail + 1){
		std::cerr << "overflow" << std::endl;
		exit(EXIT_FAILURE);
	}

	items[tail] = a;
	if(tail == length - 1)
		tail = 0;
	else
		tail++;
}

int Queue::Dequeue(){
	if(head == tail){
		std::cerr << "underflow" << std::endl;
		exit(EXIT_FAILURE);
	}

	int ret;
	ret = items[head];
	if(head == length - 1)
		head = 0;
	else
		head++;

	return ret;
}
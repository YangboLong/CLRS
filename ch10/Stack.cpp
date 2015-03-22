#include "Stack.h"
#include <cstdlib>
#include <iostream>

Stack::Stack(int size){
	len = size;
	top = -1;
	items = new int [len];
}

Stack::~Stack(){
	delete [] items;
}

bool Stack::StackEmpty(){
	if(top == -1)
		return true;
	else
		return false;
}

void Stack::push(int a){
	top++;
	items[top] = a;
}

int Stack::pop(){
	if(StackEmpty()){
		std::cerr << "underflow" << std::endl;
		exit(EXIT_FAILURE);
	}
	else{
		top--;
		return items[top + 1];
	}
}
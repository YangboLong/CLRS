// clrs p233, stack implementation
class Stack{
public:
	Stack(int);
	~Stack();
	bool StackEmpty();
	void push(int);
	int pop();
private:
	int len;
	int top;
	int* items;
};
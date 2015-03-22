// clrs p235, 10.1-4
class Queue{
public:
	Queue(int);
	~Queue();
	void Enqueue(int);
	int Dequeue();
private:
	int head;
	int tail;
	int length;
	int* items;
};
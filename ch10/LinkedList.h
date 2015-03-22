// clrs p237
struct Item{
	int key;
	Item* prev;
	Item* next;
};
class LinkedList{
public:
	LinkedList();
	~LinkedList();
	Item* ListSearch(int);
	void ListInsert(Item&);
	void ListDelete(Item&);
private:
	Item* head;
};
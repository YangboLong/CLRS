
class Node {
public:
	Node() { key = -1; left = NULL; right = NULL; parent = NULL; }
	int GetKey() { return key; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }
	Node* GetParent() { return parent; }
	void SetParent(Node* node) { parent = node; }
	void SetLeft(Node* node) { left = node; }
	void SetRight(Node* node) { right = node; }
private:
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class Tree {
public:
	Tree() { root = NULL; }
	void InorderTreeWalk(Node*);			// clrs p288
	Node* TreeSearch(Node*, int);			// clrs p290
	Node* IterativeTreeSearch(Node*, int);	// clrs p291
	Node* TreeMinimum(Node*);				// clrs p291
	Node* RecursiveTreeMinimum(Node*);
	Node* TreeMaximum(Node*);				// clrs p291
	Node* RecursiveTreeMaximum(Node*);
	Node* TreeSuccessor(Node*);				// clrs p292
	Node* TreePredecessor(Node*);
	void TreeInsert(Tree*, Node*);			// clrs p294
	void Transplant(Tree*, Node*, Node*);	// clrs p296
	void TreeDelete(Tree*, Node*);			// clrs p298
private:
	Node* root;
};
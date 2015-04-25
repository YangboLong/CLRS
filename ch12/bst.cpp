#include <iostream>
#include "bst.h"

// inorder tree transverse
void Tree::InorderTreeWalk(Node* node) {
	if(node != NULL) {
		InorderTreeWalk(node->GetLeft());
		std::cout << node->GetKey() << " ";
		InorderTreeWalk(node->GetRight());
	}
}

Node* Tree::TreeSearch(Node* root, int key) {
	if(root == NULL || key == root->GetKey())
		return root;
	if(key < root->GetKey())
		return TreeSearch(root->GetLeft(), key);
	else
		return TreeSearch(root->GetRight(), key);
}

Node* Tree::IterativeTreeSearch(Node* root, int key) {
	while(root != NULL && key != root->GetKey()) {
		if(key < root->GetKey())
			root = root->GetLeft();
		else
			root = root->GetRight();
	}

	return root;
}

Node* Tree::TreeMinimum(Node* root) {
	while(root->GetLeft() != NULL)
		root = root->GetLeft();

	return root;
}

// clrs p293, 12.2-2
Node* Tree::RecursiveTreeMinimum(Node* root) {
	if(root->GetLeft() == NULL)
		return root;
	else
		return RecursiveTreeMinimum(root->GetLeft());
}

Node* Tree::TreeMaximum(Node* root) {
	while(root->GetRight() != NULL)
		root = root->GetRight();

	return root;
}

// clrs p293, 12.2-2
Node* Tree::RecursiveTreeMaximum(Node* root) {
	if(root->GetRight() == NULL)
		return root;
	else
		return RecursiveTreeMaximum(root->GetRight());
}

Node* Tree::TreeSuccessor(Node* node) {
	if(node->GetRight() != NULL)
		return TreeMinimum(node->GetRight());

	// if the right subtree of node is empty
	Node* parent = node->GetParent();
	// go up the tree from node until we encounter a node that is the left child of its parent
	while(parent != NULL && node == parent->GetRight()) {
		node = parent;
		parent = parent->GetParent();
	}

	return parent;
}

// clrs p293, 12.2-3
Node* Tree::TreePredecessor(Node* node) {
	// if node has a left subtree
	if(node->GetLeft() != NULL)
		return TreeMaximum(node->GetLeft());

	// if the left subtree of node is empty
	Node* parent = node->GetParent();
	// go up the tree from until we encounter a node that is the right child of its parent
	while(parent != NULL && node != parent->GetRight()) {
		node = parent;
		parent = node->GetParent();
	}

	return parent;
}

void Tree::TreeInsert(Tree* tree, Node* node) {
	Node* y = NULL; // trailing pointer
	Node* x = tree->root;
	while(x != NULL) {
		y = x;
		if(node->GetKey() < x->GetKey())
			x = x->GetLeft();
		else
			x = x->GetRight();
	}

	node->SetParent(y);
	if(y == NULL)
		tree->root = node; // tree was empty
	else if(node->GetKey() < y->GetKey())
		y->SetLeft(node);
	else
		y->SetRight(node);
}

// replaces the subtree rooted at node u with the subtree rooted at node v
void Tree::Transplant(Tree* tree, Node* u, Node* v) {
	if(u->GetParent() == NULL)
		tree->root = v;
	else if(u == u->GetParent()->GetLeft())
		u->GetParent()->SetLeft(v);
	else
		u->GetParent()->SetRight(v);
	
	if(v != NULL)
		v->SetParent(u->GetParent());
}

void Tree::TreeDelete(Tree* tree, Node* node) {
	// 1. node has no left child
	if(node->GetLeft() == NULL)
		Transplant(tree, node, node->GetRight());
	// 2. node has no right child
	else if(node->GetRight() == NULL)
		Transplant(tree, node, node->GetLeft());
	// 3. node has both children
	else {
		// find the successor in the right subtree of node
		Node* successor = TreeMinimum(node->GetRight());
		// 3a. successor is not node's right child (from the line below to the end)
		if(successor->GetParent() != node) {
			Transplant(tree, successor, successor->GetRight());
			successor->SetRight(node->GetRight());
			successor->GetRight()->SetParent(successor);
		}
		// 3b. successor is node's right child
		Transplant(tree, node, successor);
		successor->SetLeft(node->GetLeft());
		successor->GetLeft()->SetParent(successor);
	}
}
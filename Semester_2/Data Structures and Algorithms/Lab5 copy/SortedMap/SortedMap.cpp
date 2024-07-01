#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

#include <stdio.h>

//BC=WC=TC=Theta(1)
SortedMap::SortedMap(Relation r) {
	root = NULL;
	rel = r;
	length = 0;
}

//BC = Theta(1) - the root has only one child and the new node is added as the other child
//WC = Theta(n) - the tree is degenerated and the new node is added as at the end of the tree
//TC = O(n)
TValue SortedMap::add(TKey k, TValue v) {
	//TODO - Implementation
	//add the first element
	if (root == NULL) {
		root = new Node;
		root->info.first = k;
		root->info.second = v;
		root->left = NULL;
		root->right = NULL;
		length++;
		return NULL_TVALUE;
	}
	Node* current = root;
	while (current != NULL) {
		if (current->info.first == k) {	// If the key already exists
			TValue oldValue = current->info.second;	// Save the old value
			current->info.second = v;	// Update the value
			return oldValue;	// Return the old value
		}
		if (rel(k, current->info.first)) {	// Ex: rel --> <, k < current->info.first -> the node goes to the left
			if (current->left == NULL) {	// If we have to add the node as a leaf --> the key doesn't exist
				Node* newNode = new Node;	// Create new node
				newNode->info.first = k;	// Set the key
				newNode->info.second = v;	// Set the value
				newNode->left = NULL;	// Set the left child to NULL
				newNode->right = NULL;	// Set the right child to NULL
				current->left = newNode; // Add the new node as the left child
				length++;	// Increase the number of elements
				return NULL_TVALUE;
			}
			else {
				current = current->left;	// Advance in the tree
			}
		}
		else if (rel(current->info.first, k)) {
			if (current->right == NULL) {	// If we have to add the node as a leaf --> the key doesn't exist
				Node* newNode = new Node;	// Create new node
				newNode->info.first = k;	// Set the key
				newNode->info.second = v;	// Set the value
				newNode->left = NULL;	// Set the left child to NULL
				newNode->right = NULL;	// Set the right child to NULL
				current->right = newNode;	// Add the new node as the right child
				length++;	// Increase the number of elements
				return NULL_TVALUE;
			}
			else {
				current = current->right;	// Advance in the tree
			}
		}
	}
	return NULL_TVALUE;
}

//BC = Theta(1) - the root is the node we are looking for
//WC = Theta(n) - the tree is degenerated and the node is the last one
//TC = O(n)
TValue SortedMap::search(TKey k) const {
	Node* current = root;
	while (current != NULL) {
		if (k == current->info.first) {	// If we find the key
			return current->info.second;	// Return the value
		}
		if (rel(k, current->info.first)) {	// Ex: rel --> <, k < current->info.first -> the node might be in the left subtree
			current = current->left;	// Advance in the tree
		}
		else if (rel(current->info.first, k)) {
			current = current->right;	// Advance in the tree
		}
	}
	return NULL_TVALUE;
}


//BC = Theta(1) - the root is the node we are looking for and it has only one child
//WC = Theta(n) - the tree is degenerated and the node is the last one
//TC = O(n)
TValue SortedMap::remove(TKey k) {
	Node* current = root;
	Node* parent = NULL;
	while (current != NULL && current->info.first != k) {	// Search for the node we need to remove
		parent = current;
		if (rel(k, current->info.first)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	if (current == NULL) {	// If the key doesn't exist
		return NULL_TVALUE;
	}
	if (current->left == NULL && current->right == NULL) {	// If the node is a leaf
		if (current == root) {	// If the node is the root
			root = NULL;	// Set the root to NULL
		}
		else {
			if (parent->left == current) {	// If the node is the left child
				parent->left = NULL;	// Set the left child to NULL
			}
			else {
				parent->right = NULL;	// Set the right child to NULL
			}
		}
		TValue oldValue = current->info.second;	// Save the old value
		delete current;	// Delete the node
		length--;	// Decrease the number of elements
		return oldValue;	// Return the old value
	}
	if (current->left == NULL) {	// If the node has only the right child
		if (current == root) {	// If the node is the root
			root = current->right;	// Set the right child as the new root
		}
		else {
			if (parent->left == current) {	// If the node is the left child
				parent->left = current->right;	// Set the right child of the current node as the new left child of the parent
			}
			else {
				parent->right = current->right;	// Set the right child of the current node as the new right child of the parent
			}
		}
		TValue oldValue = current->info.second;	// Save the old value
		delete current;	// Delete the node
		length--;	// Decrease the number of elements
		return oldValue;	// Return the old value
	}
	if (current->right == NULL) {	// If the node has only the left child
		if (current == root) {	// If the node is the root
			root = current->left;	// Set the left child as the new root
		}
		else {
			if (parent->left == current) {	// If the node is the left child
				parent->left = current->left;	// Set the left child of the current node as the new left child of the parent
			}
			else {
				parent->right = current->left;	// Set the left child of the current node as the new right child of the parent
			}
		}
		TValue oldValue = current->info.second;	// Save the old value
		delete current;	// Delete the node
		length--;	// Decrease the number of elements
		return oldValue;	// Return the old value
	}

	
	// If the node has both children, we need to find the inorder successor
	Node* successor = current->right;	// Initialize the successor as the right child
	Node* parentSuccessor = current;	//save the parent of the successor
	while (successor->left != NULL) {	// Find the leftmost node in the right subtree
		parentSuccessor = successor;
		successor = successor->left;
	}
	current->info.first = successor->info.first;	// Update the key
	current->info.second = successor->info.second;	// Update the value
	if (parentSuccessor->left == successor) {	// If the successor is the left child
		parentSuccessor->left = successor->right;	// Set the right child of the successor as the new left child of the parent
	}
	else {
		parentSuccessor->right = successor->right;	// Set the right child of the successor as the new right child of the parent
	}
	TValue oldValue = successor->info.second;	// Save the old value
	delete successor;	// Delete the successor
	length--;	// Decrease the number of elements
	return oldValue;	// Return the old value
}

//BC=WC=TC=Theta(1)
int SortedMap::size() const {
	return length;
}

//BC=WC=Theta(1)
bool SortedMap::isEmpty() const {
	return length == 0;
}

//BC=Theta(1) -> the root has no left child
//WC=Theta(n) -> the tree is degenerate
//TC=O(n), n - number of nodes
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

//WC=BC=TC=Theta(n), n = number of nodes
SortedMap::~SortedMap() {
	destroy(root);
	root = NULL;
}

//BC=WC=TC=Theta(n), n = number of nodes
void SortedMap::destroy(Node* node) {
	if (node != NULL) {
		destroy(node->left);
		destroy(node->right);
		delete node;
	}
}

//BC=WC=TC=Theta(n), number of elements in the map
//Since the map is sorted by keys and not values, we have to search through the map to get the range of values
int SortedMap::getValueRange() const {
	if (size() == 0)
		return -1;
	SMIterator it = this->iterator();
	int min = INT_MAX, max = INT_MIN;	//initialize the value range ends
	while (it.valid())
	{
		int val = it.getCurrent().second;	//the value from the key-value pair of the TElem pair
		if (val < min)	//update minimum
			min = val;
		if (val > max)	//update maximum
			max = val;
		it.next();	//go to the next element
	}
	return max - min;	//compute and return the value range
}
#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;


//BC=Theta(1) -> the root has no left child
//WC=Theta(n) -> the tree is degenerate
//TC=O(n), n - number of nodes
SMIterator::SMIterator(const SortedMap& m) : map(m){
	current = map.root;
	stack = new SortedMap::Node * [100];
	stackSize = 0;
	nrElem = 0;
	stackCapacity = 100;
	while (current != NULL) {
		nrElem++;
		push(current);
		current = current->left;
	}
	current = top();
}

//BC=Theta(1) -> the root has no left child
//WC=Theta(n) -> the tree is degenerate
//TC=O(n)
void SMIterator::first(){
	current = map.root; //set the current node to the root
	stackSize = 0;	//empty stack
	nrElem = 0;
	while (current != NULL) {	//while the current node is not null
		push(current);	//push it to the stack
		nrElem++;
		current = current->left;	//set the current node its left child
	}
	current = top();	//select the first node (the leftmost leaf)
}


//BC=Theta(1) -> the current node has no right child
//WC=Theta(n) -> the tree is degenerate and it has only right children
//TC=O(n)
void SMIterator::next(){
	if (!valid()) {
		throw exception();
	}
	current = top(); //VISIT THE CURRENT NODE
	SortedMap::Node* temp = current;
	pop();	//pop a node and visit it
	//add the right child of the popped node to the stack
	if (temp!=NULL && temp->right != NULL) {
		temp = temp->right;	//set the current node to the right child of the popped node 
		//push the right child and all its left descendants onto the stack
		while (temp != NULL) {
			nrElem++;
			push(temp);
			temp = temp->left;
		}
	}
}

//BC=WC=TC=Theta(1)
bool SMIterator::valid() const{
	return nrElem <= map.size();
}

//BC=WC=TC=Theta(1)
TElem SMIterator::getCurrent() const{
	if (valid()) {
		return current->info;
	}
	throw exception();
}

//BC=Theta(1) -> no resize
//WC=Theta(n) -> resize, n-number of elements in the stack
//TC=Theta(1) amortized
void SMIterator::push(SortedMap::Node* node) {
	if (stackSize == stackCapacity) {
		resizeStack();
	}
	stack[stackSize] = node;
	stackSize++;
}

//BC=WC=TC=Theta(1)
void SMIterator::pop() {
	stackSize--;
}

//BC=WC=TC=Theta(1)
SortedMap::Node* SMIterator::top() {
	return stack[stackSize];
}

//BC=WC=TC=Theta(n), n-number of elements in the stack
void SMIterator::resizeStack() {
	SortedMap::Node** newStack = new SortedMap::Node * [stackCapacity * 2];
	for (int i = 0; i < stackSize; i++) {
		newStack[i] = stack[i];
	}
	delete[] stack;
	stack = newStack;
	stackCapacity *= 2;
}


#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	capacity = 2;
	sizeOfList = 0;
	head = -1;
	firstEmpty = 0;
	relation = r;
	elements = new TComp[capacity];
	next = new int[capacity];
	for (int i = 0; i < capacity - 1; i++) {
		next[i] = i + 1;
	}
	next[capacity - 1] = -1;
}

//BC=WC=TC=Theta(1)
int SortedIteratedList::size() const {
	return sizeOfList;
}

//BC=WC=TC=Theta(1)
bool SortedIteratedList::isEmpty() const {
	return sizeOfList == 0;
}

//BC=WC=TC=Theta(1)
ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}

//BC=WC=TC=Theta(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (!poz.valid())
		throw exception();
	return poz.getCurrent();
}

//BC = Theta(1) --> the element is removed from the first position
//WC = Theta(sizeOfList) --> the element is removed from the last position
//TC = O(sizeOfList)
TComp SortedIteratedList::remove(ListIterator& poz) {
	if (!poz.valid())
		throw exception();
	
	TComp removedElement = poz.getCurrent();
	int previous = -1;

	// Find the previous element and update its next pointer
	int current = head;
	while (current != -1 && elements[current] != removedElement) {
		previous = current;
		current = next[current];
	}

	if (current == head) {
		// If removing the head, update the head pointer
		head = next[head];
	}
	else {
		// Update the next pointer of the previous element
		next[previous] = next[current];
	}

	//UPDATE THE ITERATOR
	poz.current = next[current];

	// Add the removed position as the head of the free list
	next[current] = firstEmpty;
	firstEmpty = current;
	sizeOfList--;

	return removedElement;
}

//BC = Theta(1) --> the element is found in the first position
//WC = Theta(sizeOfList) --> the element is found on the last position or it is not in the list
//TC = O(sizeOfList)
ListIterator SortedIteratedList::search(TComp e) const{
	//parse using the iterator
	ListIterator it = first();
	while (it.valid()) {
		if (it.getCurrent() == e) {
			return it;
		}
		it.next();
	}
	return it;
}


//BC = Theta(1) --> the element must be inserted in the first position
//WC = Theta(sizeOfList) --> the element must be inserted last (bc of the search to insert according to relation)
//TC = O(n)
void SortedIteratedList::add(TComp e) {
	if (sizeOfList == capacity) {
		resize();
	}
	
	//the element needs to be inserted as the head
	if (head == -1 || relation(e, elements[head]))
	{
		int newPos = firstEmpty;
		elements[newPos] = e;
		firstEmpty = next[firstEmpty];
		next[newPos] = head;
		head = newPos;
		sizeOfList++;
	}
	
	//insert the new element between prev and current
	else
	{
		int current = head;
		int prev = -1;
		while (current != -1 && relation(elements[current], e)) {
			prev = current;
			current = next[current];
		}

		int newPos = firstEmpty;
		elements[newPos] = e;
		firstEmpty = next[firstEmpty];
		next[newPos] = next[prev];
		next[prev] = newPos;
		sizeOfList++;
	}
}

//BC=WC=TC=Theta(capacity*2)
void SortedIteratedList::resize() {
	TComp* newElements = new TComp[2 * capacity];
	int* newNext = new int[2 * capacity];
	for (int i = 0; i < capacity; i++) {
		newElements[i] = elements[i];
		newNext[i] = next[i];
	}
	for (int i = capacity; i < 2 * capacity - 1; i++) {
		newNext[i] = i + 1;
	}
	newNext[2 * capacity - 1] = -1;
	delete[] elements;
	delete[] next;
	elements = newElements;
	next = newNext;
	firstEmpty = capacity;
	capacity *= 2;
}

SortedIteratedList::~SortedIteratedList() {
	delete[] elements;
	delete[] next;
}


//BC = Theta(sizeOfList) --> we don't have to remove any elements in the list (or only the first element) (assuming the Condition function is performed in Theta(1))
//WC = Theta(sizeOfList^2) --> we have to search and remove all the elements (always removing the last element)
//TC = O(sizeOfList^2)
void SortedIteratedList::filter(Condition cond)
{
	ListIterator it = first();
	//iterate through the list
	while (it.valid())
	{
		TComp elem = it.getCurrent(); //get the current element
		if (!cond(elem)) //if the element doesn't respect the condition
		{
			remove(it);
			//after the remove, the iterator will point to the next element, so we don't advance it
		}
		//
		else //advance iterator
		{
			it.next();
		}
	}
}
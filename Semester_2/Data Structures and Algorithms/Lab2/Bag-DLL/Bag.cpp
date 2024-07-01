#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	head = nullptr; 
	tail = nullptr; 
	nrElems = 0;
}

//BC=Theta(1), if the element is already in the DLL and it is the head of the DLL
//WC=Theta(nrElems), if the element is not in the DLL / is the last element in the DLL
//TC=O(nrElems)
void Bag::add(TElem elem) {
	//If the DLL is empty
	if (head == nullptr) {
		head = new Node(elem); //allocate memory and initialize the new node
		tail = head;	//the new node is both the head and the tail of the DLL
		nrElems++;
	}
	else {
		Node* current = head; //start from the head of the DLL
		while (current != nullptr) { //iterate through the DLL
			if (current->value == elem) { //if the element is already in the DLL
				current->frequency++; //increment the frequency of the element
				nrElems++; //increment the number of elements in the DLL
				return; //exit the function
			}
			current = current->next; //move to the next node
		}
		//if the element is not in the DLL
		nrElems++; //increment the number of elements in the DLL
		Node* newNode = new Node(elem); //allocate memory and initialize the new node
		tail->next = newNode; //the current tail points to the new node
		newNode->prev = tail; //the new node points to the current tail
		tail = newNode; //the new node is the tail
	}
}

//BC = Theta(1) , if the element is found in the head of the list
//WC = Theta(nrElems), if the element is on the last position in the list / is not in the list (and the list is not empty)
//TC = O(nrElems)
bool Bag::remove(TElem elem) {
	if (head == nullptr) //if the DLL is empty
		return false; //the element is not in the DLL
	Node* current = head; //start from the head of the DLL
	while (current != nullptr) { //iterate through the DLL
		if (current->value == elem) { //if the element is found
			if (current->frequency > 1) { //if the element has a frequency greater than 1
				current->frequency--; //decrement the frequency of the element
				nrElems--; //decrement the number of elements in the DLL
				return true; //the element was removed
			}
			else { //if the element has a frequency of 1
				if (current == head) { //removeFirst()
					head = head->next; //the head points to the next node
					if (head != nullptr) //if the DLL is not empty
						head->prev = nullptr; //the new head does not point to any node
				}
				else if (current == tail) { //removeLast()
					tail = tail->prev; //the tail points to the previous node
					tail->next = nullptr; //the new tail does not point to any node
				}
				else {
					Node* prv = current->prev;
					Node* nxt = current->next;
					prv->next = nxt; //the previous node points to the next node
					nxt->prev = prv; //the next node points to the previous node
				}
				delete current; //deallocate memory
				nrElems--; //decrement the number of elements in the DLL
				return true; //the element was removed
			}
		}
		current = current->next; //move to the next node
	}
	return false; 
}

//BC = Theta(1), if the element is found in the head of the list
//WC = Theta(nrElems), if the element is on the last position in the list / is not in the list (and the list is not empty)
//TC = O(nrElems)
bool Bag::search(TElem elem) const {
	if (head == nullptr)
		return false;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->value == elem)
			return true;
		current = current->next;
	}
	return false; 
}

//BC = Theta(1), if the element is found in the head of the list
//WC = Theta(nrElems), if the element is on the last position in the list / is not in the list (and the list is not empty)
//TC = O(nrElems)
int Bag::nrOccurrences(TElem elem) const {
	if (head == nullptr)
		return 0;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->value == elem)
			return current->frequency;
		current = current->next;
	}
	return 0; 
}

//BC=WC=TC=Theta(1)
int Bag::size() const {
	return nrElems;
}

//BC=WC=TC=Theta(1)
bool Bag::isEmpty() const {
	return nrElems == 0;
}

//BC=WC=TC=Theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

//BC = WC = TC = Theta(nrElems) nrElems = nr of distinct elements
int Bag::elementsWithThisFrequency(int freq) const
{
	if (freq <= 0)
		throw exception("Invalid frequency");
	Node* current = head;
	int count = 0;
	while (current != nullptr)
	{
		if (current->frequency == freq)
			count++;
		current = current->next;
	}
	return count;
}

//BC=WC=TC=Theta(nrElems)
Bag::~Bag() {
	Node* current = head;
	while (current != nullptr)
	{
		Node* temp = current; // save the pointer to the element to be deleted
		current = current->next; //advance in the list
		delete temp; //delete the element
	}
	head = nullptr; //clear head
	tail = nullptr; //clear tail
	nrElems = 0;
}


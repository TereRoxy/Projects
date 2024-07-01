#pragma once
//DO NOT INCLUDE BAGITERATOR

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	//ADT Bag - using a doubly-linked-list with(element, frequency) pairs
	
	struct Node {
		TElem value;
		int frequency;
		Node* next;
		Node* prev;

		Node(TElem& value, int freq = 1, Node* n = nullptr, Node* p = nullptr) : value(value), frequency(freq), next(n), prev(n) {}
	};
	
	//head and tail pointers
	Node* head;
	Node* tail;
	//size of the bag
	int nrElems;

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//returns the number of elements that appear frequency times
	//throws an exception if frequency is negative or zero
	int elementsWithThisFrequency(int freqy) const;

	//destructor
	~Bag();
};
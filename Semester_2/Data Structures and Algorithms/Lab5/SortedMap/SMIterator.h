#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	struct SortedMap::Node* current;
	//simulate a stack on a dynamic array for the inorder traversal
	struct SortedMap::Node** stack;
	int stackSize;
	int stackCapacity;
	void push(struct SortedMap::Node* node);
	void pop();
	struct SortedMap::Node* top();
	void resizeStack();
	int nrElem;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};


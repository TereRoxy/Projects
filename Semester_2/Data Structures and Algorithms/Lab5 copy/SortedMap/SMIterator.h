#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);

	//save the traversal order in an array
	int current;
	int nrElem;
	TElem* nodes;
	void buildTraversalOrder(SortedMap::Node* curr);

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
	
	~SMIterator();
};


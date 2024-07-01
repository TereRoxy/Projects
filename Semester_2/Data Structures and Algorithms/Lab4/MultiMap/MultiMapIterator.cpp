#include "MultiMapIterator.h"
#include "MultiMap.h"

//BC=Theta(1) --> there is an element in the first position in the hash table
//WC=Theta(tableSize) --> the first element is in the last position in the hash table
//TC=O(tableSize)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->currentBucketIndex = 0;
	while (currentBucketIndex < col.tableSize && col.hashTable[currentBucketIndex] == nullptr) {
		currentBucketIndex++;
	}
	if (currentBucketIndex < col.tableSize) {
		currentNode = col.hashTable[currentBucketIndex];
		currentElementIndex = 0;
	}
	else {
		currentNode = nullptr;
		currentElementIndex = 0;
	}
}

//BC=WC=TC=Theta(1)
TElem MultiMapIterator::getCurrent() const{
	if (valid()) {
		return std::make_pair(currentNode->key, currentNode->values[currentElementIndex]);
	}
	else {
		throw::exception();
	}
}

//BC=WC=TC=Theta(1)
bool MultiMapIterator::valid() const {
	return currentBucketIndex < col.tableSize&&
		currentNode != nullptr &&
		currentElementIndex < currentNode->values.size();
}

//BC=Theta(1) --> the element is in the first position in the hash table
//WC=Theta(tableSize) --> the element is in the last position in the hash table
//TC=O(tableSize)
void MultiMapIterator::next() {
	if (valid()) {
		currentElementIndex++;
		if (currentElementIndex >= currentNode->values.size()) {
			// Move to the next node in the same bucket
			currentNode = currentNode->next;
			currentElementIndex = 0;

			// If currentNode is nullptr, move to the next non-empty bucket
			while (currentNode == nullptr && currentBucketIndex < col.tableSize - 1) {
				currentBucketIndex++;
				currentNode = col.hashTable[currentBucketIndex];
			}
		}
	}
	else
		throw::exception();
}

//BC=Theta(1)
//WC=Theta(tableSize)
//TC=O(tableSize)
void MultiMapIterator::first() {
	currentBucketIndex = 0;
	while (currentBucketIndex < col.tableSize) {
		currentNode = col.hashTable[currentBucketIndex];
		if (currentNode != nullptr) {
			currentElementIndex = 0;
			break;
		}
		currentBucketIndex++;
	}
}


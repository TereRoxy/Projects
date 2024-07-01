#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0)
	{
		throw std::exception("Invalid capacity");
	}
	else
	{
		this->capacity = capacity;
		this->mapSize = 0;
		this->elements = new TElem[this->capacity];	
	}
}
//BC: Theta(1), WC: Theta(1), TC: Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
//BC = WC = TC: Theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	//the map is full
	if (this->mapSize == this->capacity){
		throw exception("Map is full");
	}
	int count = 0;
	int index = 0;
	while (count < 2 && index < this->mapSize){
		if (this->elements[index].first == c){
			count++;
		}
		index++;
	}
	// if we already have 2 occurences
	if (count == 2) {
		return false;
	}
	//else we add the element
	//this->elements[this->mapSize] = pair<TKey, TValue>(c, v);
	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;	
	this->mapSize++;
	return true;
}
//BC : Theta(1) - when the frist two keys from the map are equal to c 
//WC: Theta(mapSize)-when the key c appears only once or zero times in the map
//TC: O(mapSize)

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair result;
	result.first = NULL_TVALUE;
	result.second = NULL_TVALUE;
	int timesFound = 0;
	int index = 0;
	while (timesFound < 2 && index < this->mapSize) {
		if (this->elements[index].first == c) {
			if (timesFound == 0) {
				result.first = this->elements[index].second;
			}
			else {
				result.second = this->elements[index].second;
			}
			timesFound++;
		}
		index++;
	}
	return result;
}
// BC: Theta(1)-when the first two keys from the map are equal to c
//WC: Theta(mapSize)- when the key c appears only once or zero times in the map
//TC: O(mapSize)

bool FixedCapBiMap::remove(TKey c, TValue v){
	int index = 0;
	while (index < this->mapSize) {
		if (this->elements[index].first == c && this->elements[index].second == v) {
			this->elements[index] = this->elements[this->mapSize - 1];
			this->mapSize--;
			return true;
		}
		index++;
	}
	return false;
}
//BC: Theta(1)-when the pair with want to remove is on the first position
//WC:Theta(mapSize)-when the pair is not in the array or it is on the last position
//TC:O(mapSize)

int FixedCapBiMap::size() const {	
	return mapSize;
}
//BC = WC = TC : Theta(1)

bool FixedCapBiMap::isEmpty() const{
	return mapSize == 0;
}
//BC = WC = TC : Theta(1)

bool FixedCapBiMap::isFull() const {
	return mapSize == capacity;
}
//BC = WC = TC : Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
//BC = WC = TC : Theta(1)

int FixedCapBiMap::countUniqueKeys() const{
	int count = 0;
	for (int i = 0; i < this->mapSize; i++)
	{
		int key = this->elements[i].first; //the key to be searched for
		ValuePair found = search(key);
		if (found.second == NULL_TVALUE) //if it didn't find the key a second time
			count++;
	}
	return count;
}

// BC = WC = TC: Theta(mapSize * mapSize) 


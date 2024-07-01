#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//BC=WC=TC=Theta(1)
MultiMap::MultiMap() {
    tableSize = INITIAL_TABLE_SIZE; //initial table size is a constant
    elementsCount = 0;
    hashTable = new Node * [tableSize];
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = nullptr;
	}
}

//BC=Theta(1), collisions are rare
//WC=Theta(elementsCount) --> all added elements result in a colision
//TC=Theta(1), average, amortized
void MultiMap::add(TKey c, TValue v) {
    int index = hash(c);
    
	//if we need to resize the hash table --> it has reached the load factor threshold
    if (elementsCount >= LOAD_FACTOR_THRESHOLD * tableSize) {
        resizeHashTable();
        //rehash the index value
        index = hash(c);
    }
    //select the row in the has table
    Node* current = hashTable[index];

    //search for the key in the linked list
    while (current != nullptr && current->key != c) {
        current = current->next;
    }

    //if the key doesn't exist
    if (current == nullptr) {
        current = new Node(c, v); //create new node
        
        current->next = hashTable[index]; //insert in the linked list
        hashTable[index] = current;
    }
    //add the value to the associated values of the key
    else
    {
        current->values.push_back(v);
    }
    elementsCount++;
}

//BC=Theta(1)
//WC=Theta(elementsCount + NValues) --> many collisions and the TKey, TValue pair is not in the MultiMap, NValues, number of values associated to a key
//TC=Theta(1), average
bool MultiMap::remove(TKey c, TValue v) {
    int index = hash(c);
    Node* current = hashTable[index];
    Node* prev = nullptr;

	while (current != nullptr && current->key != c) {
		prev = current;
		current = current->next;
	}

    if (current != nullptr)
    {
        // If the value is found
        auto it = current->values.begin();
        while (it != current->values.end()) {
            if (*it == v) {
                it = current->values.erase(it);
                elementsCount--;
                // If there are no values associated with the key, remove the node from the linked list
                if (current->values.empty()) {
                    if (prev != nullptr)
                        prev->next = current->next;
                    else
                        hashTable[index] = current->next;
                    delete current;
                }
                return true;
            }
            else {
                ++it;
            }
        }
    }
    
	return  false; //key or value not found
}

//WC = Theta(elementsCount), BC = Theta(1), TC = Theta(1) on average, amortized
vector<TValue> MultiMap::search(TKey c) const {
    int index = hash(c);
	//select the row in the hash table
    Node* current = hashTable[index];

	//search for the key in the linked list
    while (current != nullptr && current->key != c) {
        current = current->next;
    }

    //if the key is found
    if (current != nullptr) {
        return current->values;
    }
	return vector<TValue>();
}

//BC=WC=TC=Theta(1)
int MultiMap::size() const {
	return elementsCount;
}

//BC=WC=TC=Theta(1)
bool MultiMap::isEmpty() const {
	return elementsCount == 0;
}

//BC=Theta(1)
//WC=Theta(tableSize) - the number of elements in the hash table
//TC=O(tableSize)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//BC=WC=TC=Theta(tableSize)
MultiMap::~MultiMap() {
    for (int i = 0; i < tableSize; ++i) {
        //for each value in the hash table
        Node* current = hashTable[i];
		// go through the linked list
        while (current != nullptr) {
            Node* temp = current;
            //advance to the next node
            current = current->next;
			//delete the current node
            delete temp;
        }
    }
    delete[] hashTable;
}


//BC=WC=TC=Theta(tableSize)
void MultiMap::resizeHashTable() {
    int newTableSize = 2 * tableSize + 1; // New size is the next prime number after doubling
    Node** newTable = new Node * [newTableSize]();

	int oldTableSize = tableSize;
	tableSize = newTableSize;

    for (int i = 0; i < oldTableSize; ++i) {
		//for each value in the old hash table
        Node* current = hashTable[i];
        // go through the linked list
        while (current != nullptr) {
            Node* next = current->next;
            //rehash the key
            int newIndex = hash(current->key);
			//insert in the new table at the new index, at the head of the linked list
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            //advance in the linked list
            current = next;
        }
    }

    delete[] hashTable;
    hashTable = newTable;
    tableSize = newTableSize;
}


//BC = Theta(elementsCount), all the elements hash to different indexes
//WC = Theta(elementsCount^2), all the values associated to the keys cause collisions
//TC = Theta(elementsCount), average, amortized
//Extra space complexity -> Theta(uniqueElements), unique values associated to the keys in the hash table
TValue MultiMap::mostFrequent() const
{   
	if (isEmpty())
		return NULL_TVALUE;

	TValue mostFrequentValue = NULL_TVALUE;
    int maxFrequency = 0;
    
	MultiMap freqMap;
	MultiMapIterator it = iterator();
	it.first();

	//go through the initial map => Theta(elementsCount) iterations
    while (it.valid())
    {
		TElem pair = it.getCurrent(); //get the current key-value pair in my initial map
		TValue val = pair.second;   //retrieve the value
		int index = freqMap.hash(val);  //use the value as key in map of frequencies

		//search for the index in the freqMap
        Node* current = freqMap.hashTable[index];

        //search for the key in the linked list of the freqMap
        while (current != nullptr && current->key != val) {
            current = current->next;
        }

		//if the key is found, the frequency will be found in the first position of the values vector (we only need a map, not a multimap)
        if (current != nullptr) {
            current->values[0]++; //increase the frequency
			if (current->values[0] > maxFrequency) //update max frequency and TValue element
			{
				maxFrequency = current->values[0];
				mostFrequentValue = val;
			}
        }
		//add the value as key in the freqMap
        else
        {
			freqMap.add(val, 1); //add the value with frequency 1
        }
        //advance the iterator
		it.next();
    }
	return mostFrequentValue;
}
#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list), current(list.head), count(0) {}

//BC=WC=TC=Theta(1)
void ListIterator::first(){
	current = list.head;
	count = 0;
}

//BC=WC=TC=Theta(1)
void ListIterator::next(){
	if (valid())
	{
		current = list.next[current];
		count++;
	}
	else
		throw exception();
}

//BC=WC=TC=Theta(1)
bool ListIterator::valid() const{
	return current != -1;
}

//BC=WC=TC=Theta(1)
TComp ListIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return list.elements[current];
}



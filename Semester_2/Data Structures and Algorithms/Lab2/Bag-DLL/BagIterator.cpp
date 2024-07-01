#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c), current_it(c.head), current_freq(1) {}

//BC=WC=TC=Theta(1)
void BagIterator::first() {
	current_it = bag.head;
	current_freq = 1;
}

//BC=WC=TC=Theta(1)
void BagIterator::next() {
	if (valid())
	{
		if (current_it->frequency <= current_freq) //if the iterator has reached all the elements of the current value
		{
			current_it = current_it->next;
			current_freq = 1;
		}
		else
			current_freq++;
	}
	else
		throw exception();
}


//BC=WC=TC=Theta(1)
bool BagIterator::valid() const {
	return current_it != nullptr;
}


//BC=WC=TC=Theta(1)
TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception();
	return current_it->value;
}

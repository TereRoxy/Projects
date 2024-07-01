#include <assert.h>
#include <iostream>

#include "SortedIteratedList.h"
#include "ListIterator.h"

#include <exception>
using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIteratedList list = SortedIteratedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator it = list.search(1);
    assert(it.valid());
    assert(it.getCurrent() == 1);
    it.next();
    assert(!it.valid());
    it.first();
    assert(it.valid());
    ListIterator itFirst = list.first();
    assert(itFirst.valid());
    assert(itFirst.getCurrent() == 1);
    assert(list.remove(it) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

bool isEven(TComp elem)
{
    return elem % 2 == 0;
}

void testFilter()
{
    std::cout << "Test Filter\n";
    SortedIteratedList list = SortedIteratedList(relation1);
    for (int i = 0; i < 10; i++)
    {
        list.add(i);
    }
    list.filter(isEven);
    assert(list.size() == 5);
    ListIterator it = list.first();
    int evenCounter = 0;
    while (it.valid())
    {
        assert(it.getCurrent() == evenCounter);
        evenCounter += 2;
        it.next();
    }
}
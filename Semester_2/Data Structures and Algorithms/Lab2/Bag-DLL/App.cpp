#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <assert.h>

using namespace std;

void testElemsWithThisFrequency()
{
	Bag b;
	for (int i = 0; i < 10; i++) {
		b.add(i);
	}
	assert(b.isEmpty() == false);
	assert(b.size() == 10);
	for (int i = -10; i < 20; i++) {
		b.add(i);
	}
	assert(b.isEmpty() == false);
	assert(b.size() == 40);
	for (int i = -100; i < 100; i++) {
		b.add(i);
	}
	assert(b.isEmpty() == false);
	assert(b.size() == 240);
	assert(b.elementsWithThisFrequency(3) == 10);
	assert(b.elementsWithThisFrequency(2) == 20);
	assert(b.elementsWithThisFrequency(1) == 170);
	try {
		b.elementsWithThisFrequency(0);
		assert(false);
	}
	catch(exception) {
		assert(true);
	}
}

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;

	testElemsWithThisFrequency();
	cout << "Extra operation tests over" << endl;
}
#include "ExtendedTest.h"
#include "ShortTest.h"

#include "FixedCapBiMap.h"

#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();
	testCountUniqueKeys();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}



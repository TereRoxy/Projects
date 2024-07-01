
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	testSetElemsOnCol();
	cout << "Test End" << endl;
	system("pause");
}
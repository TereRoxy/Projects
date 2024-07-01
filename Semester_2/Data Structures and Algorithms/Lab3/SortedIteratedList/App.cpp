#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testFilter();
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}
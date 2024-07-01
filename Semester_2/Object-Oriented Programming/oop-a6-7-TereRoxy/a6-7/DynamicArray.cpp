//#include "DynamicArray.h"
//#include <stdexcept>
//
//template <typename T>
//DynamicArray<T>::DynamicArray() : array(nullptr), capacity(0), size(0) {}
//
//template <typename T>
//DynamicArray<T>::~DynamicArray() {
//    delete[] array;
//}
//
//template <typename T>
//DynamicArray<T>::DynamicArray(const DynamicArray& v) {
//	capacity = v.capacity;
//	size = v.size;
//	array = new T[capacity];
//	for (int i = 0; i < size; ++i) {
//		array[i] = v.array[i];
//	}
//}
//
//template <typename T>
//void DynamicArray<T>::append(const T& element) {
//    if (size >= capacity) {
//		resize(2);
//    }
//
//    array[size++] = element;
//}
//
//template <typename T>
//T& DynamicArray<T>::operator[](int index) {
//    if (index < 0 || index >= size) {
//        throw std::out_of_range("Index out of range");
//    }
//    return array[index];
//}
//
//template <typename T>
//int DynamicArray<T>::getSize() const {
//    return size;
//}
//
//template <typename T>
//void DynamicArray<T>::resize(int factor) {
//	if (factor <= 0) {
//		throw std::invalid_argument("Factor must be positive");
//	}
//	if (factor == 1) {
//		return;
//	}
//    
//	if (capacity == 0) {
//		capacity = 1;
//	}
//    
//	int newCapacity = capacity * factor;
//	T* newArray = new T[newCapacity];
//
//	for (int i = 0; i < size; ++i) {
//		newArray[i] = array[i];
//	}
//
//	delete[] array;
//	array = newArray;
//	capacity = newCapacity;
//}
//
//template <typename T>
//void DynamicArray<T>::remove(int index) {
//	if (index < 0 || index >= size) {
//		throw std::out_of_range("Index out of range");
//	}
//
//	for (int i = index; i < size - 1; ++i) {
//		array[i] = array[i + 1];
//	}
//
//	--size;
//}
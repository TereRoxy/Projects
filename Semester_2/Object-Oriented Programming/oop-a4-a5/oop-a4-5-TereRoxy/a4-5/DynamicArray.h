#pragma once
#include <stdexcept>

template <typename T>

class DynamicArray {
private:
    T* array;
    int capacity;
    int size;

public:
    //Constructor
    DynamicArray() : array(nullptr), capacity(0), size(0) {};
    //Destructor
    ~DynamicArray() { delete[] array; };
    //Copy constructor
	/*DynamicArray(const DynamicArray& v) {
        capacity = v.capacity;
        size = v.size;
        array = new T[capacity];
        for (int i = 0; i < size; ++i) {
            array[i] = v.array[i];
        }
    };*/
    void append(const T& element) {
        if (size >= capacity) {
            resize(2);
        }

        array[size++] = element;
    };
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    };
    int getSize() const {
        return size;
    };
    void resize(int factor) {
        //if (factor <= 0) {
        //    throw std::invalid_argument("Factor must be positive");
        //}
        //if (factor == 1) {
        //    return;
        //}

        if (capacity == 0) {
            capacity = 1;
        }

        int newCapacity = capacity * factor;
        T* newArray = new T[newCapacity];

        for (int i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }

        delete[] array;
        array = newArray;
        capacity = newCapacity;
    };
	void remove(int index)
    {
        //if (index < 0 || index >= size) {
        //    throw std::out_of_range("Index out of range");
        //}

        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }

        --size;
    };
    //Copy dynamic array
	DynamicArray(const DynamicArray& v) {
		capacity = v.capacity;
		size = v.size;
		array = new T[capacity];
		for (int i = 0; i < size; ++i) {
			array[i] = v.array[i];
		}
	};
};

//#pragma once
//
//typedef void* Telem;
//
//class DynamicArray {
//private:
//	Telem* array;
//	int capacity;
//	int size;
//public:
//	//Constructor
//	DynamicArray();
//	//Destructor
//	~DynamicArray();
//	//Copy constructor
//	DynamicArray(const DynamicArray& v);
//	//Append an element to the array
//	void append(const Telem& element);
//	//Get the element from the array by index
//	Telem& operator[](int index);
//	//Get the size of the array
//	int getSize() const;
//	//Resize the array
//	void resize(int factor);
//	//Remove an element from the array by index
//	void remove(int index);
//};
#pragma once
#include "Estate.h"

typedef void* TElem;
typedef void (*DestroyFunctionType)(TElem);

typedef struct
{
	TElem* elems;
	int size;
	int capacity;
	DestroyFunctionType destroyFct;
}DynamicArray;

DynamicArray* createDynamicArray(int capacity, DestroyFunctionType destroyFct);
void destroy(DynamicArray* arr);
int resize(DynamicArray* arr);
int add(DynamicArray* arr, TElem t);
int insertAtPosition(DynamicArray* arr, TElem t, int index);
int delete_elem(DynamicArray* arr, int index);
int update(DynamicArray* arr, TElem t, int index);
TElem get_elem(DynamicArray* arr, int index);
int get_size(DynamicArray* arr);
void print_array(DynamicArray* arr);
#include "DynamicArray.h"
#include <stdlib.h>

 DynamicArray* createDynamicArray(int capacity, DestroyFunctionType destroyFct)
{
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (arr == NULL)
		return NULL;
	arr->capacity = capacity;
	arr->size = 0;
	arr->elems = (TElem*)malloc(capacity * sizeof(TElem));
	if (arr->elems == NULL)
	{
		free(arr);
		return NULL;
	}
	arr->destroyFct = destroyFct;
	return arr;
}


void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// considering that the dynamic array takes responsibility of all the elements, it will have to deallocate the memory for these
	for (int i = 0; i < arr->size; i++)
		arr->destroyFct(arr->elems[i]);

	// free the space allocated for the elements
	free(arr->elems);
	arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
}

int resize(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	arr->capacity *= 2;
	TElem* aux = (TElem*)realloc(arr->elems, arr->capacity * sizeof(TElem));
	if (aux == NULL)
		return 0;
	arr->elems = aux;
	return 1;
}

int add(DynamicArray* arr, TElem t)
{
	if (arr == NULL)
		return 0;
	if (arr->size == arr->capacity)
		resize(arr);
	arr->elems[arr->size++] = t;
	return 1;
}

int insertAtPosition(DynamicArray* arr, TElem t, int index)
{
	if (arr == NULL)
		return 0;
	if (index < 0 || index > arr->size)
		return 0;
	if (arr->size == arr->capacity)
		resize(arr);
	for (int i = arr->size; i > index; i--)
		arr->elems[i] = arr->elems[i - 1];
	arr->elems[index] = t;
	arr->size++;
	return 1;
}

int delete_elem(DynamicArray* arr, int index)
{
	if (arr == NULL)
		return 0;
	if (index < 0 || index >= arr->size)
		return 0;
	
	arr->destroyFct(arr->elems[index]);

	for (int i = index; i < arr->size - 1; i++)
		arr->elems[i] = arr->elems[i + 1];
	
	//arr->elems[index] = arr->elems[arr->size - 1];

	arr->size--;
	return 1;
}

int update(DynamicArray* arr, TElem t, int index)
{
	if (arr == NULL)
		return 0;
	if (index < 0 || index >= arr->size)
		return 0;

	arr->destroyFct(arr->elems[index]);
	arr->elems[index] = t;
	return 1;
}

TElem get_elem(DynamicArray* arr, int index)
{
	if (arr == NULL)
		return;
	if (index < 0 || index >= arr->size)
		return;
	return arr->elems[index];
}

int get_size(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->size;
}

void print_array(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	for (int i = 0; i < arr->size; i++)
	{
		Estate* estate = arr->elems[i];
		printEstate(estate);
	}
}
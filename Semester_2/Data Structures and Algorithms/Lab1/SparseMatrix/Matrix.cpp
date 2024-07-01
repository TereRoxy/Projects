#include "Matrix.h"
#include <exception>
using namespace std;

//BC=WC=TC=Theta(nrCols) ~ number of columns in the matrix
Matrix::Matrix(int nrLines, int nrCols) {
	   
	nrLin = nrLines; //set the number of lines
	nrCol = nrCols; //set the number of columns
	cols = new int[nrCols + 1]; //+1 buffer column
	for (int i = 0; i <= nrCols; i++) //initialize the compressed columns structure
		cols[i] = 0;
	values = nullptr;	//the matrix is empty
	lines = nullptr;	//the matrix is empty
	capacity = 0;	//initialize the capacity of the sparse matrix (capacity of the dynamic arrays of values int the matrix and lines)
	size = 0;	//initialize the size of the sparse matrix (number of non-zero elements in the matrix)
}


//BC=WC=TC=Theta(1)
int Matrix::nrLines() const {
	return nrLin; //getter
}

//BC=WC=TC=Theta(1)
int Matrix::nrColumns() const {
	return nrCol; //getter
}

//BC = Theta(1) --> the element is found in the middle of column j (it is found in the first iteration of the search)
//WC = Theta(log nrNonZeroElements) --> nrNonZeroElements = number of non-zero elements in a column j (last searched element or null element)
//TC = O(log nrNonZeroElements)
TElem Matrix::element(int i, int j) const {
	// Check if the provided indices are within bounds
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw std::exception("Index out of bounds");

	// Define the start and end indices for binary search in the column 'j'
	int start = cols[j];
	int end = cols[j + 1] - 1;

	// Perform binary search within the column to find the element
	while (start <= end) {
		int mid = start + (end - start) / 2;
		if (lines[mid] == i)
			// If the current line index equals the requested line 'i',
		    // return the corresponding value from the 'values' array
			return values[mid];
		else if (lines[mid] < i)
			// If the current line index is less than 'i', continue searching
			// in the upper half of the remaining elements
			start = mid + 1;
		else
			// If the current line index is greater than 'i', continue searching
			// in the lower half of the remaining elements
			end = mid - 1;
	}
	// if the element hasn't been found
	return NULL_TELEM; //return 0
}

//BC: Theta(1) --> 
//    NO insertion/remove is performed:
//	  - we have the element represented by the pair (i, j) in the matrix, AND it is found in Theta(1) and we modify it to a non-null value
//	  (if we find the element in Theta(log nrNonZeroElements) OR we don't have the element represented by the pair (i, j) in the matrix and it is modified with a null value ==> Theta(log nrNonZeroElements) )
//WC: Theta(size + log nrNonZeroElements) --> nrNonZeroElements = number of non-zero elements in a column j
//    - the element represented by the pair (i, j) is a null value and we modify it to a non-null value --> insertion
//    - we have the element represented by the pair (i, j) in the matrix and it is modified with a null value --> remove
//TC: O(size + log nrNonZeroElements)
TElem Matrix::modify(int i, int j, TElem e) {
	// Check if the provided indices are within bounds
	if (i < 0 || i >= nrLin || j < 0 || j >= nrCol)
		throw std::exception("Index out of bounds");
	//The search of the element (lin, col, elem) results in the following:
	//4 cases:
	//1 - the element and new element are not null --> we change the value of the element
	//2 - the element is null and the new element is not null --> we add (insert) the new element
	//3 - the element is not null and the new element is null --> we delete the element
	//4 - the element and new element are null --> we do nothing
	// 
	// Define the start and end indices for binary search in the column 'j'
	int start = cols[j];
	int end = cols[j + 1] - 1;
	
	// Perform binary search within the column to find the element and update it accordingly
	while (start <= end) {
		int mid = start + (end - start) / 2;
		//if we found the element
		if (lines[mid] == i) {
			// If the current line index equals the requested line 'i',
			// store the current value in a temporary variable
			TElem oldValue = values[mid];
			if (e != NULL_TELEM) {
				// If the new element is not NULL, update the value in the 'values' array
				values[mid] = e;
			}
			else {
				// If the new element is NULL, delete the element from the 'values' and 'lines' arrays
				for (int k = mid; k < size; k++) {
					values[k] = values[k + 1];
					lines[k] = lines[k + 1];
				}
				for (int k = j + 1; k <= nrCol; k++)
					cols[k]--; //decrease the beginning of the next columns
			}
			return oldValue; //return the old value
		}
		
		else if (lines[mid] < i) {
			// If the current line index is less than 'i', continue searching
			// in the upper half of the remaining elements
			start = mid + 1;
		}
		
		else {
			// If the current line index is greater than 'i', continue searching
			// in the lower half of the remaining elements
			end = mid - 1;
		}
	}
	//start = end + 1
	//the position where we have to insert the new element is after the 'end' position --> shift all the elements from 'start' to 'size' with one position to the right
	
	//if we have to insert a new element
	if (e != NULL_TELEM) {
		// If the new element is not NULL, insert it in the 'values' and 'lines' arrays -> O(nrNonZeroElements)
		if (size == capacity) {
			// If the current capacity is not enough, resize the arrays
			resize(); //Theta(1) amortized
		}
		//shift the elements to the right
		int k = size;
		while (k > start) {
			values[k] = values[k - 1];
			lines[k] = lines[k - 1];
			k--;
		}
		// Insert the new element at the correct position
		values[start] = e;
		lines[start] = i;
		
		for (int k = j + 1; k <= nrCol; k++)
			cols[k]++; //increase the beginning index of the next columns
		
		size++; //increase the number of non-zero elements in the matrix
	}
	//if both the old and new elements are NULL, we do nothing
	return NULL_TELEM;
}


//BC=WC=TC=Theta(size) ~ Number of nonZeroElements elements in the matrix
void Matrix::resize()
{
	if (capacity == 0) //if the matrix is empty
	{
		capacity = 1;
		values = new TElem[capacity];
		lines = new int[capacity];
	}
	else
	{
		capacity *= 2; //increase the capacity
		TElem* newValues = new TElem[capacity]; //reallocate the matrix values
		int* newLines = new int[capacity];	//reallocate the line numbers
		for (int i = 0; i < capacity / 2; i++) //copy the current elems
		{
			newValues[i] = values[i];
			newLines[i] = lines[i];
		}
		delete[] values; //deallocate old memory
		delete[] lines; //deallocate old memory
		values = newValues; //reset pointers
		lines = newLines; //reset pointers
	}
}


//BC = Theta(nrLin * log nrLin) --> all the elements on column col are not null (no insertions) 
//									(or they are all null and we set the column to null --> no deletions
//WC = Theta(nrLin * (size + log nrLin)) --> we need to insert/delete all the elements
//TC = O(nrLin * (size + log nrLin)); size = number of non-null elements
//Possible optimization: calculate how many elements need to be inserted(deleted), insert(delete) each element 
//while shifting the rest of the elements to the right(left) to their final positions in the array --> TC = O(size + nrLin * log nrLin)
void Matrix::setElemsOnCol(int col, TElem elem)
{
	if (col < 0 || col >= nrCol)
		throw std::exception("Column index out of bounds");
	
	for (int i = 0; i < nrLin; i++)
	{
		modify(i, col, elem);
	}
}
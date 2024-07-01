#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

//Sparse matrix with compressed columns represented on a dynamic array

class Matrix {

private:
	int nrLin, nrCol;
	TElem* values;
	int* lines;
	int capacity;
	int size;
	int* cols; 
	void resize();
	
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//sets all the values from col to the value elem
	//throws an exception if col is not valid
	void setElemsOnCol(int col, TElem elem);

	class Iterator {
	private:
		const Matrix& matrix;
		int currentCol;
		int currentPosition;
		
	public:
		Iterator(const SparseMatrix& matrix) : matrix(matrix), currentCol(0), currentPosition(matrix.cols[0]) {}
		
		// Method to get the current element
		TElem getCurrent() {
			return matrix.values[currentPosition];
		}

		// Method to check if the iterator is valid
		bool valid() {
			return currentCol < matrix.nrColumns() && currentPosition < matrix.size;
		}

		// Method to move to the next element
		void next() {
			currentPosition++;
			while (currentCol < matrix.nrColumns() && currentPosition >= matrix.cols[currentCol + 1]) {
				currentCol++;
				currentPosition = matrix.cols[currentCol];
			}
		}

		// Method to move to the first element
		void first() {
			currentCol = 0;
			currentPosition = matrix.cols[0];
		}
	};
};

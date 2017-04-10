#pragma once

class Matrix
{
private:
    //Stores gamestate as a 1D array
    int* Value;
public:
	int NumRow;
	int NumCol;

	//Returns true if within bounds
	bool checkBounds(int row, int col);

	//Access via Matrix(row,col)
	int& operator()(int row, int col);
    const int& operator()(int row, int col) const;

	friend void swap(Matrix& first, Matrix& second);
    
    Matrix();
	Matrix(int _row, int _col);
	//Copy assignment by copy-and-swap pass by value
    Matrix(const Matrix & other);
    Matrix(Matrix&& other);
    Matrix& operator=(Matrix other);
	~Matrix();
};
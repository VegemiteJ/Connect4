
#include "Matrix.h"

#include <memory>
#include <string>
#include <sstream>

using namespace std;

void swap(Matrix & first, Matrix & second)
{
	using std::swap;

	swap(first.NumCol, second.NumCol);
	swap(first.NumRow, second.NumRow);
	swap(first.Value, second.Value);
}

int& Matrix::operator()(int row, int col)
{
    int index = row*NumCol + col;
    if (index < 0 || index >= NumRow*NumCol)
    {
        stringstream ss;
        ss << "OutOfBoundsAccess at " << row << " " << col << " Index: " << index;
        string result = ss.str();
        const char* ExceptionMessage = result.c_str();
        throw exception(ExceptionMessage);
    }
	return Value[index];
}

const int& Matrix::operator()(int row, int col) const
{
    int index = row*NumCol + col;
    if (index < 0 || index >= NumRow*NumCol)
    {
        stringstream ss;
        ss << "OutOfBoundsAccess at " << row << " " << col << " Index: " << index;
        string result = ss.str();
        const char* ExceptionMessage = result.c_str();
        throw exception(ExceptionMessage);
    }
    return Value[index];
}

Matrix::Matrix() {}

Matrix::Matrix(int _row, int _col)
{
	NumRow = _row;
	NumCol = _col;

    Value = new int[_row*_col]{ {0} };
}

Matrix & Matrix::operator=(Matrix other)
{
	swap(*this, other);
	return *this;
}

Matrix::Matrix(const Matrix & other)
{
    Value = new int[(other.NumCol)*(other.NumRow)]{ {0} };
    std::copy(other.Value, other.Value + other.NumCol*other.NumRow, Value);

    NumCol = other.NumCol;
    NumRow = other.NumRow;
}

Matrix::Matrix(Matrix && other)
    :Matrix()
{
    swap(*this, other);
}

Matrix::~Matrix()
{
	delete[] Value;
}


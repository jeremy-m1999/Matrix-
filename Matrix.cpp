#include "Matrix.h"

using namespace std;

/*
This program implements a matrix given the number of rows, number of columns, and
a pointer to an array[][]. Includes modified copy constructor, move constructor,
copy assignment operator, move assignment operator, constructor and destructor.
Additionally, various methods of this class allow you to set values within the matrix,
get values within the matrix, add two matrices together, get the number of rows/cols and
prints the matrix

@author Jeremy Mednik
*/

//Constructor
Matrix::Matrix(): numRows{DEFAULT_SIZE}, numCols{DEFAULT_SIZE} {
  //Creates a pointer to an DEFAULT_SIZE x DEFAULT_SIZE array
  values = new double*[DEFAULT_SIZE];
  for (int row = 0; row < numRows; ++row) {
    values[row] = new double[numCols];
  }

  //Sets all values in the array[][] to 0
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      values[row][col] = 0;
    }
  }
}



//Constructor with parameters
Matrix::Matrix(int numRows, int numCols) {
  //Throws a runtime error if the integers passed in are negative
  if (numCols < 0 || numRows < 0) {
    string str = "Invalid string indices: " + to_string(numRows) + " , " + to_string(numCols);
    throw runtime_error(str.c_str());
  }
  //Specifies the number of rows, n and number of columns, m, for the matrix
  this -> numRows = numRows;
  this -> numCols = numCols;

  //Creates a pointer to an n x m array
  values = new double*[numRows];
  for (int row = 0; row < numRows; ++row) {
    values[row] = new double[numCols];
  }
  //Sets all values in the array[][] to 0
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      values[row][col] = 0;
    }
  }
}



//Copy constructor
Matrix :: Matrix(const Matrix& other) {
  //Sets the number of rows and number of columns equal to the other matrix object
  numRows = other.numRows;
  numCols = other.numCols;
  values = new double*[numRows];

  //Creates a pointer to an other.numRows x other.numCols array
  for (int row = 0; row < numRows; ++row) {
    values[row] = new double[numCols];
  }

  //Sets all values in the matrix to the other matrix
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      values[row][col] = other.values[row][col];
    }
  }
}



//Copy assignment operator
Matrix& Matrix :: operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }

  //Creates a pointer to an other.numRows x other.numCols array
  double** Newvalues = new double*[other.numRows];

  for (int row = 0; row < other.numRows; ++row) {
    Newvalues[row] = new double[other.numCols];
  }

  //Sets all values in the matrix to the other matrix
  for (int row = 0; row < other.numRows; ++row) {
    for (int col = 0; col < other.numCols; ++col) {
      Newvalues[row][col] = other.values[row][col];
    }
  }

  //Deallocates memory
  for (int row = 0; row < numRows; ++row) {
    delete[] values[row];
  }
  // Then delete the array or pointers to arrays
  delete[] values;
  //Replaces the values of the matrix with the new values of the matrix
  values = Newvalues;

  //Replaces the number of rows and columns of the matrix with the new values of the matrix
  numRows = other.numRows;
  numCols = other.numCols;

  return *this;
}





Matrix:: Matrix(Matrix&& other)noexcept: numRows{other.numRows}, numCols{other.numCols},
values{new double*[other.numRows]}{
  //Creates a new pointer to an array[][]
  for (int row = 0; row < numRows; ++row) {
    this -> values[row] = new double[numCols];
  }
  //Sets the values the matrix to the values of the other matrix
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      this -> values[row][col] = other.values[row][col];
    }
  }

  //Canibalizes other
  for (int row = 0; row < other.numRows; ++row) {
    other.values[row] = nullptr;
  }
  other.values = nullptr;
  other.numRows = 0;
  other.numCols = 0;
}



//Move assignment operator
Matrix& Matrix :: operator=(Matrix&& other)noexcept {
  if (this == &other) {
    return *this;
  }
  //Creates a new pointer to an array[][]
  double** Newvalues = new double*[other.numRows];

  for (int row = 0; row < other.numRows; ++row) {
    Newvalues[row] = new double[other.numCols];
  }
  //Sets the values the matrix to the values of the other matrix
  for (int row = 0; row < other.numRows; ++row) {
    for (int col = 0; col < other.numCols; ++col) {
      Newvalues[row][col] = other.values[row][col];
    }
  }

  for (int row = 0; row < numRows; ++row) {
    delete[] values[row];
  }
  // Then delete the array or pointers to arrays
  delete[] values;
  //Replaces the pointer
  values = Newvalues;

  //Sets number of rows and columns of the matrix to that of other
  numRows = other.numRows;
  numCols = other.numCols;

  //Canibalizes other
  for (int row = 0; row < other.numRows; ++row) {
    other.values[row] = nullptr;
  }
  // Then delete the array or pointers to arrays
  other.values = nullptr;
  other.numRows = 0;
  other.numCols = 0;

  return *this;
}



//+ operator
Matrix Matrix :: operator+(const Matrix& other) {
  //Checks to see if the matrices are the same size and throws a runtime error if not
  if (numRows != other.numRows || numCols != other.numCols) {
    string str = "Matrices Different Size: " + to_string(numRows) + "x" + to_string(numCols) +  " , "
    + to_string(other.numRows) + "x" + to_string(other.numCols) ;
    throw runtime_error(str.c_str());
  }

  //Creates a new matrix
  Matrix addition(other.numRows, other.numCols);

  //Sets the values the matrix to the values of the other matrix + the values of this matrix
  for (int row = 0; row < other.numRows; ++row) {
    for (int col = 0; col < other.numCols; ++col) {
      addition.values[row][col] = values[row][col] + other.values[row][col];
    }
  }
  //Returns a matrix
  return addition;
}



//- operator
Matrix Matrix :: operator-(const Matrix& other) {
  //Checks to see if the matrices are the same size and throws a runtime error if not
  if (numRows != other.numRows || numCols != other.numCols) {
    string str = "Matrices Different Size: " + to_string(numRows) + "x" + to_string(numCols) +  " , "
    + to_string(other.numRows) + "x" + to_string(other.numCols) ;
    throw runtime_error(str.c_str());
  }

  //Creates a new matrix
  Matrix subtraction(other.numRows, other.numCols);

  //Sets the values the matrix to the values of the other matrix - the values of this matrix
  for (int row = 0; row < other.numRows; ++row) {
    for (int col = 0; col < other.numCols; ++col) {
      subtraction.values[row][col] = values[row][col] - other.values[row][col];
    }
  }
  //Returns a matrix
  return subtraction;
}

//* operator
Matrix Matrix :: operator*(const Matrix& other) {
  //Checks to see if the matrices are the same size and throws a runtime error if not
  if (numCols != other.numRows) {
    string str = "Matrices Different Size: " + to_string(numRows) + "x" + to_string(numCols) +  " , "
    + to_string(other.numRows) + "x" + to_string(other.numCols) ;
    throw runtime_error(str.c_str());
  }

  //Creates a new matrix
  Matrix multiplication(numRows, other.numCols);

  //Sets the values the matrix to the values of the other matrix - the values of this matrix
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < other.numCols; ++col) {
      for (int row2 = 0; row2 < other.numRows; row2++) {
        multiplication.values[row][col] += values[row][row2] * other.values[row2][col];
      }
    }
  }
  //Returns a matrix
  return multiplication;
}



//+= operator
Matrix& Matrix :: operator+=(const Matrix& other) {
  //Checks to see if the matrices are the same size
  if (numRows != other.numRows || numCols != other.numCols) {
    return *this;
  }

  //Adds the values of other matrix to this matrix in their respective index
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      this -> values[row][col] += other.values[row][col];
    }
  }
  return *this;
}



//Destructor
Matrix::~Matrix() {
  // First delete each row (every row is an array)
  for (int row = 0; row < numRows; ++row) {
    delete[] values[row];
  }
  // Then delete the array or pointers to arrays
  delete[] values;
}



//Gets the value of the matrix at the specified indices
double Matrix :: get(int row, int col) {
  //Checks to see if the indices specified are within the matrix
  if (row >= this -> numRows || col >= this -> numCols || col < 0 || row < 0) {
    string str = "Invalid string indices: " + to_string(numRows) + " , " + to_string(numCols);
    throw runtime_error(str.c_str());
  }
  //Returns a double
  return values[row][col];
}



//Returns a transpose of the matrix
Matrix Matrix :: transpose() {
  Matrix transpose( this -> numCols, this -> numRows);
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      transpose.values[col][row] = values[row][col];
    }
  }
  return transpose;
}



//Returns number of rows in this matrix
int Matrix :: getNumRows() {
  return numRows;
}



//Returns number of cols in this matrix
int Matrix :: getNumCols() {
  return numCols;
}



//Sets a value for a matrix at a given index
void Matrix :: set(int row, int col, double value) {
  //Checks to see if the indices are within the current matrix
  if (row >= this -> numRows || col >= this -> numCols || col < 0 || row < 0) {
    string str = "Invalid string indices: " + to_string(row) + " , " + to_string(col);
    throw runtime_error(str.c_str());
  }
  //Sets the new value at given indices
  values[row][col] = value;
}



//Prints the matrix
void Matrix::print() {
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      cout << values[row][col] << " ";
    }
    cout << endl;
  }
}

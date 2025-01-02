// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <stdexcept>
#include <fstream>

class Matrix {
private:
    int** mat;
    int rows;
    int cols;

    // Helper function to allocate memory
    void allocateMemory() {
        mat = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            mat[i] = new int[cols];
        }
    }

    // Helper function to deallocate memory
    void deallocateMemory() {
        for (int i = 0; i < rows; ++i) {
            delete[] mat[i];
        }
        delete[] mat;
    }

public:
    // Constructor
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        allocateMemory();
    }

    // Copy constructor
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocateMemory();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = other.mat[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        deallocateMemory();
    }

    // Get number of rows
    int getRows() const {
        return rows;
    }

    // Get number of columns
    int getCols() const {
        return cols;
    }

    // Overload operator() for accessing elements
    int& operator()(int row, int col) {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Index out of bounds");
        return mat[row][col];
    }

    const int& operator()(int row, int col) const {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Index out of bounds");
        return mat[row][col];
    }

    // Overload assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        deallocateMemory();

        rows = other.rows;
        cols = other.cols;
        allocateMemory();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = other.mat[i][j];
            }
        }

        return *this;
    }

    // Addition of two matrices
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = mat[i][j] + other.mat[i][j];
            }
        }

        return result;
    }

    // Subtraction of two matrices
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = mat[i][j] - other.mat[i][j];
            }
        }

        return result;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Number of columns of the first matrix must equal number of rows of the second matrix.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result(i, j) = 0;
                for (int k = 0; k < cols; ++k) {
                    result(i, j) += mat[i][k] * other.mat[k][j];
                }
            }
        }

        return result;
    }
    Matrix& operator+=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition.");
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] += other.mat[i][j];
            }
        }

        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] -= other.mat[i][j];
            }
        }

        return *this;
    }

    Matrix& operator*=(const Matrix& other) {
        if (cols != other.rows) {
            throw std::invalid_argument("Number of columns of the first matrix must equal number of rows of the second matrix.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result(i, j) = 0;
                for (int k = 0; k < cols; ++k) {
                    result(i, j) += mat[i][k] * other.mat[k][j];
                }
            }
        }

        *this = result; // Assign the result back to the current matrix

        return *this;
    }

    // Transpose of the matrix
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(j, i) = mat[i][j];
            }
        }

        return result;
    }

    friend std::istream& operator>>(std::istream& in, Matrix& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                in >> matrix.mat[i][j];
            }
        }
        return in;
    }

    // Friend function to overload output stream operator
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                out << matrix.mat[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
};

int main() {

    return 0;
}

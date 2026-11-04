
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Matrix {
private:
    int n;
    vector<vector<int>> data;

public:
    Matrix(int size = 0)
        : n(size), data(size, vector<int>(size, 0)) {}

    int size() const {
        return n;
    }

    void read(ifstream& file) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                file >> data[i][j];
    }

    void display() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << setw(4) << data[i][j];
            cout << endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result.data[i][j] =
                    data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    result.data[i][j] +=
                        data[i][k] * other.data[k][j];
        return result;
    }

    int mainDiagonalSum() const {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += data[i][i];
        return sum;
    }

    int secondaryDiagonalSum() const {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += data[i][n - 1 - i];
        return sum;
    }

    bool validIndex(int index) const {
        return index >= 0 && index < n;
    }

    void swapRows(int r1 = 0, int r2 = 1) {
        if (!validIndex(r1) || !validIndex(r2)) {
            cout << "Invalid row indices." << endl;
            return;
        }
        swap(data[r1], data[r2]);
    }

    void swapColumns(int c1 = 0, int c2 = 1) {
        if (!validIndex(c1) || !validIndex(c2)) {
            cout << "Invalid column indices." << endl;
            return;
        }
        for (int i = 0; i < n; i++)
            swap(data[i][c1], data[i][c2]);
    }

    void update(int row = 0, int col = 0,
                int value = 100) {
        if (!validIndex(row) || !validIndex(col)) {
            cout << "Invalid row or column index." << endl;
            return;
        }
        data[row][col] = value;
    }
};

// Matrix is passed by value to keep the original unchanged.
void swapMatrixRows(Matrix matrix, int r1 = 0,
                    int r2 = 1) {
    matrix.swapRows(r1, r2);
    matrix.display();
}

void swapMatrixColumns(Matrix matrix, int c1 = 0,
                       int c2 = 1) {
    matrix.swapColumns(c1, c2);
    matrix.display();
}

void updateMatrix(Matrix matrix, int row = 0,
                  int col = 0, int value = 100) {
    matrix.update(row, col, value);
    matrix.display();
}

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int n;
    if (!(file >> n) || n <= 0) {
        cout << "Invalid matrix size." << endl;
        return 1;
    }

    Matrix A(n), B(n);
    A.read(file);
    B.read(file);

    if (!file) {
        cout << "Invalid matrix data." << endl;
        return 1;
    }

    cout << "Matrix A:" << endl;
    A.display();

    cout << "Matrix B:" << endl;
    B.display();

    cout << "A + B:" << endl;
    Matrix sum = A + B;
    sum.display();

    cout << "A * B:" << endl;
    Matrix product = A * B;
    product.display();

    cout << "Diagonal sums for Matrix A:" << endl;
    cout << "Main diagonal sum: "
         << A.mainDiagonalSum() << endl;
    cout << "Secondary diagonal sum: "
         << A.secondaryDiagonalSum() << endl;

    cout << "Problem 5 - Rows 0 and 2 swapped:"
         << endl;
    swapMatrixRows(A, 0, 2);

    cout << "Problem 6 - Columns 0 and 2 swapped:"
         << endl;
    swapMatrixColumns(A, 0, 2);

    cout << "Problem 7 - Updated matrix:" << endl;
    updateMatrix(A, 1, 2, 99);

    return 0;
}

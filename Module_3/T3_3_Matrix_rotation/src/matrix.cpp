#include "matrix.hpp"

#include <iostream>
#include <vector>

// Assumes 'm' is a square matrix
Matrix ReadMatrix(int n) {
    Matrix m(n, std::vector<int>(n));

    for (auto& row : m) {
        for (auto& elem : row) {
            std::cin >> elem;
        }
    }

    return m;
}

Matrix Rotate90Deg(const Matrix& m) {
    int n = m.size();
    Matrix rotated(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = m[i][j];
        }
    }

    return rotated;
}

void Print(const Matrix& m) {
    int n = m.size();
    std::cout << "Printing out a " << n << " x " << n << " matrix:" << std::endl;

    for (const auto& row : m) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

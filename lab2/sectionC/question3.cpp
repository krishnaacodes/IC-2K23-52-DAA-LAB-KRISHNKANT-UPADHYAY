
#include <iostream>
#include <vector>
using namespace std;

// Convert full matrix into sparse representation
vector<vector<int>> toSparse(vector<vector<int>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> sparse;

    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    // Header: rows, columns, non-zero elements
    sparse.push_back({rows, cols, count});

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse.push_back({i, j, matrix[i][j]});
            }
        }
    }

    return sparse;
}

// Reconstruct full matrix from sparse representation
vector<vector<int>> toFull(vector<vector<int>> sparse) {
    int rows = sparse[0][0];
    int cols = sparse[0][1];

    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    for (int i = 1; i < sparse.size(); i++) {
        int r = sparse[i][0];
        int c = sparse[i][1];
        int value = sparse[i][2];

        matrix[r][c] = value;
    }

    return matrix;
}

// Add two sparse matrices directly
vector<vector<int>> addSparse(
    vector<vector<int>> A,
    vector<vector<int>> B
) {
    if (A[0][0] != B[0][0] || A[0][1] != B[0][1]) {
        cout << "Matrix dimensions do not match!\n";
        return {};
    }

    vector<vector<int>> result;

    int rows = A[0][0];
    int cols = A[0][1];

    int i = 1, j = 1;

    // Merge two sorted sparse representations
    while (i < A.size() && j < B.size()) {

        int rowA = A[i][0];
        int colA = A[i][1];

        int rowB = B[j][0];
        int colB = B[j][1];

        if (rowA == rowB && colA == colB) {
            int sum = A[i][2] + B[j][2];

            if (sum != 0) {
                result.push_back({rowA, colA, sum});
            }

            i++;
            j++;
        }
        else if (rowA < rowB ||
                (rowA == rowB && colA < colB)) {

            result.push_back(A[i]);
            i++;
        }
        else {
            result.push_back(B[j]);
            j++;
        }
    }

    // Add remaining elements of A
    while (i < A.size()) {
        result.push_back(A[i]);
        i++;
    }

    // Add remaining elements of B
    while (j < B.size()) {
        result.push_back(B[j]);
        j++;
    }

    // Add header
    result.insert(result.begin(),
                  {rows, cols, (int)result.size()});

    return result;
}

// Display sparse representation
void displaySparse(vector<vector<int>> sparse) {
    cout << "Row  Column  Value\n";

    for (int i = 0; i < sparse.size(); i++) {
        cout << sparse[i][0] << "     "
             << sparse[i][1] << "       "
             << sparse[i][2] << endl;
    }
}

// Display full matrix
void displayFull(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;

    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    vector<vector<int>> A(rows, vector<int>(cols));
    vector<vector<int>> B(rows, vector<int>(cols));

    cout << "Enter first matrix:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> A[i][j];
        }
    }

    cout << "Enter second matrix:\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> B[i][j];
        }
    }

    // Convert both matrices into sparse form
    vector<vector<int>> sparseA = toSparse(A);
    vector<vector<int>> sparseB = toSparse(B);

    cout << "\nSparse Matrix A:\n";
    displaySparse(sparseA);

    cout << "\nSparse Matrix B:\n";
    displaySparse(sparseB);

    // Reconstruct full matrices
    cout << "\nReconstructed Matrix A:\n";
    displayFull(toFull(sparseA));

    cout << "\nReconstructed Matrix B:\n";
    displayFull(toFull(sparseB));

    // Add sparse matrices directly
    vector<vector<int>> sparseSum =
        addSparse(sparseA, sparseB);

    if (!sparseSum.empty()) {
        cout << "\nSparse Addition Result:\n";
        displaySparse(sparseSum);

        cout << "\nReconstructed Addition Result:\n";
        displayFull(toFull(sparseSum));
    }

    return 0;
}

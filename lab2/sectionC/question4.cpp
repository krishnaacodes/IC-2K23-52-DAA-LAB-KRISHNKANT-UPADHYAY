
#include <iostream>
#include <vector>
using namespace std;

// Function to input a matrix
vector<vector<int>> inputMatrix(int r, int c) {
    vector<vector<int>> mat(r, vector<int>(c));

    cout << "Enter matrix elements:\n";

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> mat[i][j];
        }
    }

    return mat;
}

// Function to display a matrix
void displayMatrix(vector<vector<int>> mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

// Matrix Addition
void addMatrix() {
    int r1, c1, r2, c2;

    cout << "Enter rows and columns of Matrix A: ";
    cin >> r1 >> c1;

    auto A = inputMatrix(r1, c1);

    cout << "Enter rows and columns of Matrix B: ";
    cin >> r2 >> c2;

    auto B = inputMatrix(r2, c2);

    if (r1 != r2 || c1 != c2) {
        cout << "Addition not possible!\n";
        return;
    }

    vector<vector<int>> C(r1, vector<int>(c1));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "Addition Result:\n";
    displayMatrix(C);
}

// Matrix Multiplication
void multiplyMatrix() {
    int r1, c1, r2, c2;

    cout << "Enter rows and columns of Matrix A: ";
    cin >> r1 >> c1;

    auto A = inputMatrix(r1, c1);

    cout << "Enter rows and columns of Matrix B: ";
    cin >> r2 >> c2;

    auto B = inputMatrix(r2, c2);

    if (c1 != r2) {
        cout << "Multiplication not possible!\n";
        return;
    }

    vector<vector<int>> C(r1, vector<int>(c2, 0));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "Multiplication Result:\n";
    displayMatrix(C);
}

// Matrix Transpose
void transposeMatrix() {
    int r, c;

    cout << "Enter rows and columns: ";
    cin >> r >> c;

    auto A = inputMatrix(r, c);

    vector<vector<int>> T(c, vector<int>(r));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            T[j][i] = A[i][j];
        }
    }

    cout << "Transpose Matrix:\n";
    displayMatrix(T);
}

// Determinant of a 2x2 or 3x3 matrix
void determinantMatrix() {
    int n;

    cout << "Enter order of square matrix (2 or 3): ";
    cin >> n;

    if (n != 2 && n != 3) {
        cout << "Only 2x2 and 3x3 matrices are supported!\n";
        return;
    }

    auto A = inputMatrix(n, n);

    int det;

    if (n == 2) {
        det = A[0][0] * A[1][1] -
              A[0][1] * A[1][0];
    }
    else {
        det =
            A[0][0] * (A[1][1] * A[2][2] -
                       A[1][2] * A[2][1])

          - A[0][1] * (A[1][0] * A[2][2] -
                       A[1][2] * A[2][0])

          + A[0][2] * (A[1][0] * A[2][1] -
                       A[1][1] * A[2][0]);
    }

    cout << "Determinant = " << det << endl;
}

int main() {
    int choice;

    do {
        cout << "\n===== MATRIX CALCULATOR =====\n";
        cout << "1. Add Two Matrices\n";
        cout << "2. Multiply Two Matrices\n";
        cout << "3. Transpose Matrix\n";
        cout << "4. Find Determinant\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addMatrix();
                break;

            case 2:
                multiplyMatrix();
                break;

            case 3:
                transposeMatrix();
                break;

            case 4:
                determinantMatrix();
                break;

            case 5:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

// Function to display the matrix
void display(vector<vector<int>> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> arr;
    int rows, cols, choice, pos, value;

    cout << "Enter number of rows: ";
    cin >> rows;

    cout << "Enter number of columns: ";
    cin >> cols;

    arr.resize(rows, vector<int>(cols));

    cout << "Enter matrix elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }

    do {
        cout << "\n--- 2D Array Operations ---\n";
        cout << "1. Insert a Row\n";
        cout << "2. Delete a Row\n";
        cout << "3. Search an Element\n";
        cout << "4. Rotate 90 Degrees Clockwise\n";
        cout << "5. Display Matrix\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            cout << "Enter position to insert row: ";
            cin >> pos;

            if (pos >= 0 && pos <= arr.size()) {
                vector<int> newRow(cols);

                cout << "Enter " << cols << " elements:\n";
                for (int j = 0; j < cols; j++) {
                    cin >> newRow[j];
                }

                arr.insert(arr.begin() + pos, newRow);

                cout << "After insertion:\n";
                display(arr);
            }
            else {
                cout << "Invalid position!\n";
            }
            break;
        }

        case 2: {
            cout << "Enter row position to delete: ";
            cin >> pos;

            if (pos >= 0 && pos < arr.size()) {
                arr.erase(arr.begin() + pos);

                cout << "After deletion:\n";
                display(arr);
            }
            else {
                cout << "Invalid position!\n";
            }
            break;
        }

        case 3: {
            cout << "Enter value to search: ";
            cin >> value;

            bool found = false;

            for (int i = 0; i < arr.size(); i++) {
                for (int j = 0; j < arr[i].size(); j++) {
                    if (arr[i][j] == value) {
                        cout << "Element found at Row: "
                             << i << ", Column: " << j << endl;
                        found = true;
                    }
                }
            }

            if (!found) {
                cout << "Element not found!\n";
            }
            break;
        }

        case 4: {
            if (arr.empty() || arr[0].empty()) {
                cout << "Cannot rotate an empty matrix!\n";
                break;
            }

            int r = arr.size();
            int c = arr[0].size();

            vector<vector<int>> rotated(c, vector<int>(r));

            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    rotated[j][r - 1 - i] = arr[i][j];
                }
            }

            arr = rotated;

            cout << "After 90 degree clockwise rotation:\n";
            display(arr);
            break;
        }

        case 5:
            cout << "Current Matrix:\n";
            display(arr);
            break;

        case 6:
            cout << "Program terminated.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

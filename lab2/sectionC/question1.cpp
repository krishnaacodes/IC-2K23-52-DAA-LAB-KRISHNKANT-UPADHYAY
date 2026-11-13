
#include <iostream>
using namespace std;

int main() {
    int arr[100], n, choice, value, index, k;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    do {
        cout << "\n--- 1D Array Operations ---\n";
        cout << "1. Insert an element\n";
        cout << "2. Delete an element\n";
        cout << "3. Linear Search\n";
        cout << "4. Rotate Left\n";
        cout << "5. Rotate Right\n";
        cout << "6. Display Array\n";
        cout << "7. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter value: ";
            cin >> value;

            cout << "Enter index: ";
            cin >> index;

            if (index >= 0 && index <= n && n < 100) {
                for (int i = n; i > index; i--) {
                    arr[i] = arr[i - 1];
                }

                arr[index] = value;
                n++;

                cout << "After insertion: ";
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " ";
                cout << endl;
            }
            else {
                cout << "Invalid index or array is full!\n";
            }
            break;

        case 2:
            cout << "Enter index to delete: ";
            cin >> index;

            if (index >= 0 && index < n) {
                for (int i = index; i < n - 1; i++) {
                    arr[i] = arr[i + 1];
                }

                n--;

                cout << "After deletion: ";
                for (int i = 0; i < n; i++)
                    cout << arr[i] << " ";
                cout << endl;
            }
            else {
                cout << "Invalid index!\n";
            }
            break;

        case 3:
            cout << "Enter value to search: ";
            cin >> value;

            index = -1;

            for (int i = 0; i < n; i++) {
                if (arr[i] == value) {
                    index = i;
                    break;
                }
            }

            if (index != -1)
                cout << "Element found at index: " << index << endl;
            else
                cout << "Element not found!\n";
            break;

        case 4:
            cout << "Enter rotation positions: ";
            cin >> k;

            if (n > 0 && k >= 0) {
                k = k % n;

                for (int j = 0; j < k; j++) {
                    int first = arr[0];

                    for (int i = 0; i < n - 1; i++) {
                        arr[i] = arr[i + 1];
                    }

                    arr[n - 1] = first;
                }
            }

            cout << "After left rotation: ";
            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << endl;
            break;

        case 5:
            cout << "Enter rotation positions: ";
            cin >> k;

            if (n > 0 && k >= 0) {
                k = k % n;

                for (int j = 0; j < k; j++) {
                    int last = arr[n - 1];

                    for (int i = n - 1; i > 0; i--) {
                        arr[i] = arr[i - 1];
                    }

                    arr[0] = last;
                }
            }

            cout << "After right rotation: ";
            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << endl;
            break;

        case 6:
            cout << "Current array: ";
            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << endl;
            break;

        case 7:
            cout << "Program terminated.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}

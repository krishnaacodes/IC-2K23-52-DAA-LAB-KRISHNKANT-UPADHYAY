
#include <iostream>
using namespace std;

// Function to display array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    cout << "\n--- Bubble Sort ---\n";

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        cout << "Pass " << i + 1 << ": ";
        display(arr, n);
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    cout << "\n--- Selection Sort ---\n";

    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);

        cout << "Pass " << i + 1 << ": ";
        display(arr, n);
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n) {
    cout << "\n--- Insertion Sort ---\n";

    for (int i = 1; i < n; i++) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {

            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

        cout << "Step " << i << ": ";
        display(arr, n);
    }
}

// Main Function
int main() {

    int arr1[] = {5, 2, 8, 1, 9};
    int arr2[] = {5, 2, 8, 1, 9};
    int arr3[] = {5, 2, 8, 1, 9};

    int n = 5;

    cout << "Original Array: ";
    display(arr1, n);

    // Calling Bubble Sort
    bubbleSort(arr1, n);

    // Calling Selection Sort
    selectionSort(arr2, n);

    // Calling Insertion Sort
    insertionSort(arr3, n);

    return 0;
}

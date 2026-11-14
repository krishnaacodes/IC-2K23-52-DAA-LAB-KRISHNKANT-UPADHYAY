
#include <iostream>
using namespace std;

// Helper function: Counting Sort for a specific digit position
void countingSort(int arr[], int n, int exp) {

    int output[n];
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Calculate cumulative count
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build output array in stable order
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;

        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort using LSD approach
void radixSort(int arr[], int n) {

    // Find maximum element
    int maxValue = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }

    // Sort by ones, tens, hundreds, etc.
    for (int exp = 1; maxValue / exp > 0; exp *= 10) {

        countingSort(arr, n, exp);

        if (exp == 1)
            cout << "After sorting by ones digit: ";
        else if (exp == 10)
            cout << "After sorting by tens digit: ";
        else if (exp == 100)
            cout << "After sorting by hundreds digit: ";
        else
            cout << "After sorting at position " << exp << ": ";

        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }

        cout << endl;
    }
}

// Main Function
int main() {

    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};

    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original Array: ";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n\n--- Radix Sort ---\n";

    radixSort(arr, n);

    cout << "\nFinal Sorted Array: ";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}

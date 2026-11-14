
#include <iostream>
using namespace std;

// Iterative Binary Search Function
int binarySearch(int arr[], int n, int target) {

    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        // Check if target is found
        if (arr[mid] == target) {
            return mid;
        }

        // Search in the right half
        else if (arr[mid] < target) {
            low = mid + 1;
        }

        // Search in the left half
        else {
            high = mid - 1;
        }
    }

    // Target not found
    return -1;
}

// Main Function
int main() {

    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};

    int n = sizeof(arr) / sizeof(arr[0]);

    int target1 = 23;
    int target2 = 30;

    cout << "Sorted Array: ";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    // Search for existing value
    int result1 = binarySearch(arr, n, target1);

    cout << "\n\nSearching for " << target1 << ":";

    if (result1 != -1) {
        cout << "\nElement found at index: " << result1;
    }
    else {
        cout << "\nElement not found.";
    }

    // Search for non-existing value
    int result2 = binarySearch(arr, n, target2);

    cout << "\n\nSearching for " << target2 << ":";

    if (result2 != -1) {
        cout << "\nElement found at index: " << result2;
    }
    else {
        cout << "\nElement not found. Index: " << result2;
    }

    cout << endl;

    return 0;
}

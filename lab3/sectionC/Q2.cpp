
#include <iostream>
using namespace std;

// Function to display array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ---------------- MERGE SORT ----------------

// Merge two sorted subarrays
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[low + i];

    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];

    while (j < n2)
        arr[k++] = right[j++];
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// ---------------- QUICK SORT ----------------

// Pivot selection strategy: LAST ELEMENT
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Last element is selected as pivot

    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ---------------- HEAP SORT ----------------

// Heapify function
void heapify(int arr[], int n, int i) {
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

// ---------------- MAIN FUNCTION ----------------

int main() {

    int original[] = {8, 3, 5, 4, 7, 6, 1, 2};
    int n = 8;

    // Create separate copies of the same array
    int arr1[8], arr2[8], arr3[8];

    for (int i = 0; i < n; i++) {
        arr1[i] = original[i];
        arr2[i] = original[i];
        arr3[i] = original[i];
    }

    cout << "Original Array: ";
    display(original, n);

    // Calling Merge Sort
    cout << "\n--- Merge Sort ---\n";
    mergeSort(arr1, 0, n - 1);
    cout << "Sorted Array: ";
    display(arr1, n);

    // Calling Quick Sort
    cout << "\n--- Quick Sort ---\n";
    cout << "Pivot Strategy: Last Element\n";
    quickSort(arr2, 0, n - 1);
    cout << "Sorted Array: ";
    display(arr2, n);

    // Calling Heap Sort
    cout << "\n--- Heap Sort ---\n";
    heapSort(arr3, n);
    cout << "Sorted Array: ";
    display(arr3, n);

    return 0;
}

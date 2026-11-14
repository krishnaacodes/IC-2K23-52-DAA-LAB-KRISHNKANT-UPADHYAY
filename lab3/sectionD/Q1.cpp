
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

// 1. Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// 2. Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
}

// 3. Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

    int i = 0, j = 0, k = low;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// 5. Quick Sort
// Pivot selection strategy: LAST ELEMENT
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
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

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Heap Sort
void heapify(vector<int>& arr, int n, int i) {
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

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to measure execution time
template <typename Function>
double measureTime(Function sortFunction, vector<int> arr) {
    auto start = high_resolution_clock::now();

    sortFunction(arr);

    auto stop = high_resolution_clock::now();

    // Verify sorting correctness
    if (!is_sorted(arr.begin(), arr.end())) {
        cerr << "Sorting failed!\n";
        return -1;
    }

    duration<double, milli> elapsed = stop - start;

    return elapsed.count();
}

// Main Function
int main() {

    // Four input sizes
    int sizes[] = {100, 500, 1000, 2000};

    // Random number generator
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 10000);

    cout << fixed << setprecision(4);

    cout << "\n========== SORTING ALGORITHM COMPARISON ==========\n\n";

    cout << left
         << setw(18) << "Algorithm"
         << setw(15) << "Input Type"
         << setw(10) << "Size"
         << setw(15) << "Time (ms)"
         << endl;

    cout << string(58, '-') << endl;

    // Test each input size
    for (int n : sizes) {

        // Generate random array
        vector<int> randomArray(n);

        for (int i = 0; i < n; i++)
            randomArray[i] = dist(rng);

        // Generate sorted and reverse sorted arrays
        vector<int> sortedArray = randomArray;
        sort(sortedArray.begin(), sortedArray.end());

        vector<int> reverseArray = sortedArray;
        reverse(reverseArray.begin(), reverseArray.end());

        // Three input types
        vector<pair<string, vector<int>>> inputs = {
            {"Random", randomArray},
            {"Sorted", sortedArray},
            {"Reverse", reverseArray}
        };

        // Test each input type
        for (auto& input : inputs) {

            string type = input.first;
            vector<int> original = input.second;

            // Bubble Sort
            double t1 = measureTime(
                [](vector<int>& a) { bubbleSort(a); },
                original
            );

            cout << left << setw(18) << "Bubble Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t1 << endl;

            // Selection Sort
            double t2 = measureTime(
                [](vector<int>& a) { selectionSort(a); },
                original
            );

            cout << left << setw(18) << "Selection Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t2 << endl;

            // Insertion Sort
            double t3 = measureTime(
                [](vector<int>& a) { insertionSort(a); },
                original
            );

            cout << left << setw(18) << "Insertion Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t3 << endl;

            // Merge Sort
            double t4 = measureTime(
                [](vector<int>& a) {
                    mergeSort(a, 0, (int)a.size() - 1);
                },
                original
            );

            cout << left << setw(18) << "Merge Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t4 << endl;

            // Quick Sort
            double t5 = measureTime(
                [](vector<int>& a) {
                    quickSort(a, 0, (int)a.size() - 1);
                },
                original
            );

            cout << left << setw(18) << "Quick Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t5 << endl;

            // Heap Sort
            double t6 = measureTime(
                [](vector<int>& a) { heapSort(a); },
                original
            );

            cout << left << setw(18) << "Heap Sort"
                 << setw(15) << type
                 << setw(10) << n
                 << setw(15) << t6 << endl;
        }

        cout << string(58, '-') << endl;
    }

    cout << "\nTiming analysis completed successfully!\n";

    return 0;
}

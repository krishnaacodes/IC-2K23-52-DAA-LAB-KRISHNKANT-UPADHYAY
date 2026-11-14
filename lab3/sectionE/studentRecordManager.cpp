
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

// Student structure
struct Student {
    int roll;
    string name;
    float marks;
};

// Display student records
void display(vector<Student> students) {
    cout << "\nRoll No.\tName\t\tMarks\n";
    cout << "----------------------------------------\n";

    for (auto s : students) {
        cout << s.roll << "\t\t"
             << s.name << "\t\t"
             << s.marks << endl;
    }
}

// Compare students based on selected field
bool compareStudent(Student a, Student b, int field) {

    if (field == 1)
        return a.roll < b.roll;

    else if (field == 2)
        return a.name < b.name;

    else
        return a.marks < b.marks;
}

// 1. Bubble Sort
void bubbleSort(vector<Student>& a, int field) {
    int n = a.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (compareStudent(a[j + 1], a[j], field)) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// 2. Selection Sort
void selectionSort(vector<Student>& a, int field) {
    int n = a.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (compareStudent(a[j], a[minIndex], field))
                minIndex = j;
        }

        swap(a[i], a[minIndex]);
    }
}

// 3. Insertion Sort
void insertionSort(vector<Student>& a, int field) {
    int n = a.size();

    for (int i = 1; i < n; i++) {
        Student key = a[i];
        int j = i - 1;

        while (j >= 0 && compareStudent(key, a[j], field)) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// 4. Merge Sort
void merge(vector<Student>& a, int low, int mid,
           int high, int field) {

    vector<Student> left(a.begin() + low,
                         a.begin() + mid + 1);

    vector<Student> right(a.begin() + mid + 1,
                          a.begin() + high + 1);

    int i = 0, j = 0, k = low;

    while (i < left.size() && j < right.size()) {

        if (!compareStudent(right[j], left[i], field))
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    while (i < left.size())
        a[k++] = left[i++];

    while (j < right.size())
        a[k++] = right[j++];
}

void mergeSort(vector<Student>& a, int low,
               int high, int field) {

    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSort(a, low, mid, field);
        mergeSort(a, mid + 1, high, field);

        merge(a, low, mid, high, field);
    }
}

// 5. Quick Sort
// Pivot selection strategy: LAST ELEMENT
int partition(vector<Student>& a, int low,
              int high, int field) {

    Student pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (!compareStudent(pivot, a[j], field)) {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);

    return i + 1;
}

void quickSort(vector<Student>& a, int low,
               int high, int field) {

    if (low < high) {
        int pi = partition(a, low, high, field);

        quickSort(a, low, pi - 1, field);
        quickSort(a, pi + 1, high, field);
    }
}

// 6. Heap Sort
void heapify(vector<Student>& a, int n,
             int i, int field) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n &&
        compareStudent(a[largest], a[left], field))
        largest = left;

    if (right < n &&
        compareStudent(a[largest], a[right], field))
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest, field);
    }
}

void heapSort(vector<Student>& a, int field) {
    int n = a.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i, field);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0, field);
    }
}

// Binary Search by Roll Number
int binarySearch(vector<Student>& a, int roll) {

    int low = 0;
    int high = a.size() - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        if (a[mid].roll == roll)
            return mid;

        else if (a[mid].roll < roll)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

// Measure sorting time
template <typename Function>
double measureTime(Function sortFunction,
                   vector<Student> data) {

    auto start = high_resolution_clock::now();

    sortFunction(data);

    auto stop = high_resolution_clock::now();

    return duration<double, micro>(stop - start).count();
}

// Main Function
int main() {

    int n;

    cout << "Enter number of students: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of students.\n";
        return 0;
    }

    vector<Student> students(n);

    // Input student records
    cout << "\nEnter Student Details:\n";

    for (int i = 0; i < n; i++) {

        cout << "\nStudent " << i + 1 << endl;

        cout << "Roll Number: ";
        cin >> students[i].roll;

        cout << "Name: ";
        cin >> ws;
        getline(cin, students[i].name);

        cout << "Marks: ";
        cin >> students[i].marks;
    }

    vector<Student> original = students;

    int field, choice;

    cout << "\nSort Records By:\n";
    cout << "1. Roll Number\n";
    cout << "2. Name\n";
    cout << "3. Marks\n";

    cout << "Enter choice: ";
    cin >> field;

    if (field < 1 || field > 3) {
        cout << "Invalid sorting field.\n";
        return 0;
    }

    cout << "\nSelect Sorting Algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";
    cout << "6. Heap Sort\n";

    cout << "Enter choice: ";
    cin >> choice;

    if (choice < 1 || choice > 6) {
        cout << "Invalid algorithm choice.\n";
        return 0;
    }

    // Perform selected sorting algorithm
    switch (choice) {

        case 1:
            bubbleSort(students, field);
            break;

        case 2:
            selectionSort(students, field);
            break;

        case 3:
            insertionSort(students, field);
            break;

        case 4:
            mergeSort(students, 0, n - 1, field);
            break;

        case 5:
            quickSort(students, 0, n - 1, field);
            break;

        case 6:
            heapSort(students, field);
            break;
    }

    cout << "\nSorted Student Records:\n";
    display(students);

    // Binary search by roll number
    // Sort a separate copy by roll number first
    vector<Student> rollSorted = original;

    sort(rollSorted.begin(), rollSorted.end(),
         [](Student a, Student b) {
             return a.roll < b.roll;
         });

    int searchRoll;

    cout << "\nEnter Roll Number to Search: ";
    cin >> searchRoll;

    int result = binarySearch(rollSorted, searchRoll);

    if (result != -1) {
        cout << "\nStudent Found!\n";

        cout << "Roll Number: "
             << rollSorted[result].roll << endl;

        cout << "Name: "
             << rollSorted[result].name << endl;

        cout << "Marks: "
             << rollSorted[result].marks << endl;
    }
    else {
        cout << "\nStudent Not Found!\n";
    }

    // Performance comparison
    cout << "\n--- Sorting Performance Comparison ---\n";

    double times[6];

    times[0] = measureTime(
        [&](vector<Student>& a) {
            bubbleSort(a, field);
        }, original
    );

    times[1] = measureTime(
        [&](vector<Student>& a) {
            selectionSort(a, field);
        }, original
    );

    times[2] = measureTime(
        [&](vector<Student>& a) {
            insertionSort(a, field);
        }, original
    );

    times[3] = measureTime(
        [&](vector<Student>& a) {
            mergeSort(a, 0, (int)a.size() - 1, field);
        }, original
    );

    times[4] = measureTime(
        [&](vector<Student>& a) {
            quickSort(a, 0, (int)a.size() - 1, field);
        }, original
    );

    times[5] = measureTime(
        [&](vector<Student>& a) {
            heapSort(a, field);
        }, original
    );

    string names[] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
        "Heap Sort"
    };

    int fastest = 0;
    int slowest = 0;

    cout << fixed << setprecision(3);

    cout << "\nAlgorithm\t\tTime (microseconds)\n";
    cout << "------------------------------------------\n";

    for (int i = 0; i < 6; i++) {

        cout << left << setw(22) << names[i]
             << times[i] << endl;

        if (times[i] < times[fastest])
            fastest = i;

        if (times[i] > times[slowest])
            slowest = i;
    }

    cout << "\nFastest Algorithm: "
         << names[fastest] << endl;

    cout << "Slowest Algorithm: "
         << names[slowest] << endl;

    cout << "Time Difference: "
         << times[slowest] - times[fastest]
         << " microseconds\n";

    return 0;
}

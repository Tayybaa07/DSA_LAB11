#include <iostream>
using namespace std;

long long gComparisons = 0;  // counts arr[j] <= pivot checks
bool gTrace = false;         // print each partition step
int gSize = 0;

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

void swapInts(int& a, int& b) { int t = a; a = b; b = t; }

//partition: pivot = arr[high]. Returns pivot's final index.
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                 // end of the "<= pivot" region

    for (int j = low; j < high; j++) {
        gComparisons++;
        if (arr[j] <= pivot) {
            i++;
            swapInts(arr[i], arr[j]);
        }
    }
    swapInts(arr[i + 1], arr[high]); // put pivot in its final place
    int pi = i + 1;

    if (gTrace) {
        cout << "  partition [" << low << ".." << high << "] pivot=" << pivot
             << " pi=" << pi << " -> ";
        printArray(arr, gSize);
        cout << endl;
    }
    return pi;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);     // pi excluded from both sides
        quickSort(arr, pi + 1, high);
    }
}

// Sorts a copy of input; prints trace, result and comparison count
void runTest(const char* title, const int input[], int n, bool trace) {
    cout << "  " << title << "  " << endl;
    int* arr = new int[n > 0 ? n : 1];
    for (int i = 0; i < n; i++) arr[i] = input[i];
    gSize = n;
    gComparisons = 0;
    gTrace = trace;

    cout << "Before: "; printArray(arr, n); cout << endl;
    quickSort(arr, 0, n - 1);
    cout << "After:  "; printArray(arr, n); cout << endl;
    cout << "Total comparisons (arr[j] <= pivot): " << gComparisons << endl << endl;

    delete[] arr;
}

// trace of the first partition pass of {2,1,5,4,6,3} showing i, j, swaps
void traceFirstPass() {
    int a[] = {2, 1, 5, 4, 6, 3};
    int low = 0, high = 5;
    int pivot = a[high];
    int i = low - 1;
    cout << " First partition pass trace of {2,1,5,4,6,3}, pivot = " << pivot << "  " << endl;
    for (int j = low; j < high; j++) {
        cout << "  j=" << j << " arr[j]=" << a[j];
        if (a[j] <= pivot) {
            i++;
            cout << " <= " << pivot << " -> i=" << i << ", swap arr[" << i << "] and arr[" << j << "]";
            swapInts(a[i], a[j]);
        } else {
            cout << " >  " << pivot << " -> no swap (i=" << i << ")";
        }
        cout << "  => "; printArray(a, 6); cout << endl;
    }
    swapInts(a[i + 1], a[high]);
    cout << "  Final: swap arr[" << i + 1 << "] with arr[" << high << "] -> ";
    printArray(a, 6);
    cout << "  pi = " << i + 1 << endl << endl;
}

int main() {
    int t1[]   = {2, 1, 5, 4, 6, 3};
    int t2[]   = {35, 12, 43, 8, 51, 27, 19};
    int rnd[]  = {5, 1, 4, 2, 8};
    int srt[]  = {1, 2, 4, 5, 8};
    int rev[]  = {8, 5, 4, 2, 1};
    int same[] = {7, 7, 7, 7, 7};
    int one[]  = {9};
    int none[] = {0};

    // Part 1: step-by-step partition traces
    runTest("Trace {2,1,5,4,6,3}", t1, 6, true);
    runTest("Trace {35,12,43,8,51,27,19}", t2, 7, true);

    // Part 2: comparison counts
    runTest("Random order {5,1,4,2,8}", rnd, 5, false);
    runTest("Already sorted {1,2,4,5,8}", srt, 5, false);
    runTest("Reverse sorted {8,5,4,2,1}", rev, 5, false);
    runTest("Repeated values {7,7,7,7,7}", same, 5, false);
    runTest("Single element (n = 1)", one, 1, false);
    runTest("Empty array (n = 0)", none, 0, false);

    // Demonstration check
    traceFirstPass();

    return 0;
}
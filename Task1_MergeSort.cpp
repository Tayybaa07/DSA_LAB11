#include <iostream>
using namespace std;

// Prints arr[0..n-1] on one line
void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

// Globals used only for tracing inside merge()
int gSize = 0;       // total size of the array 
bool gTrace = true;  // turn step printing on/off

// Merges two adjacent sorted subarrays arr[low..mid] and arr[mid+1..high]
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;   // size of left half
    int n2 = high - mid;      // size of right half

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    // Two pointer merge; <= keeps equal elements in original order (stable)
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    // Copy leftovers
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;

    if (gTrace) {
        cout << "  merge [" << low << ".." << high << "] -> ";
        printArray(arr, gSize);
        cout << endl;
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low >= high) return;            // 0 or 1 element
    int mid = low + (high - low) / 2;   // overflow safe midpoint
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

// Runs one test case: prints before, trace, after
void runTest(const char* title, const int input[], int n) {
    cout << " "  << title << " " << endl;
    int* arr = new int[n > 0 ? n : 1];   // safe even when n = 0
    for (int i = 0; i < n; i++) arr[i] = input[i];
    gSize = n;

    cout << "Before: "; printArray(arr, n); cout << endl;
    mergeSort(arr, 0, n - 1);
    cout << "After:  "; printArray(arr, n); cout << endl << endl;

    delete[] arr;
}

int main() {
    int main_data[] = {35, 12, 43, 8, 51, 27, 19};
    int sorted[]    = {1, 2, 4, 5, 8};
    int reversed[]  = {8, 5, 4, 2, 1};
    int dups[]      = {5, 2, 5, 1, 2};
    int single[]    = {42};
    int empty[]     = {0};   // placeholder, n = 0 so never read

    runTest("Main example {35,12,43,8,51,27,19}", main_data, 7);
    runTest("Already sorted", sorted, 5);
    runTest("Reverse sorted", reversed, 5);
    runTest("Repeated values", dups, 5);
    runTest("Single element (n = 1)", single, 1);
    runTest("Empty array (n = 0)", empty, 0);

    return 0;
}
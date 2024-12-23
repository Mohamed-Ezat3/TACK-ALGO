#include <iostream>
#include <vector>

using namespace std;

// Function to heapify a subtree rooted at index `i`
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;          // Initialize largest as root
    int left = 2 * i + 1;     // Left child
    int right = 2 * i + 2;    // Right child

    // Check if left child exists and is greater than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Check if right child exists and is greater than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap and continue heapifying if root is not the largest
    if (largest != i) {
        swap(arr[i], arr[largest]);  // Swap
        heapify(arr, n, largest);   // Recursively heapify the affected subtree
    }
}

// Main function to perform heap sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move the current root to the end
        swap(arr[0], arr[i]);

        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

// Helper function to print an array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {4, 10, 3, 5, 1};

    cout << "Original array: ";
    printArray(arr);

    heapSort(arr);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}

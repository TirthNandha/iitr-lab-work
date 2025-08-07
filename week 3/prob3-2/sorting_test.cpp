#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <climits>

using namespace std;
using namespace std::chrono;

class SortingAlgorithms {
private:
    vector<int> data;
    
public:
    SortingAlgorithms(int size) {
        // Initialize random seed as specified
        unsigned int seed = time(NULL);
        srand(seed);
        
        // Generate random data
        data.resize(size);
        for (int i = 0; i < size; i++) {
            data[i] = rand() % 100000; // Random numbers 0-99999
        }
    }
    
    vector<int> getData() { return data; }
    
    // Merge Sort Implementation
    void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<int> leftArr(n1), rightArr(n2);
        
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    // Quick Sort Implementation
    void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    
    // Randomized Quick Sort Implementation
    void randomizedQuickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = randomizedPartition(arr, low, high);
            randomizedQuickSort(arr, low, pi - 1);
            randomizedQuickSort(arr, pi + 1, high);
        }
    }
    
    int randomizedPartition(vector<int>& arr, int low, int high) {
        int random = low + rand() % (high - low);
        swap(arr[random], arr[high]);
        return partition(arr, low, high);
    }
    
    // Heap Sort Implementation
    void heapSort(vector<int>& arr) {
        int n = arr.size();
        
        // Build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
        
        // Extract elements one by one
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
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
    
    // Bubble Sort Implementation
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    
    // Selection Sort Implementation
    void selectionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
            swap(arr[min_idx], arr[i]);
        }
    }
    
    // Function to run specific algorithm
    double runAlgorithm(string algorithm) {
        vector<int> testData = data; // Copy original data
        
        auto start = high_resolution_clock::now();
        
        if (algorithm == "merge" || algorithm == "MERGE") {
            mergeSort(testData, 0, testData.size() - 1);
        }
        else if (algorithm == "quick" || algorithm == "QUICK") {
            quickSort(testData, 0, testData.size() - 1);
        }
        else if (algorithm == "randomized_quick" || algorithm == "RANDOMIZED_QUICK") {
            randomizedQuickSort(testData, 0, testData.size() - 1);
        }
        else if (algorithm == "heap" || algorithm == "HEAP") {
            heapSort(testData);
        }
        else if (algorithm == "bubble" || algorithm == "BUBBLE") {
            bubbleSort(testData);
        }
        else if (algorithm == "selection" || algorithm == "SELECTION") {
            selectionSort(testData);
        }
        else {
            cerr << "Unknown algorithm: " << algorithm << endl;
            return -1;
        }
        
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        
        return duration.count() / 1000000.0; // Convert to seconds
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <algorithm> <size>" << endl;
        cout << "Algorithms: merge, quick, randomized_quick, heap, bubble, selection" << endl;
        return 1;
    }
    
    string algorithm = argv[1];
    int size = atoi(argv[2]);
    
    if (size <= 0) {
        cerr << "Error: Size must be positive" << endl;
        return 1;
    }
    
    // Create sorting object with random data
    SortingAlgorithms sorter(size);
    
    // Run the algorithm and measure time
    double executionTime = sorter.runAlgorithm(algorithm);
    
    if (executionTime >= 0) {
        // Output in the format expected by the bash script
        cout << "Time: " << executionTime << endl;
        
        // Estimate memory usage (rough approximation)
        // For most algorithms: input array + some overhead
        int memoryUsage = size * sizeof(int) / 1024; // Convert to KB
        
        // Merge sort uses additional O(n) space
        if (algorithm == "merge" || algorithm == "MERGE") {
            memoryUsage *= 2;
        }
        
        cout << "Memory: " << memoryUsage << endl;
        
        // Optional: Print algorithm and size info
        cout << "Algorithm: " << algorithm << endl;
        cout << "Size: " << size << endl;
    }
    
    return 0;
}
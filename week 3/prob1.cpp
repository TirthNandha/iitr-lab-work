#include<iostream>

#include<vector>

// #include<cstdlib>

#include<ctime>

using namespace std;

void bubbleSort(vector < int > & a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void selectionSort(vector < int > & a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        swap(a[i], a[minIndex]);
    }
}

void merge(vector < int > & a, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector < int > L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int i = 0; i < n2; i++) R[i] = a[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(vector < int > & a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int partition(vector < int > & a, int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector < int > & a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int randomPartition(vector < int > & a, int low, int high) {
    int randIdx = low + rand() % (high - low + 1);
    swap(a[randIdx], a[high]);
    return partition(a, low, high);
}

void randomizedQuickSort(vector < int > & a, int low, int high) {
    if (low < high) {
        int pi = randomPartition(a, low, high);
        randomizedQuickSort(a, low, pi - 1);
        randomizedQuickSort(a, pi + 1, high);
    }
}

void heapify(vector < int > & a, int n, int i) {
    int big = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l] > a[big]) big = l;
    if (r < n && a[r] > a[big]) big = r;
    if (big != i) {
        swap(a[i], a[big]);
        heapify(a, n, big);
    }
}

void heapSort(vector < int > & a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cout << "Usage: ./prob1 <num_elements>\n";
        return 1;
    }

    int n = atoi(argv[1]);
    vector < int > temp(n);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        temp[i] = rand() % 100000;

    cout << "original array:\n";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";
    cout << "\n";

    #ifdef BUBBLE
    cout << "using bubble sort\n";
    bubbleSort(temp);
    #elif SELECTION
    cout << "using selection sort\n";
    selectionSort(temp);
    #elif MERGE
    cout << "using merge sort\n";
    mergeSort(temp, 0, n - 1);
    #elif QUICK
    cout << "using quick sort\n";
    quickSort(temp, 0, n - 1);
    #elif RQUICK
    cout << "using randomized quick sort\n";
    randomizedQuickSort(temp, 0, n - 1);
    #elif HEAP
    cout << "using heap sort\n";
    heapSort(temp);
    #else
    cout << "No algo defined\n";
    return 1;
    #endif

    cout << "sorted array:\n";
    for (int i = 0; i < n; i++) cout << temp[i] << " ";
    cout << "\n";

    return 0;
}
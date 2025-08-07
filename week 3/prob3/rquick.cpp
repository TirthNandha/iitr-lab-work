#include <bits/stdc++.h>
using namespace std;

int customPartition(vector<int>& arr, int low, int high);

int randomizedPartition(vector<int>& arr, int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    return customPartition(arr, low, high);
}

int customPartition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    int n = stoi(argv[1]);
    srand(time(NULL));
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand();
    randomizedQuickSort(arr, 0, n - 1);
    return 0;
}

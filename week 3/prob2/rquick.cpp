#include <bits/stdc++.h>
using namespace std;

int myPartition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return myPartition(arr, low, high);
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

int main(int argc, char* argv[]) {
    int n = stoi(argv[1]);
    srand(time(NULL));
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand();
    quickSort(arr, 0, n-1);
    return 0;
}

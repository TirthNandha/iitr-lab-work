#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    int n = stoi(argv[1]);
    srand(time(NULL));
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand();
    bubbleSort(arr, n);
    return 0;
}
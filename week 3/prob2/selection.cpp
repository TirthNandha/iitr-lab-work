#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int>& arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int min_i = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_i])
                min_i = j;
        swap(arr[i], arr[min_i]);
    }
}

int main(int argc, char* argv[]) {
    int n = stoi(argv[1]);
    srand(time(NULL));
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand();
    selectionSort(arr, n);
    return 0;
}

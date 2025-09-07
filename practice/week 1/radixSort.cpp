#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void countingSortByDigit(vector<int>& arr, int n, int exp) {
    vector<int> output(n);
    vector<int> count(10, 0);

    // Count occurrences of each digit at current place
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Convert count to prefix sum (cumulative count)
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array (stable sorting by current digit)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back to original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(vector<int>& arr, int n) {
    if (n == 0) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    // Apply counting sort for each digit (exp = 1, 10, 100, ...)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, n, exp);
    }
}

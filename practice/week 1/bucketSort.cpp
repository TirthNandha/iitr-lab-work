#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(vector<float>& arr, int n) {
    if (n == 0) return;

    // Create n empty buckets
    vector<vector<float>> buckets(n);

    // Put array elements into buckets
    for (int i = 0; i < n; i++) {
        int index = n * arr[i];  // index based on value
        buckets[index].push_back(arr[i]);
    }

    // Sort individual buckets
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Concatenate all buckets back into arr
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (float val : buckets[i]) {
            arr[idx++] = val;
        }
    }
}

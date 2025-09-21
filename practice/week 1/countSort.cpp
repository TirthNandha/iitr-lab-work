#include <iostream>
#include <vector>
using namespace std;

vector<int> countSort(vector<int>&arr, int n){
    int maxElem = 0;
    for(int num:arr) {
        if (num>maxElem){
            maxElem = num;
        }
    }
    vector<int> count(maxElem+1, 0);

    for(int num: arr){
        count[num]++;
    }

    for(int i = 1; i < maxElem+1; i++){
        count[i] += count[i-1];
    }

    vector<int> ans(n);
    for(int i = n-1; i>=0; i--){
        ans[count[arr[i]] -1] = arr[i];
        count[arr[i]]--;
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i =0; i<n; i++){
        cin >> arr[i];
    }
    arr = countSort(arr, n);
    for(int num: arr){
        cout << num;
    }
}
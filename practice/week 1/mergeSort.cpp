#include<iostream>
#include<vector>
using namespace std;

void merge(vector<int>& arr, int low, int mid, int high){
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++){
        L[i] = arr[low + i];
    }
    for(int j = 0; j< n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    int i =0, j = 0, k = low;
    while(i<n1 && j < n2){
        if(L[i]<= R[j]){
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    while(i < n1) {
        arr[k++] = L[i++];
    }
    while(j < n2){
        arr[k++] = R[j++];
    }

}

void mergeSort(vector<int>& arr, int low, int high){
    if(low >= high){
        return;
    }
    int mid = low + (high-low)/2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main(){
    int n;
    cout << "Enter n:" << endl;
    cin >> n;
    int k;
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for(int i= 0; i<n;i++){
        cin >> arr[i];
    }
    mergeSort(arr, 0, n-1);
    for(int num: arr){
        cout << num << " ";
    }

}
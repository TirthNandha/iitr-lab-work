#include<iostream>
#include<vector>
using namespace std;

int partition(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
        if (arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high){
    if(low >= high){
        return;
    }
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
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
    quickSort(arr, 0, n-1);
    for(int num: arr){
        cout << num << " ";
    }

}
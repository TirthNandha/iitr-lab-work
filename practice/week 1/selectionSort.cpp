#include<iostream>
#include<vector>
using namespace std;

void selectionSort(vector<int>& arr, int n){
    for(int i = 0; i< n-1; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
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
    selectionSort(arr, n);
    for(int num: arr){
        cout << num << " ";
    }

}
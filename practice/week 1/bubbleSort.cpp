#include<iostream>
#include<vector>
using namespace std;

void bubbleSort(vector<int>& arr, int n){
    for(int i = n; i>0; i--) {
        bool swapped = false;
        for(int j = 0; j < i - 1; j++) {
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
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
    bubbleSort(arr, n);
    for(int num: arr){
        cout << num << " ";
    }

}
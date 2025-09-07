#include<iostream>
#include<vector>
using namespace std;

int binarySearch(vector<int>& arr, int k){
    int i = 0;
    int j = arr.size() - 1;
    int ans = -1;
    while(i<=j){
        int mid = i + (j-i)/2;
        if(arr[mid]<=k){
            ans = arr[mid];
            i = mid+1;
        }
        else{
            j = mid-1;
        }
    }
    return ans;

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
    cout << "Enter k: " << endl;
    cin >> k;
    cout << binarySearch(arr, k);
}
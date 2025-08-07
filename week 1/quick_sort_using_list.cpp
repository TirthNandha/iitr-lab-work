#include <iostream>
#include <list>
using namespace std;


void quickSort(list<int>& lst) {
    if (lst.size() <= 1) return;

    int pivot = lst.front();
    lst.pop_front();

    list<int> left, right;
    for (int val : lst) {
        if (val <= pivot) left.push_back(val);
        else right.push_back(val);
    }

    quickSort(left);
    quickSort(right);

    lst.clear();
    lst.splice(lst.end(), left);
    lst.push_back(pivot);
    lst.splice(lst.end(), right);
}

int main()
{
    list<int> arr = {-30, 9, 29, 60};
    quickSort(arr);
    
    
    for(int num: arr){
        cout << num << endl;
    }

    return 0;
}
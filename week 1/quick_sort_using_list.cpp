#include <iostream>
#include <list>
using namespace std;


list<int> quickSort(list<int>& lst) {
    if(lst.size()<=1) return lst;

    list<int> less, equal, greater;

    int pivot = lst.front();

    //partitioning
    for(int num: lst){
        if(num< pivot) less.push_back(num);
        else if(num > pivot) greater.push_back(num);
        else equal.push_back(num);
    }

    less = quickSort(less);
    greater = quickSort(greater);

    list<int> result;
    result.splice(result.end(), less);
    result.splice(result.end(), equal);
    result.splice(result.end(), greater);

    return result;
}

int main()
{
    list<int> arr = {5 , -30, 20, 6, 8, 2};
    cout << "Original List: " << endl;
    for(int num: arr){
        cout << num << endl;
    }
    list<int> result = quickSort(arr);
    cout << "Sorted list: " << endl;
    for(int num: result){
        cout << num << endl;
    }
    

    return 0;
}
#include <iostream>
#include <list>
using namespace std;

list<int> mergeLists(list<int>& left, list<int>& right) {
    list<int> result;
    auto it1 = left.begin();
    auto it2 = right.begin();

    while (it1 != left.end() && it2 != right.end()) {
        if (*it1 <= *it2) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    // Copy remaining elements
    while (it1 != left.end()) result.push_back(*it1++);
    while (it2 != right.end()) result.push_back(*it2++);
    return result;
}

list<int> mergeSort(list<int>& lst) {
    if (lst.size() <= 1) return lst; // base case

    auto mid = lst.begin();
    advance(mid, lst.size() / 2); // find middle iterator

    list<int> left(lst.begin(), mid);
    list<int> right(mid, lst.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return mergeLists(left, right);
}

int main() {
    list<int> lst = {4, 2, 7, 1, 5, 3};
    lst = mergeSort(lst);

    for (int x : lst) cout << x << " ";
}

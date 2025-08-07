#include <iostream>
#include <list>
using namespace std;


void mergeSort(list<int>& lst) {
	if (lst.size() <= 1) return;
	auto it = lst.begin();
	advance(it, lst.size()/2);
	list<int> left, right;

	left.splice(left.end(), lst, lst.begin(), it);
	right.splice(right.end(), lst, lst.begin(), lst.end());

	mergeSort(left);
	mergeSort(right);

	lst.clear();

	auto it1 = left.begin(), it2 = right.begin();

	while(it1 != left.end() && it2 != right.end()) {
		if(*it1< *it2) {
			lst.splice(lst.end(), left, it1++);
		}
		else {
			lst.splice(lst.end(), right, it2++);
		}
	}

	lst.splice(lst.end(), left);
	lst.splice(lst.end(), right);

}

int main()
{
	list<int> lst = {9, -30, 29, 60};
	mergeSort(lst);

	for(int num: lst) {
		cout << num << endl;
	}

	return 0;
}
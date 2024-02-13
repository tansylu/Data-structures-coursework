#include <vector>
#include <iostream>
using namespace std;

template <class objectType>
class InsertionSort {

public:
	InsertionSort() {
		
	}
	void sort(vector<objectType>& v);
	
};


template <class objectType>
void InsertionSort<objectType>::sort(vector<objectType>& v) {
	
	for (int i = 1; i < v.size(); i++) {

		objectType current = v[i];
		int k = i;
		int s = -1;
		while (k >0) {
			if (current < v[k - 1]) {
				v[k] = v[k - 1];
				v[k - 1] = current;
			}
			k--;
		}

	}
};

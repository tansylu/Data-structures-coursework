#include <vector>
#include <iostream>
using namespace std;

template <class objectType>
class QuickSort {
private:
	vector<objectType> input_v;

public:
	QuickSort() {

	
	}
	void partition(vector<objectType>& v, int start, int end);
	
};


template <class objectType>
void QuickSort<objectType>::partition(vector<objectType>& v, int start, int end) {
	if (start >= end) {
		return; 
	}
	int i = start, j = end;
	objectType temp;
	objectType pivot = v[(start + end) / 2];

	while (i <= j) {
		while (v[j] > pivot) {//go from end of vector until a value <= pivot(skipp all that are greater)
			j--;
		}
		while (v[i] < pivot) {//go from start of vector until a value >= pivot(skipp all that are smaller)
			i++;
		}

		if (i <= j) {//we are in the middle
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;//swap v[i] and v[j]
			i++;
			j--;
		}
	};

	if (start < j) {
		partition(v, start, j);
	}

	if (i < end) {
		partition(v, i, end);
	}

};

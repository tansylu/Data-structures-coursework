#include <vector>
#include <iostream>
using namespace std;

template <class objectType>
class HeapSort {
private:
	vector<objectType> input_v;

public:
	HeapSort() {

	
	}
	void buildheap(vector<objectType> &v,int my_size, int root);
	void placement(vector<objectType> &heap);

};


template <class objectType>
void HeapSort<objectType>::buildheap(vector<objectType>& v, int  my_size, int root) {

    int maks = root;

    int r_child = 2 * root + 2;
    int l_child = 2 * root + 1;

    

    if (l_child < my_size && v[l_child] > v[maks]) {
        maks = l_child;
    }

   
    if (r_child < my_size && v[r_child] > v[maks]) {
        maks = r_child;
    }

    if (maks != root) {
        swap(v[root], v[maks]);

        buildheap(v, my_size,maks);
    }
		
};

template <class objectType>
void HeapSort<objectType>::placement(vector<objectType> &v)
{
    int my_size = v.size();
    for (int k = my_size / 2 - 1; k >= 0; k--)
        buildheap(v, my_size, k);

   
    for (int s = my_size - 1; s > 0; s--) {
        objectType tmp = v[0];
        v[0] = v[s];
        v[s] = tmp;
      
        buildheap(v, s, 0);
    }
}
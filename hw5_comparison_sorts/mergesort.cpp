#include <vector>
using namespace std;

template <class objectType>
class MergeSort {
public:
    void split(vector<objectType>& v) {
        int my_size = v.size();

        for (int k = 1; k < my_size; k *= 2) {
            for (int i = 0; i < my_size; i += 2 * k) {
                int left = i;
                int mid = min(i + k - 1, my_size - 1);
                int right = min(i + 2 * k - 1, my_size - 1);
                merge(v, left, mid, right);
            }
        }
    }

    void merge(vector<objectType>& v, int left, int mid, int right) {
     
        int right_start = mid + 1;
        int right_end = right;
        int left_start = left;
        int left_end = mid;

        while (right_start <= right_end && left_start <= left_end  ) {
            if (v[left_start] < v[right_start] || v[left_start] == v[right_start]) {
                left_start++;
            }
            else {
                objectType temp = v[right_start];
                int index = right_start;

                while (index != left_start) {
                    v[index] = v[index - 1];
                    index--;
                }

                v[left_start] = temp;
                left_start++;
                left_end++;
                right_start++;
            }
        }
    }
};

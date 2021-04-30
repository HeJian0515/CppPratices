#include <vector>
#include <string>

#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>

using namespace std;
// 数组中的第K个最大元素

void quickSortOrigin(int *arr, int begin, int end) {
    srand(time(0));
    if (begin < end) {
        int q  = rand() % (end - begin + 1) + begin; // 选取一个数作为基准数
        int temp = arr[q];
        swap(arr[begin], arr[q]);  // 将基准数放到数组起始位置

        int i = begin;  // 指示当前左位置
        int j = end;  // 指示当前右位置 

        while (i < j) {
            // 当右边的数大于基准数时，略过，继续向左查找
            // 不满足条件时跳出循环，此时的j对应元素是小于基准元素的
            while (i<j && arr[j] > temp) {
                j--;
            }
            // 将右边小于等于基准元素的数填入右边相应位置
            arr[i] = arr[j];
            // 当左边的数小于等于基准数时，略过，继续向右查找
            // (重复的基准元素集合到左区间)
            // 不满足条件时跳出循环，此时的i对应的元素是大于等于基准元素的
            while (i<j && arr[i] <= temp) {
                i++;
            }
            //将左边大于基准元素的数填入左边相应位置
            arr[j] = arr[i];

        }
        arr[i] = temp;
         // 继续排序左区间
        quickSortOrigin(arr, begin, i-1);
        // 继续排序右区间
         quickSortOrigin(arr, i+1, end);
    }
}

namespace _215findKthLargest {

inline int partition(vector<int>& a, int l, int r)
{
    int x = a[r], i = l - 1;
    for (int j = l; j < r; ++j) {
        if (a[j] <= x) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i+1], a[r]);
    return i+1;
}

inline int randomPartition(vector<int>& a, int l, int r) {
    int i = rand() % (r - l + 1) + l;
    swap(a[i], a[r]);
    return partition(a, l, r);
}

int quickSelect(vector<int>& a, int l, int r, int index) {
   int q = randomPartition(a, l, r);
   if (q == index) {
       return a[q];
   } else {
       return q < index ? quickSelect(a, q+1, r, index) : quickSelect(a, l, q-1, index);
   }
}

int findKthLargest(vector<int>& nums, int k) {
    // srand(time(0));
    // return quickSelect(nums, 0, nums.size()-1, nums.size()-k);
    nth_element(nums.begin(), nums.end() - k, nums.end());
    return nums[nums.size() - k];
}
}
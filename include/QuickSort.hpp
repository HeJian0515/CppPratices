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
int QuickSort(vector<int>& nums, int l, int r)
{
    int randIndex = l + rand()%(r-l+1);
    int pivot = nums[randIndex];
    swap(nums[l], nums[randIndex]);

    while (l < r)
    {
        while (l < r && nums[r] > pivot) {
            --r;
        }
        nums[l] = nums[r];

        while (l < r && nums[l] <= pivot) {
            ++l;
        }
        nums[r] = nums[l];
    }

    nums[l] = pivot;
    return l;
}
int findKthLargest_1(vector<int>& nums, int k)
{   
    int n = nums.size();
    k = n - k;
    srand(time(NULL));
    int l = 0, r = n-1;
    for (;;)
    {
        int pos = QuickSort(nums, l, r);
        if (pos == k) {
            return nums[pos];
        } else if (pos < k) {
            l = pos+1;
        } else {
            r = pos-1;
        }
    }
    return -1;
}

int findKthLargest(vector<int>& nums, int k) {
    // srand(time(0));
    // return quickSelect(nums, 0, nums.size()-1, nums.size()-k);
    nth_element(nums.begin(), nums.end() - k, nums.end());
    return nums[nums.size() - k];
}
}


// 荷兰国旗问题
namespace __78sortColors
{
void sortColor(vector<int>& nums)
{
    // l维护[0, ..., 0)的右边界
    // r维护(2, ..., 2]的左边界
    int l = 0, r = nums.size()-1; 
    int curr = 0;

    while (curr <= r)
    {   
        while (curr <= r && nums[curr] == 2) {
            swap(nums[curr], nums[r]);
            --r;
        }
        if (nums[curr] == 0) {
            swap(nums[curr], nums[l]);
            ++l;
        }
        ++curr;
    }
}
}

// 摆动数组II
namespace _324wiggleSort
{
void wiggleSort(vector<int>& nums)
{
    int n = nums.size();
    
    auto midIt = next(nums.begin(), n/2);
    nth_element(nums.begin(), midIt, nums.end());

    int mid = *midIt;

    #define A(i) nums[(1+2*(i)) % (n|1)]

    int l = 0, k = 0, r = n-1;
    while (k <= r)
    {
        while (k <= r && A(k) < mid) {
            swap(A(k), A(r));
            --r;
        }
        if (A(k) > mid) {
            swap(A(k), A(l));
            ++l;
        }
        ++k;
    }
}
}
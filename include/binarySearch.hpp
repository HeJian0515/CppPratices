#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;


namespace _69MySqrt{
int mySqrt(int x) {
    if (x <= 1) return x;
    int low = 1;
    int high = x;
    
    while (low <= high) {
        int mid = low + (high - low) >> 2;
        int sqrt = x / mid;
        if (sqrt == mid) {
            return mid;
        } else if (mid > sqrt) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return high;
}
}

namespace _875minEatingSpeed {

inline int TimeOf(int n, int speed) {
    return (n / speed) + ((n % speed > 0) ? 1 : 0);
}

bool CanFinish(const vector<int>& piles, int speed, int h)
{
    int time = 0;
    for (int n : piles) {
        time += TimeOf(n, speed);
    }
    return time <= h;
}

int minEatingSpeed(vector<int>& piles, int h)
{
    int left = 1;
    int right = (*std::max_element(piles.cbegin(), piles.cend())) + 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (CanFinish(piles, mid, h)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
}

namespace _1011shipWithinDay
{

// 如果载重为cap，能否在D天内运完货物
bool canFinish(const vector<int>& ws, int d, int cap) {
    int i = 0;
    for (int day = 0; day < d; ++day) {
        int maxCap = cap;
        while ((maxCap -= ws[i]) >= 0) {
            ++i;
            if (i == ws.size()) return true;
        }
    }
    return false;
}

int shipWithinDays(vector<int>& weights, int D) {
    int left = *(std::max_element(weights.cbegin(), weights.cend()));
    int right = std::accumulate(weights.cbegin(), weights.cend(), 0) + 1;
    while (left < right) {
        int mid = left + (right - left)/2;
        if (canFinish(weights, D, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
}

// 搜索旋转排序数组 II
namespace _81search
{
bool search(vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target)
        return true;

        if (nums[mid] == nums[r]) { // 不能判断哪一边递增
            --r;
        } else if (nums[mid] < nums[r]) { // 右边是单调递增的
            if (target > nums[mid] && target <= nums[r]) { // 目标在单调区间里
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        } else { // 左边是单调递增的
            if (target >= nums[l] && target < nums[mid]) { // 目标在单调区间里
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }
    return false;
}
}

namespace _540singleNonDuplicate
{
int singleNonDuplicate(vector<int>& nums)
{
    int l = 0, r = nums.size()-1;
    
    while (l < r)
    {
        int mid = l + (r-l)/2;
        if (mid % 2 == 1) --mid; // 保证mid是偶数

        if (nums[mid] != nums[mid+1]) {
            r = mid;
        } else {
            l = mid+2;
        }
    }
    return nums[l];
}
}

namespace _4findMedianSortedArrays
{
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k)
{
    int m = nums1.size();
    int n = nums2.size();
    int index1 = 0, index2 = 0; // 区间的开头位置

    while (true)
    {
        // 边界情况
        if (index1 == m) {
            return nums2[index2 + k - 1];
        }
        if (index2 == n) {
            return nums1[index1 + k -1];
        }
        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        // 正常情况
        int newIndex1 = min(index1+k/2-1, m-1); // 将区间右边前进k/2-1
        int newIndex2 = min(index2+k/2-1, n-1);

        int pivot1 = nums1[newIndex1];
        int pivot2 = nums2[newIndex2];

        if (pivot1 <= pivot2) {
            k -= newIndex1 - index1 + 1;
            index1 = newIndex1+1;
        } else {
            k -= newIndex2 - index2 + 1;
            index2 = newIndex2 + 1;
        }
    }
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    int totalLen = nums1.size() + nums2.size();
    if (totalLen % 2 == 1) {
        return getKthElement(nums1, nums2, (totalLen+1)/2);
    } else {
        return (getKthElement(nums1, nums2, totalLen/2) + getKthElement(nums1, nums2, totalLen/2+1)) / 2.0;
    }

}
}
#pragma once 
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

namespace _350Array { //! 350. 两个数组的交集 II
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < 1 || nums2.size() < 1) return {};
        unordered_map<int, int> m1;
        for (int i : nums1) {
            ++m1[i]; // 记录nums1中元素及其个数个数
        }
        vector<int> res;
        for (int i : nums2) {
            if(m1.count(i)) { // 如果m1中含有nums2中的元素i
                res.push_back(i);
                --m1[i]; // 将其计数减一
                if (m1[i] == 0) {
                    m1.erase(i);
                }
            }
        }
        return res;
    }
    // 排好序了的
    vector<int> intersect2(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < 1 || nums2.size() < 1) return {};
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());

        int i = 0, j = 0;
        vector<int> res;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] > nums2[j]) {
                ++j;
            } else if(nums1[i] < nums2[j]) {
                ++i;
            } else {
                res.push_back(nums1[i]);
                ++i;
                ++j;
            }
        }
        return res;
    }
}

namespace _410splitArray {
//! 将一个数组分成m段非空连续子数组， 使m个子数组和的最大值最小
//* 动态规划 f[i][j]表示将数组的前i个数分割为j段，所能得到的最大连续子数组和的最小值
//* f[i][j] = min|(k=0:i-1){max(f[k][j-1], sub(k+1, i))};
int splitArray(vector<int>& nums, int m) {
    int n = nums.size();
    vector<vector<long long>> f(n+1, vector<long long>(m+1, LLONG_MAX));
    vector<long long> sub(n+1);

    for (int i = 0; i < n; ++i) sub[i+1] = sub[i] + nums[i];
    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, m); ++j) {
            for (int k = 0; k < i; ++k) {
                f[i][j] = min(f[i][j], max(f[k][j-1], sub[i]-sub[k]));
            }
        }
    }
    return (int)f[n][m];
}

namespace _1{
//! 贪心——找一个x验证是否存在一种分割方案,满足其最大分割子数组和不超过x
//* 从前到后遍历数组，用sum表示当前分割子数组的和，cnt表示分割出的子数组的数量
//* 每当sum加上当前值超过了x, j把当前值作为新的开头cnt加一
bool check(vector<int>& nums, int x, int m) {
    long long sum = 0;
    int cnt = 1;
    for (int i = 0; i < nums.size(); ++i) {
        if (sum + nums[i] > x) {
            ++cnt;
            sum = nums[i];
        } else {
            sum += nums[i];
        }
    }
    return cnt <= m;
}

int splitArray(vector<int>& nums, int m) {
    long long l = 0, r = 0;
    for (int i = 0; i < nums.size(); ++i) {
        r += nums[i];
        if (l < nums[i]) {
            l = nums[i];
        }
    }

    while(l < r) {
        long long mid = l + (r - l)/2;
        if (check(nums, mid, m)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}
}

}

//! 数组去重================================================================

//! 删除有序数组中的重复项
namespace _26removeDuplicates {
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int slow = 0, fast = 0;
        while (fast < n) {
            if (nums[slow] != nums[fast]) {
                ++slow;
                nums[slow] = nums[fast];
            }
            ++fast;
        }
        
        return slow + 1;
    }
}

//! 数组移除元素=======================
namespace _27removeElement {
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        if (n == 0) return 0;

        int slow = 0, fast = 0;
        while (fast < n) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
        return slow;
    }
}

//! 移动零================================
//! 相当于移除数组中的0,再将后面的数都置零
namespace _283moveZeroes {
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int p0 = -1, p = 0;
        while (p < n) {
            if (nums[p] == 0) {
                if (p0 == -1) p0 = p; // 首先将p0指向0
            } else {
                if (p0 != -1) {
                    swap(nums[p0], nums[p]); 
                    ++p0;
                }
            }
            ++p;
        }
    }
}


//! Offer51 数组中的逆序对===========================
namespace __51reversePair {

    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r) {
            return 0;
        }
        int mid = (l + r) / 2;
        int inv_count = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid+1, r);
        int i = l, j = mid + 1, pos = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {
                tmp[pos] = nums[i];
                ++i;
                //! nums[i] 比 nums[mid+1, j-1]大
                inv_count += (j - (mid+1));
            } else {
                tmp[pos] = nums[j];
                ++j;
            }
            ++pos;
        }

        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = nums[k];
            inv_count += (j - (mid+1));
        }
        for (int k = j; k <= r; ++k) {
            tmp[pos++] = nums[k];
        }
        copy(tmp.begin()+l, tmp.begin()+r+1, nums.begin()+l);
        return inv_count;

    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size(); vector<int> tmp(n);
        vector<int> copy(nums);
        return mergeSort(copy, tmp, 0, n-1);
    }
}
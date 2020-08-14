#pragma once 
#include <algorithm>
#include <vector>
#include <unordered_map>

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


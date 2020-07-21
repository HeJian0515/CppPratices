#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

namespace _16cur {
     vector<int> divingBoard(int shorter, int longer, int k) {
         if (k < 1) return {};
         if (shorter==longer) return {shorter*k};
         vector<int> res(k+1, 0); // 节省vector重新分配空间的时间
         for (int x = 0; x <= k; ++x) {
             res[x] = (longer*x+ shorter*(k-x)); // 关于x单调递增，故不会有重复值
         }
         return res;
    }
}

namespace _350Array { //! 350. 两个数组的交集 II
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() < 1 || nums2.size() < 1) return {};
        unordered_map<int, int> map;

        for (int num : nums1) {
            ++map[num];
        }
        vector<int> res;

        for (int num : nums2) {
            if (map.count(num)) {
                res.push_back(num);
                --map[num];
                if (map[num] == 0) {
                    map.erase(num);
                }
            }
        }
        return res;
    }
}
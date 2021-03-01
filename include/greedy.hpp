#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

namespace _435Interval {  //! 435. 无重叠区间

static bool compare(vector<int>& a1, vector<int>& a2) {
    return a1.back() < a2.back();
}
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() < 1) return 0;
    std::sort(intervals.begin(), intervals.end(), [](vector<int>& a1, vector<int>& a2)->bool { return a1.back() < a2.back();});
    // 至少有一个区间相交
    int count = 1;
    int x_end = intervals[0].back();
    for (int i = 1; i < intervals.size(); ++i) {
        int x_start = intervals[i].front();
        if (x_start >= x_end) {
            ++count;
            x_end = intervals[i].back();
        }
    }
    return intervals.size() - count;
}
}  // namespace _435Interval

namespace _392SubStr {
bool isSubsequence(string s, string t) {
    int i = 0;
    for (int j = 0; i < s.length(), j < t.length(); ) {
        if (s[i] == t[j]) {
           ++i;
        }
        ++j;
    }
    return i == s.size();
}
// 动态规划
//* f[i][j] t从i开始 j字符第一次出现的位置 
bool IsSubsequence(string s, string t) {
    int sLen = s.size();
    int tLen = t.size();
    vector<vector<int>> f(tLen+1, vector<int>(26, 0));
    for (int i = 0; i < 26; ++i) {
        f[tLen][i] = tLen; // f==tLen表示从i开始不存在i字符
    }

    // 从后往前递推初始化dp数组
    for (int i = tLen - 1; i >= 0; --i) {
        // 从 a到z
        for (int j = 0; j < 26; ++j) {
            if (t[i] == j+'a') f[i][j] = i;
            else f[i][j] = f[i+1][j];
        }
    }

    // 每次从 add位置寻找s[i]第一次的位置, 同时+1更新add，开始下一轮寻找s[i+1]
    int add = 0;
    for (int i = 0; i < sLen; ++i) {
        // t中没有s[i]
        if (f[add][s[i] - 'a'] == tLen) return false;
        // 跳到s[i]第一次出现的位置之后一位
        add = f[add][s[i] - 'a'] + 1;
    }
    return true;

}
}

namespace _53MaxSubArray {
//* 暴力法
int maxSubArray(vector<int>& nums) {
    int max = INT_MIN;
    for (int i = 0; i < nums.size(); ++i) {
        int sum_iToj = 0;
        for (int j = i ; j < nums.size(); ++j) {
            sum_iToj += nums[j];
            max = std::max(max, sum_iToj);
        }
    }
    return max;
}
// f(i) 以i为结尾的序列的最大和 f(i) = max{f(i-1)+a[i], a[i]}
int maxSubArray_1(vector<int>& nums) {
    int pre = 0;
    int maxAns = nums[0];
    for (const auto x : nums) {
        pre = std::max(pre + x, x);
        maxAns = std::max(maxAns, pre);
    }
    return maxAns;
}
}

namespace _763partitionLabels{
//*每次找第一个字母出现的最后位置 再找第二个字母出现的最后位置...
vector<int> partitionLabels(string S) {
    unordered_map<char, int> charIndexMap; // 记录字符最后一次出现的位置
    int strLen = S.size();
    for (int i = 0; i < strLen; ++i) {
        charIndexMap[S[i]] = i;
    }

    vector<int> res;
    int start = 0;
    int end = 0;

    for (int i = 0; i < strLen; ++i) {
        end = std::max(end, charIndexMap[S[i]]);
        if (i == end) {
            res.push_back(end - start + 1);
            start = end + 1;
        }
    }

    return res;
}

// 用变长数组代替map
vector<int> partitionLabels_1(string S) {
    vector<int> charIndexMap(26, INT_MAX);
    int strLen = S.size();
    // 建立字符和最后一次出现位置的映射
    for (int i = 0; i < strLen; ++i) {
        charIndexMap[S[i]-'a'] = i;
    }

    vector<int> res;
    int start = 0;
    int end = 0;

    for (int i = 0; i < strLen; ++i) {
        end = std::max(end, charIndexMap[S[i] - 'a']);
        if (i == end) {
            res.push_back(end - start + 1);
            start = end + 1;
        }
    }

    return res;
}
}
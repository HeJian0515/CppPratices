#pragma once

#include <algorithm>
#include <vector>
#include <string>
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

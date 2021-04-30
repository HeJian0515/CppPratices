#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace _88merge 
{
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
    int pos = m + n -1;
    --m;
    --n;
    while(m >=0 && n >= 0) {
        if (nums1[m] > nums2[n]) {
            nums1[pos--] = nums1[m--];
        } else {
            nums1[pos--] = nums2[n--];
        }
    }

    while (n >= 0) {
        nums1[pos--] = nums2[n--];
    }
}
}

//! 滑动窗口框架=========================================================
#if 0

void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) {
        ++need[c];
    }

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        // c是将移入窗口的字符
        char c = s[right];
        // 右移窗口
        ++right;
        // 进行窗口内数据的一系列更新
        ...

        // ===debug输出位置=== 
        printf("window: [%d, %d]\n", left, right);
        //***********************************

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            // d 是将要移出窗口的字符
            char d = s[left];
            // 左移窗口
            ++left;
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}

#endif
//! 滑动窗口框架=========================================================

namespace _76minWindow
{
string minWindow(string s, string t)
{
    unordered_map<char, int> needs, window;
    for (char c : t) {
        ++needs[c];
    }

    int left = 0, right = 0;
    int valid = 0;

    int start = 0, len = INT_MAX;
    while(right < s.size()) {
        char c = s[right];
        ++right;
        //* 不断向右,使窗口内包含t的所有字符个数相同
        if (needs.count(c)) {
            window[c]++;
            if (window[c] == needs[c]) {
                valid++; // 每个字符的个数相同，则完成一个字符的收集
            }
        }

        // 当s满足包含t时，记录子串，并缩减窗口
        while (valid == needs.size()) { 
            if (right - left < len) {
                start = left;
                len = right - left;
            }

            char d = s[left];
            left++;

            if (needs.count(d)) {
                if (window[d] == needs[d]) {
                    valid--; 
                }
                window[d]--;
            }
        }
    }

    return len == INT_MAX ? "" : s.substr(start, len); 
}

}
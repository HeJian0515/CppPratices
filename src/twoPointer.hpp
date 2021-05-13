#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

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

namespace _567checkInclusion
{
// 判断 s2 中是否存在 s1 的排列
bool checkInclusion(string s1, string s2)
{
    unordered_map<char, int> window, needs;
    for (char c : s1) {
        ++needs[c];
    }

    int l = 0, r = 0;
    int valid = 0;
    while (r < s2.size())
    {
        char c = s2[r];
        ++r;

        // 进行窗口内数据的一系列更新
        if (needs.count(c)) {
           int n = ++window[c];
           if (n == needs[c]) ++valid;
        }

        // 当窗口长度r-l等于s1长度时候进入循环，减小窗口的长度
        if (r - l >= s1.size())
        {
            if (valid == needs.size()) return true;

            // 缩小窗口并更新窗口数据
            char d = s2[l];
            ++l;
            if (needs.count(d)) {
                if (window[d] == needs[d]) {
                    --valid;
                }
                --window[d];
            }
        } 
    }
    return false;
}
}

//* 类似上题
namespace _438findAnagrams
{
vector<int> findAnagrams(string s, string p)
{
    unordered_map<char, int> needs, window;
    for (char c : p) ++needs[c];

    int l = 0, r = 0;
    int valid = 0;
    vector<int> ans;

    while (r < s.size())
    {
        char c = s[r];
        ++r;

        if (needs.count(c)) {
            int n = ++window[c];
            if (n == needs[c]) ++valid;
        }

        if (int len = r - l; len == p.size())
        {
            if (valid == needs.size()) ans.push_back(l);

            char d = s[l];
            ++l;
            if (needs.count(d)) {
                int n = window[d]--;
                if (n == needs[d]) {
                    --valid;
                }
            }
        }
    }

    return ans;
}
}

namespace _3lengthOfLongestSubstring
{
int lengthOfLongestSubstring(string s)
{
    unordered_set<char> chSet;
    int l = 0, r = 0;
    int ans = 0;
    while (r < s.size())
    {
        char c = s[r];
        ++r;

        if (!chSet.count(c)) {
            chSet.insert(c);
            ans = max(ans, r - l);
        } else {
            while (chSet.count(c))
            {
                char d = s[l];
                chSet.erase(d);
                ++l;
            }
            chSet.insert(c);
        }
    }
    return ans;
}
}

namespace _340lengthOfLongestSubstringkDistinct 
{
int lengthOfLongestSubstringKDistinct(string s, int k)
{
    int sLen = s.size();
    int l = 0, r = 0;
    unordered_map<char, int> chMap; // 记录加入窗口的字符的个数
    int len = 0;
    while (r < sLen)
    {
        // 窗口右边界不断拓展
        int c = s[r];
        ++r;
        ++chMap[c];

        if (chMap.size() <= k) {
            len = max(len, r-l); // 满足要求时，更新结果
        } else {
            while (chMap.size() > k) // 当字符数大于k时，左边界右移以缩小窗口，使字符个数<=k
            {
                char d = s[l];
                if (--chMap[d] == 0) {
                    chMap.erase(d);
                }
                ++l;
            }
        }
    }

    return len;
}
}


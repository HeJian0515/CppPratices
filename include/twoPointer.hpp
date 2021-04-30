#include <algorithm>
#include <numeric>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
using namespace std;

namespace _76minWindow
{
string minWindow(const string& s, const string& t) {
    unordered_map<char, int> need;
    unordered_map<char, int> window;
    for(char c : t) ++need[c];

    int left = 0;
    int right = 0;
    int valid = 0;
    // 记录最小覆盖子串的起始索引及长度
    int start = 0;
    int len = std::numeric_limits<int>::max();

    while (right < s.size()) {
        // c 是将移入窗口的字符
        char c = s[right];
        ++right; // 右移窗口
        // 进行窗口内数据的一系列更新
        if (need.count(c)) {
            ++window[c];
            if (window[c] == need[c]) {
                ++valid;
            }
        }

        // 判断左侧窗口是否要收缩
        while (valid == need.size()) {
            // 在这里更新最小覆盖子串
            if (right - left < len) {
                start = left;
                len = right - left;
            }

            // d将是移出窗口的字符
            char d = s[left];
            // 左移窗口
            ++left;
            // 进行窗口内数据的一系列更新
            if (need.count(d)) {
                if (window[d] == need[d]) --valid;
                --window[d];
            }
        }
    }

    return std::numeric_limits<int>::max() == len ? "" : s.substr(start, len);
}
}

namespace _567checkInclusion
{
bool checkInclusion (const string& s1, const string& s2) {
    unordered_map<char, int> need, window;
    for (char c : s1) ++need[c];

    int left = 0, right = 0;
    int valid = 0;
    while (right < s2.size()) {
        char c = s2[right];
        ++right;

        if (need.count(c)) {
            ++window[c];
            if (window[c] == need[c]) {
                ++valid;
            }
        }

        while (right - left >= s1.size()) {
            if (valid == need.size()) return true;

            char d = s2[left];
            ++left;
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    --valid;
                }
                --window[d];
            }
        }
    }

    return false;
    
}
}

namespace _438findAnagrams
{
vector<int> findAnagrams(const string& s, const string& p) 
{
    unordered_map<char, int> need, window;
    for (char c : p) ++need[c];

    int left = 0, right = 0;
    int valid = 0;
    vector<int> res;
    while (right < s.size()) {
        char c = s[right];
        ++right;
        if (auto it = need.find(c); it != need.cend()) {
            ++window[c];
            if (window[c] == it->second) {
                ++valid;
            }
        }

        while (right - left >= p.size()) {
            if (valid == need.size()) {
                res.push_back(left);
            }
            char d = s[left];
            ++left;
            
            if (auto it = need.find(d); it != need.cend()) {
                if (window[d] == it->second) {
                    --valid;
                }
                --window[d];
            }
        }
    }
    return res;
}
}

namespace _3lengthOfLongestSubstring
{
int lengthOfLongestSubstring(const string& s) {
    // 记录字符和其位置
   unordered_map<char, int> window;

   int left = 0, right = 0;
   int maxLen = 0;
   while (right < s.size()) {
       char c = s[right];
       if (window.count(c) && window[c] != -1) {
           int n = window[c];
           for (int i = left; i < n; ++i){
               window[s[i]] = -1;
           }
           left = n + 1;
       }
       window[c] = right;
        ++right;
       maxLen = std::max(maxLen, right -left);
   }
   return maxLen;
}
}

namespace _threeSum {
vector<vector<int>> threeSum(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());

    vector<vector<int>> res;
    int n = nums.size();
    for (int first = 0; first < n; ++first) {
        if (first > 0 && nums[first] == nums[first - 1]) {
            continue;
        }

        int target = -nums[first];
        int thrid = n -1;
        for (int second = first + 1; second < n; ++second) {
            if (second > first + 1 && nums[second] == nums[second - 1]) {
                continue;
            }

            while (second < thrid && nums[second] + nums[thrid] > target) {
                --thrid;
            }

            if (second == thrid) break;

            if (nums[second] + nums[thrid] == target) {
                res.push_back({nums[first], nums[second], nums[thrid]});
            }
        }
    }
    return res;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    int n = nums.size();
    if (n < 3 || nums[0] > 0 || nums[n-1] < 0) {
        return res;
    }

    for (int first = 0; first < n; ++first) {
        if (first > 0 && nums[first] == nums[first - 1]) continue;
        if (nums[first] > 0) break;
       

        // 双指法求TwoSum
        int second = first + 1;
        int third = n - 1;
        int target = -nums[first];
        while (second < third) {
            int sum = nums[second] + nums[third];

            if (sum == target) {
                res.push_back({nums[first], nums[second], nums[third]});
                while (second < third && nums[second] == nums[second + 1]) {
                    ++second;
                }
                while (second < third && nums[third] == nums[third-1]) {
                    --third;
                }
                ++second;
                --third;
            } else if (sum < target) { 
                ++second;
            } else {
                --third;
            }
        }
    }

    return res;
}
}
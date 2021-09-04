#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <cstdlib>
#include <set>
#include <stack>
#include <queue>
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

// 删除一个字符后是否仍然为回文
namespace _680validPalindrome
{
bool isPalindrome(const string& str, int l, int r)
{
    while (l <= r) {
        if (str[l] == str[r]) {
            ++l, --r;
        } else {
            return false;
        }
    }
    return true;
}

bool validPalindrome(string s)
{
    int l = 0, r = s.size()-1;
    while (l <= r) {
        if (s[l] == s[r]) {
            ++l, --r;
        } else {
            return isPalindrome(s, l+1, r) || isPalindrome(s, l, r-1);
        }
    }
    return true;
}
}

// 反转元音字符
namespace _345reverseVowels
{
string reverseVowels(string s)
{
    int l = 0;
    int r = s.size()-1;

    const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};

    while (l <= r) {
       int lIsVow = vowels.count(s[l]);
       int rIsVow = vowels.count(s[r]);

       if (!lIsVow && !rIsVow) {
           ++l, --r;
       } else if (lIsVow && rIsVow) {
           swap(s[l++], s[r--]);
       } else if (lIsVow) {
           while (l <= r && !vowels.count(s[r])) {
               --r;
           }
           swap(s[l++], s[r--]);
       } else {
           while (l <= r && !vowels.count(s[l])) {
               ++l;
           }
           swap(s[l++], s[r--]);
       }
    }
    return s;
}
}

//! 判断一个字符能不能通过删除得到
namespace _524findLongestWord
{
bool isSubstring(const string& s, const string& sub)
{
    int sl = 0, subl = 0;
    while (sl < s.size() && subl < sub.size()) {
        if (s[sl] == sub[subl]) {
            ++subl;
        }
        ++sl;
    }
    return subl == sub.size();
}
string findLongestWord(string s, vector<string>& dictionary)
{
    string ans;

    for(const auto& sub : dictionary) {
        if (sub.size() >= ans.size()) {
            if (isSubstring(s, sub)) {
                if (sub.size() == ans.size()) {
                    ans = sub < ans ? sub : ans;
                } else {
                    ans = sub;
                }
            }
        }
    }
    return ans;
}
}

namespace _containsNearbyAlmostDuplicate
{
//! 将[i-k, i-1]的元素放入有序集合中, 在里面寻找[nums[i]-t, nums[i]+t]的元素
// 保持集合中始终是nums[i]，左侧的k个元素
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    int n = nums.size();
    set<int> rec;

    for (int i = 0; i < n; ++i) {
        // 找到下界， 并比较下界的值<= nums[i]+t
        auto iter = rec.lower_bound(max(nums[i], INT_MIN+t)-t);
        if (iter != rec.end() && *iter <= min(nums[i], INT_MAX-t)+t) {
            return true;
        }
        rec.insert(nums[i]);
        if (i >= k) {
            rec.erase(nums[i-k]);
        }
    }

    return false;
}

//! 桶排序 ---》 找出生日在30天之内的人; 按月份分桶，再比较相邻桶中的元素
long getID(long x, long t) 
{
    // 如果x元素大于等于0,直接分桶
    if (x >= 0) {
        return x /(t+1);
    } else {
        return (x + 1)/(t+1) -1;
    }
    return 0;
}

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    unordered_map<int, int> m;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        long x = nums[i];
        //给当前元素生成id,这里我们同一个id的桶内元素满足abs(nums[i] - nums[j]) <= t
        int id = getID(x, t);
        if (i-(k+1) >= 0) {
            m.erase(getID(nums[i-(k+1)], t));
        }

        // 看看当前元素属于的桶中有没有元素
        if (m.count(id)) {
            return true;
        }
        // 看看前面相邻的桶有没有符合条件的
        if (m.count(id-1) && abs(m[id-1]-x) <= t) {
            return true;
        }
        // 看看后面相邻的桶有没有符合条件的
        if (m.count(id+1) && abs(m[id+1]-x) <= t) {
            return true;
        }

        m[id] = x;
    }
    return false;
}

}


//! 三数之和=====================================================
namespace _15threeSum {
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        // 枚举a
        for (int first = 0; first < n; ++first) {
            if (first > 0 && nums[first] == nums[first-1]) {
                continue;
            }
            // c对应的指针指向数组的最右端
            int third = n - 1;
            int target = -nums[first];

            // 枚举b
            for (int second = first + 1; second < n; ++second) {
                // 需要和上一次枚举的数不相同
                if (second > first + 1 && nums[second] == nums[second-1]) {
                    continue;
                }

                // 需要保证b的指针在c的指针的左侧
                while (second < third && nums[second] + nums[third] > target) {
                    -- third;
                }
                // 如果指针重合，随着b后续的增加
                // 就不会满足a+b+c=0,并且 b < c 的c了
                if (second == third) break;

                if (nums[second] + nums[third] == target) {
                    ans.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return ans;
    }
}

//! 下一个排列==================================================
namespace _31nextPermutation {
    //! 找一个较小的和一个较大数，较小数尽量有
    //1. 从后向前查找第一个顺序对(i, i+1)，满足a[i] < a[i+1]; [i+1， n)必为降序序列
    //2. 如果找到了顺序对，那么在区间[i+1, n)中从后向前查找第一个元素j,满足a[i]<a[j].
    //3. 交换a[i]与a[j],此时可以证明该区间[j+1, n)必为降序
    void nextPermutation(vector<int>& nums) {
        int i = nums.size()-2;
        while (i >= 0 && nums[i] >= nums[i+1]) {
            --i;
        }

        if (i >= 0) {
            int j = nums.size()-1;
            while (j >= 0 && nums[i] >= nums[j]) {
                --j;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin()+i+1, nums.end());
        
    }
}
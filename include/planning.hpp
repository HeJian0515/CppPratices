#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

//!滑动窗口==========================================================
namespace _325LC {
class Solution {
   public:
    //! 双指指针，暴力迭代
    int maxSubArrayLen(vector<int>& nums, int k) {
        int len = nums.size();
        int max = 0;
        for (int i = 0; i < len; ++i) {
            int sum = 0;
            for (int j = i; j < len; ++j) {
                sum += nums[i];
                if (sum == k) max = std::max(sum, j - i + 1);
            }
        }
        return max;
    }
    //******************************************************
    int maxSubArrayLen_1(vector<int>& nums, int k) {
        int len = nums.size();
        vector<int> sums(len);

        using sn = int;     // nums前n项和
        using index = int;  // nums最早出现sn时下标
        unordered_map<sn, index> um;
        um[0] = -1;
        int maxLen = 0;
        int sum = 0;

        // 每次记录[...., i]的maxLen
        for (int i = 0; i < len; ++i) {
            sum += nums[i];
            if (um.count(sum - k)) {
                maxLen = std::max(i - um[sum - k], maxLen);
            }
            if (!um.count(sum)) {
                um[sum] = i;
            }
        }
        return maxLen;
    }
};
}  // namespace _325LC

namespace _subArrayGivenSum {
class Solution {
   public:
    int subArraySum(vector<int>& arr, int sum) {
        int curSum;
        int len = arr.size();
        for (int i = 0; i < len; ++i) {
            curSum = arr[i];
            for (int j = i + 1; j <= len; ++j) {
                if (curSum == sum) {
                    cout << "Sum found between indexes " << i << " and " << j - 1;
                }
                if (curSum > sum || j == len) break;
                curSum = curSum + arr[j];
            }
        }
        cout << "No subarray found";
        return 0;
    }

    void subArraySum_1(vector<int>& arr, int sum) {
        int len = arr.size();
        int curSum = arr[0];
        int start = 0;

        for (int i = 1; i <= len; ++i) {
            // 左边界右移
            while (curSum > sum && start < i - 1) {
                curSum = curSum - arr[start];
                start++;
            }
            if (curSum == sum) {
                cout << "Sum found between indexes " << start << " and " << i - 1;
                return;
            }
            // 右边界右移
            if (i < len) curSum += arr[i];
        }
        cout << "No subarray found";
    }
};
}  // namespace _subArrayGivenSum

namespace _340LC {
class Solution {
   public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> um;
        int left = 0, right = 0;
        int res = 0;
        while (right < s.length()) {
            ++um[s[right]];
            while (um.size() > k) {                         //!判断窗口内字符种类是否大于k
                if (--um[s[left]] == 0) um.erase(s[left]);  //如果大于k，左边界开始缩小窗口，直至等于k
                ++left;
            }
            // 前面的步骤保证了窗口内至多有k种字符
            // 更新max值
            res = std::max(res, right - left + 1);
            ++right;
        }
        return res;
    }
};
}  // namespace _340LC

namespace _904LC {
class Solution {
    using FruitType = int;

   public:
    int totalFruit(vector<int>& tree) {
        unordered_map<FruitType, int> um;
        int left = 0, right = 0;
        int res = 0;
        while (right < tree.size()) {
            ++um[tree[right]];  // 增大窗口
            ++right;
            while (um.size() > 2) {  // 当窗口内水果种类超过两种，便开始缩小窗口
                --um[tree[left]];
                if (um[tree[left]] == 0) um.erase(tree[left]);  // 当某种水果类型数量为0时，将其移出窗口
                ++left;
            }
            res = std::max(res, right - left);  // 保证窗口内水果种类<=两种，更新结果
        }
        return res;
    }
};
}  // namespace _904LC

namespace _3LC {
class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> um;  // 字符出现的个数
        int left = 0, right = 0;
        int res = 0;

        while (right < s.length()) {
            ++um[s[right]];
            while (um[s[right]] > 1) {
                --um[s[left++]];
            }
            res = std::max(res, right - left + 1);
            ++right;
        }
        return res;
    }
};
}  // namespace _3LC

//!双指针===============================================================
// 有序数组Two Sum
namespace _167LC {
class Solution {
   public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum > target) {
                --right;
            } else {
                ++left;
            }
        }
        return {};
    }
};
}  // namespace _167LC

//!两数平方和
namespace _633Lc {
class Solution {
   public:
    bool judgeSquareSum(int c) {
        long left = 1;
        long right = sqrt(c);
        while (left <= right) {
            long squareSum = left * left + right * right;
            if (squareSum == c) {
                return true;
            }
            squareSum < c ? ++left : --right;
        }
        return false;
    }
};
}  // namespace _633Lc

//!原音替换
namespace _345LC {
class Solution {
   private:
    const unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

   public:
    string reverseVowels(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (vowels.count(s[left]) && vowels.count(s[right])) {
                std::swap(s[left], s[right]);
                ++left;
                --right;
            } else if (!vowels.count(s[left]) && vowels.count(s[right])) {
                ++left;
            } else if (vowels.count(s[left]) && !vowels.count(s[right])) {
                --right;
            } else {
                ++left;
                --right;
            }
        }
        return s;
    }
};
}  // namespace _345LC

//!验证回文字符串
namespace _680LC {
class Solution {
   private:
    //! 判断一个字符串是否为回文
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

   public:
    bool validPalindrome(string s) {
        for (int i = 0, j = s.length() - 1; i < j; ++i, --j) {
            if (s[i] != s[j]) {  //!若有一个字符不相等
                //!判断删除左边或右边的一个字符后是否为回文
                return isPalindrome(s, i, j - 1) || isPalindrome(s, i + 1, j);
            }
        }
        return true;
    }
};
}  // namespace _680LC

//!合并两个有序数组
namespace _88LC {
class Solution {
   public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index1 = m - 1, index2 = n - 1;
        int indexMerge = m + n - 1;
        while (index1 >= 0 || index2 >= 0) {
            if (index1 < 0) {
                nums1[indexMerge--] = nums2[index2--];
            } else if (index2 < 0) {
                nums1[indexMerge--] = nums1[index1--];
            } else if (nums1[index1] > nums2[index2]) {
                nums1[indexMerge--] = nums1[index1--];
            } else {
                nums1[indexMerge--] = nums2[index2--];
            }
        }
        for (auto it : nums1) {
            cout << it << ",";
        }
    }
};
}  // namespace _88LC

//!链表是否有环
namespace _141LC {

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast;
        if (head && head->next)
            fast = head->next;
        else
            return false;
        while (fast && fast->next) {
            if (slow == fast) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }

    bool hasCycle_1(ListNode* head) {
        if (!head) return false;
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            if (slow == fast) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }
};
}  // namespace _141LC

namespace _524LC {
class Solution {
   private:
    bool isSubstr(const string& s, const string& target) {
        int i = 0, j = 1;
        while (i < s.length() && j < target.length()) {
            if (s[i] == target[j]) {
                ++j;
            }
            ++i;
        }
        return j == target.length();
    }

   public:
    string findLongestWord(string s, vector<string>& d) {
        string longestWord = "";
        for (auto& target : d) {
            int l1 = longestWord.length();
            int l2 = target.length();
            if (l1 > l2 || (l1 == l2 && longestWord.compare(target) < 0)) {
                continue;
            }
            //!判断s删除一些字符后能否变成target
            if (isSubstr(s, target)) {
                longestWord = target;
            }
        }
        return longestWord;
    }
};
}  // namespace _524LC

//!排序问题=======================================================================
//*数组中的第K个最大元素
namespace _215LC {
class Soulution {
   public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (auto val : nums) {
            if (pq.size() == k) {
                if (val > pq.top()) {
                    pq.push(val);
                    pq.pop();
                }
            } else {
                pq.push(val);
            }
        }
        return pq.top();
    }
};

inline int partition(vector<int>& a, int l, int r) {
    int x = a[r], i = l - 1;
    // 将小于等于x的放到数组左边
    // i+1为大于x的位置
    for (int j = l; j < r; ++j) {
        if (a[j] <= x) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);  // 将a[r]放到应该放的位置
    return i + 1;
}

inline int randomPartition(vector<int>& a, int l, int r) {
    int i = rand() % (r - l + 1) + l;  // 随机找一个元素
    swap(a[i], a[r]);
    return partition(a, l, r);
}

// 将随机得到的i排到正确的位置
// 如果i的位置q恰好时是第k大的位置则返回
// 否则在q两边之一找一个元素去排
int quickSelect(vector<int>& a, int l, int r, int index) {
    int q = randomPartition(a, l, r);
    if (q == index) {
        return a[q];
    } else {
        return q < index ? quickSelect(a, q + 1, r, index) : quickSelect(a, l, q - 1, index);
    }
}

int findKthLargest(vector<int>& nums, int k) {
    srand(time(0));
    return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
}
}  // namespace _215LC

//* 前 K 个高频元素
namespace _347LC {
class Solution {
   public:
    static bool cmp(pair<int, int>& m, pair<int, int>& n) {
        return m.second > n.second;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            ++occurrences[v];
        }

        //! pair的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        //! 小顶堆
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        for (auto& [num, count] : occurrences) {
            if (q.size() == k) {
                //! 出现频率大于小顶堆最少的，则将其加入堆，并移除最少的
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);
                }
            } else {
                q.emplace(num, count);
            }
        }

        vector<int> ret;
        while (!q.empty()) {
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};
}  // namespace _347LC

//* 根据字符出现的频率排序
namespace _451LC {
string frequencySort(string s) {
    unordered_map<char, int> umap;
    for (auto ch : s) {
        ++umap[ch];
    }
    auto cmp = [](pair<int, char>& e1, pair<int, char>& e2) { return e1.first < e2.first; };
    priority_queue<pair<int, char>, vector<pair<int, char>>, decltype(cmp)> que(cmp);
    for (auto& [ch, fre] : umap) {
        que.emplace(fre, ch);
    }

    string ans;
    while (!que.empty()) {
        auto top = que.top();
        que.pop();
        ans.append(string(top.first, top.second));
    }
    return ans;
}
}  // namespace _451LC

//* 颜色分类
//* 荷兰国旗问题
namespace _75LC {
void sortColors(vector<int>& nums) {
    // 对于所有 idx < p0 : nums[idx < p0] = 0
    // curr 是当前考虑元素的下标
    int p0 = -1, curr = 0;
    // 对于所有的idx > p2: nums[idx > p2] = 2;
    int p2 = nums.size();

    while (curr < p2) {
        if (nums[curr] == 0) {
            swap(nums[curr++], nums[++p0]);
        } else if (nums[curr] == 2) {
            swap(nums[curr], nums[--p2]);
        } else {
            ++curr;
        }
    }
}
}  // namespace _75LC

//!贪心算法=========================================================================
//*分发饼干
namespace _455LC {
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int gi = 0, si = 0;
    while (gi < g.size() && si < s.size()) {
        if (g[gi] <= s[si]) {
            ++gi;
        }
        ++si;
    }
    return gi;
}
}  // namespace _455LC

//*无重叠区间
namespace _435LC {
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() < 2) return 0;
    sort(intervals.begin(), intervals.end(), [](vector<int>& v1, vector<int>& v2) { return v1[1] < v2[1]; });
    int count = 1;  // 至少有一个不相交的的区间
    int x_end = intervals[0][1];
    // 每次走到与区间不相交的第一个区间
    /*  for (int i = 1; i < intervals.size(); ++i) {
        // 找到了第一个与上一个区间不相交的区间，更新基准
        if (intervals[i][0] >= x_end) {
            ++count;                  // 记录不重叠的区间
            x_end = intervals[i][1];  // 更新
        }
    } */
    for (auto& range : intervals) {
        if (range[0] >= x_end) {
            ++count;
            x_end = range[1];
        }
    }
    return intervals.size() - count;
}
}  // namespace _435LC

//*投飞镖刺破气球
namespace _453LC {
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.size() == 0) return 0;
    sort(points.begin(), points.end(), [](vector<int>& v1, vector<int>& v2) { return v1[1] < v2[1]; });
    int cnt = 1;
    int xend = points[0][1];
    for (auto& p : points) {
        if (p[0] > xend) {
            ++cnt;
            xend = p[1];
        }
    }
    /* for (int i = 1; i < points.size(); ++i) {
        if (points[i][0] > xend) {
            ++cnt;
            xend = points[i][1];
        }
    } */
    return cnt;
}
}  // namespace _453LC

//*根据身高重建队列
namespace _406LC {
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), [](vector<int>& v1, vector<int>& v2) {
        return v1[0] == v2[0] ? v1[1] < v2[1] : v1[0] > v2[0];
    });
    list<vector<int>> ans;
    for (auto&& p : people) {
        auto pos = ans.begin();
        advance(pos, p[1]);
        ans.insert(pos, p);
    }
    return vector<vector<int>>(ans.begin(), ans.end());
}
}  // namespace _406LC

//* 买卖股票的最佳时机
namespace _121LC {
//!记录第i天之前的最低价，用（今天的价格-最低价）就是第i天
int maxProfix(vector<int>& prices) {
    int mimprices = INT_MAX;
    int maxprofit = 0;
    for (int i = 0; i < prices.size(); ++i) {
        if (prices[i] < mimprices)
            mimprices = prices[i];
        else if (prices[i] - mimprices > maxprofit)
            maxprofit = prices[i] - mimprices;
    }
    return maxprofit;
}
}  // namespace _121LC

//*买卖股票的最佳时机2
//!累加每一个波谷到波峰的利润
namespace _122LC {
int maxProfix(vector<int>& prices) {
    int i = 0;
    int valley = prices[0];
    int peak = prices[0];
    int maxprofit = 0;
    while (i < prices.size() - 1) {
        while (i < prices.size() - 1 && prices[i] >= prices[i + 1])
            ++i;  // 记录波谷位置
        valley = prices[i];
        while (i < prices.size() - 1 && prices[i] < prices[i + 1])
            ++i;  // 记录波峰位置
        peak = prices[i];
        maxprofit += peak - valley;
    }
    return maxprofit;
}
}  // namespace _122LC

//*种花问题
namespace _605LC {
//!将能种花的地方全种上花 与n比较大小
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if (n == 0) return true;
    if (flowerbed.size() == 1) return flowerbed[0] == 0;
    int cnt = 0;
    for (int i = 0; i < flowerbed.size(); ++i) {
        if (i == 0) {  // 在i==0处能否种花
            if (flowerbed[0] == 0 && flowerbed[1] == 0) {
                ++cnt;
                flowerbed[i] = 1;
            }
        } else if (i == flowerbed.size() - 1) {  // 在 i==最右边时能否种花
            if (flowerbed[i - 1] == 0 && flowerbed[i] == 0) {
                ++cnt;
                flowerbed[i] = 1;
            }
        } else {
            if (flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0) {
                ++cnt;
                flowerbed[i] = 1;
            }
        }
        if (cnt >= n) return true;
    }
    return false;
}

bool canPlaceFlowers_1(vector<int>& flowerbed, int n) {
    int i = 0, cnt = 0;
    while (i < flowerbed.size()) {
        if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) && (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0)) {
            flowerbed[i] = 1;
            ++cnt;
        }
        if (cnt >= n) return true;
        ++i;
    }
    return false;
}

bool canPlaceFlower_2(vector<int>& flowerbed, int n) {
}
}  // namespace _605LC

//?????????????????????????????????????????????????????????????????????判断子序列
namespace _392LC {
//! t中匹配字符都取第一次出现的字符
bool isSubsequence(string s, string t) {
    int n = s.length(), m = t.length();
    int i = 0, j = 0;
    while (i < n && j < n) {
        if (s[i] == t[j]) {
            ++i;
        }
        ++j;
    }
    return i == n;
}

//! 有大量的s需要去和t匹配
//! 所以先把t处理
bool isSubsequence_1(string s, string t) {
    int n = s.size(), m = t.size();
    // f数组中f[i][j]表示字符串t以i位置开始第一次出现的字符j位置
    vector<vector<int>> f(m + 1, vector<int>(26, 0));
    // 初始化边界条件，f[i][j]=m 表示t中不存在字符j
    for (int i = 0; i < 26; ++i) {
        f[m][i] = m;
    }

    // 从后往前递推初始化dp数组
    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) {
            if (t[i] == j + 'a')
                f[i][j] = i;
            else
                f[i][j] = f[i + 1][j];
        }
    }

    int add = 0;
    for (int i = 0; i < n; ++i) {
        // t中没有s[i]返回false
        if (f[add][s[i] - 'a'] == m) {
            return false;
        }
        // 直接跳到t中是s[i]第一次出现的位置之后一位
        add = f[add][s[i] - 'a'] + 1;
    }
    return true;
}
}  // namespace _392LC

//*非递减数列
namespace _665LC {
bool checkPossibility(vector<int>& nums) {
    if (nums.size() <= 1) return true;
    int cnt = 0;  // 记录改变次数
    for (int i = 1; i < nums.size() && cnt < 2; ++i) {
        if (nums[i - 1] <= nums[i]) continue;  // 比较a(i-1)和a(i)
        if (++cnt > 1) return false;
        if (i - 2 >= 0 && nums[i - 2] > nums[i]) {
            nums[i] = nums[i - 1];
        } else {
            nums[i - 1] = nums[i];
        }
    }
    return true;
}
}  // namespace _665LC

//* 最大子序和
namespace _53LC {
int maxSubArray(vector<int>& nums) {
    int pre = 0, maxAns = nums[0];
    for (auto x : nums) {
        pre = max(pre + x, x);  // 以x为结尾的子序列和的最大值
        maxAns = max(maxAns, pre);
    }
    return maxAns;
}
}  // namespace _53LC

//*划分字母空间
namespace _763LC {
//!对与每遇到的第一个字母，去找这个字母最后一次出现的位置
vector<int> partitionLabels(string S) {
    vector<int> last(26, 0);
    for (int i = 0; i < S.length(); ++i)
        last[S[i] - 'a'] = i;  // 最后一出现的位置

    int j = 0, anchor = 0;  // 表示区间的尾、首
    vector<int> ans;
    for (int i = 0; i < S.length(); ++i) {
        j = std::max(j, last[S[i] - 'a']);  // 判断区间内的其他字符最后出现位置在区间外
        if (i == j) {                       // 可以划分出来
            ans.emplace_back(i - anchor + 1);
            anchor = i + 1;
        }
    }
    return ans;
}
}  // namespace _763LC

//!二分查找===========================================================================================
namespace _69LC {
int mySqrt(int x) {
    if (x <= 1) return x;
    int l = 1, h = x;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        int sqrt = x / mid;
        if (sqrt == mid) {
            return mid;
        } else if (mid > sqrt) {
            h = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return h;
}

// 牛顿迭代法
int mySqrt_1(int x) {
    if (x == 0) return 0;

    double C = x, x0 = x;
    while (true) {
        double xi = 0.5 * (x0 + C / x0);
        if (fabs(x0 - xi) < 1e-6) {
            break;
        }
        x0 = xi;
    }
    return int(x0);
}
}  // namespace _69LC

//*寻找比目标字母大的最小字母
//*等价于寻找右边界
namespace _744LC {
char nextGreatestLetter(vector<int>& letters, char target) {
    int len = letters.size();
    int lo = 0, hi = len - 1;
    while (lo <= hi) {
        int mi = lo + (hi - lo) / 2;
        if (letters[mi] <= target) {  //?尽量扩大右区间
            lo = mi + 1;
        } else {
            hi = mi - 1;
        }
    }
    return lo < len ? letters[lo] : letters[0];
}
}  // namespace _744LC

//*寻找有序数组中的单一元素
namespace _540LC {
int singleNonDuplicate(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (mi % 2 == 1) --mi;           // 保证lo、mi、hi都为偶数
        if (nums[mi] == nums[mi + 1]) {  //! 表明元素一定在右边
            lo = mi + 2;
        } else {  //! 表明元素在右边或就是mi
            hi = mi;
        }
    }
    return nums[lo];
}

int singleNonDuplicate(vector<int>& nums) {
    int lo = 0;
    int hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        bool halveAreEven = ((hi - mid) % 2 == 0);
        //!首先判断mid与左右元素等不等，再根据区间长度判断元素位于哪一边
        if (nums[mid + 1] == nums[mid]) {
            if (halveAreEven) {
                lo = mid + 2;
            } else {
                hi = mid - 1;
            }
        } else if (nums[mid - 1] == nums[mid]) {
            if (halveAreEven) {
                hi = mid - 2;
            } else {
                lo = mid + 1;
            }
        } else {
            return nums[mid];
        }
    }
    return nums[lo];
}
}  // namespace _540LC

//*第一个错误的版本
namespace _278LC {
bool isBadVersion(int version);
int firstBadVersion(int n) {
    int lo = 1;
    int hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (isBadVersion(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return hi;
}
}  // namespace _278LC

//* 寻找旋转排列数组中的最小值
namespace _153LC {
int findMin(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    int lo = 0;
    int hi = nums.size() - 1;
    // 没有旋转
    if (nums[hi] > nums[lo]) {
        return nums[0];
    }

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[mid + 1]) {
            return nums[mid + 1];
        }
        if (nums[mid] > nums[0]) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return -1;
}
}  // namespace _153LC

//* 在排序数组中查找元素的第一个和最后一个位置
namespace _34LC {
//! left==false时 求右边界
//! left==true 求左边界
int edgeIndex(vector<int>& nums, int target, bool left) {
    int lo = 0;
    int hi = nums.size();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > target || (left && target == nums[mid])) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

vector<int> searcjRange_1(vector<int>& nums, int target) {
    int leftIdx = edgeIndex(nums, target, true);

    if (leftIdx == nums.size() || nums[leftIdx] != target) {
        return {-1, -1};
    }
    int rightIdx = edgeIndex(nums, target, false) - 1;
    return {leftIdx, rightIdx};
}
vector<int> searchRange(vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size();
    // 求得左边界
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo == nums.size() || nums[lo] != target) return {-1, -1};
    // 求得右边界
    int l = 0;
    int r = nums.size();
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] <= target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return {lo, l - 1};
}
}  // namespace _34LC

//!分治===================================================================
//*给表达式加括号
namespace _241LC {
inline bool isOperation(char c) {
    return c == '+' || c == '-' || c == '*';
}

int caculate(int num1, char c, int num2) {
    switch (c) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
    }
    return 1 / 0;
}

//!添加备忘录
unordered_map<string, vector<int>> umap;
vector<int> diffWaysToCompute(string input) {
    // 递归
    if (input.size() == 0) return {};

    if (umap.count(input)) return umap[input];
    vector<int> res;
    int num = 0;
    //!全是数字的情况
    int index = 0;
    while (index < input.size() && !isOperation(input[index])) {
        num = num * 10 + (input[index] - '0');
        ++index;
    }
    //全是数字时直接返回
    if (index == input.size()) {
        res.push_back(num);
        umap[input] = res;
        return res;
    }

    for (int i = 0; i < input.size(); ++i) {
        // 运算符将字符串分成两部分
        if (isOperation(input[i])) {
            vector<int> lres = diffWaysToCompute(input.substr(0, i));
            vector<int> rres = diffWaysToCompute(input.substr(i + 1));
            // 将两个结果依次运算
            for (int j = 0; j < lres.size(); ++j) {
                for (int k = 0; k < rres.size(); ++k) {
                    char op = input[i];
                    res.emplace_back(caculate(lres[j], op, rres[k]));
                }
            }
        }
    }
    umap[input] = res;
    return res;
}
}  // namespace _241LC

namespace _95LC {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

    vector<TreeNode*> genTree(int start, int end) {
       if (start > end) return {nullptr};
       vector<TreeNode*> allTrees;

       //?遍历可行根节点
       for (int i = start; i <= end; ++i) {
           //?所有的左子树
           vector<TreeNode*> leftTrees  = genTree(start, i-1);
           //?所有的右子树
           vector<TreeNode*> rightTrees = genTree(i+1, end);

           for (auto& left : leftTrees) {
               for (auto& right : rightTrees) {
                   auto currTree = new TreeNode(i);
                   currTree->left = left;
                   currTree->right = right;
                   allTrees.push_back(currTree);
               }
           }
       }
        return allTrees;
    }
    vector<TreeNode*> generateTrees(int n) {
        if (n < 1) return {};
        return genTree(1, n);
    }
}  // namespace _95LC

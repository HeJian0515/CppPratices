#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
#include <list>
#include <forward_list>
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


namespace _452findMinArrowShots
{
int findMinArrowShots(vector<vector<int>>& points)
{
    if (points.empty()) return 0;
    sort(points.begin(), points.end(), 
        [] (const vector<int>& a, const vector<int>& b){return a[1] < b[1];}
    );

    int x_end = points[0][1];
    int delCnt = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (x_end >= points[i][0]) {
            delCnt++;
        } else {
            x_end = points[i][1];
        }
    }
    return points.size() - delCnt;
}
}

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
//* 当遍历到的字符最后位置等于自己的时候，即获得一个划分区间
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


// 分发饼干
// 让饥饿度最小的找到能满足的最小饼干
namespace _455findContentChildren {
int findContentChildren(vector<int>& g, vector<int>& s)
{
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int m = g.size();
    int n = s.size();
    int i = 0, j = 0;
    while (j < n && i < m)
    {
        if (g[i] <= s[j]) {
            ++i;
        };
        ++j;
    }
    return i;
}
}

//!! 135 分发糖果===========================================================
// 升序序列从1开始，降序序列也从1开始
// 升序序列长度等于最后一个人分到的糖果数，降序序列长度等于第一个人分到的糖果数
namespace _135candy {
int candy(vector<int>& ratings)
{
    int n = ratings.size();
    int ret = 1; 
    int inc = 1; // 升序序列长度
    int dec = 0; // 降序序列长度
    int pre = 1; // 上一个人分发的数量

    for (int i = 1; i < n; ++i) {
        if (ratings[i] >= ratings[i-1]) {
            dec = 0;
            pre = (ratings[i] == ratings[i-1]) ? 1 : pre+1;
            ret += pre;
            inc = pre; // 更新升序序列数量
        } else {
            dec++;
            if (dec == inc) { // 当降序序列长度等于升序时，将升序最后一个元素视为降序序列中第一个元素
                dec++;
            }
            ret += dec; // 降序序列以1结尾,前面的全部+1
            pre = 1;
        }
    }

    return ret;
}

//! 分为左规则和右规则；左规则：a[i-1]<a[i]时i号学生得的糖果数量多，
//! 右规则：a[i]>a[i+1]时 i号学生得的糖果数量多
//! 遍历两遍，别使之满足左规则和右规则
int candy_1(vector<int>& ratings) 
{
    int n = ratings.size();
    if (n < 2) return n;

    vector<int> num(n, 1); // 先给每个人分配一个糖果
    // 考虑左规则
    for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i-1]) {
            num[i] = num[i-1] + 1;
        }
    }

    // 考虑右规则
    for (int i = n-1; i > 0; --i) {
        if (ratings[i] < ratings[i-1]) {
            num[i-1] = max(num[i-1], num[i]+1);
        }
    }
    return accumulate(num.cbegin(), num.cend(), 0);
}
}


//! 统计[1, ...., 1]两个1之间的0的个数， 该段区间内种花的数量 = (count - 1) / 2;
namespace _605canPlaceFlowers {
bool canPlaceFlowers(vector<int>& flowerbed, int n)
{   
    int cnt = 0;
    int prev = -1;
    int m = flowerbed.size();

    for (int i = 0; i < m; ++i) {
        if (flowerbed[i] == 1) {
            if (prev < 0) {
                cnt += (i / 2); // [0] 的位置为0的情况
            } else {
                cnt += (i - prev - 2) / 2;
            }

            if (cnt >= n) return true;

            prev = i;
        }
    }

    if (prev < 0) { // 整个数组都为0
        cnt += (m + 1) / 2;
    } else { // 考虑了最后一个数为0和不为0的情况
        cnt += (m - prev - 1) / 2;
    }
    return cnt >= n;
}
}


namespace _406reconstructQueue
{
//* 将人从低往高排序，放入第i个人保证其前面有ki个空位置来放身高更高的人
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(), people.end(), 
        [] (const vector<int>& u1, const vector<int>& u2){
            return u1[0]<u2[0] || (u1[0]==u2[0] && u1[1]>u2[1]);
    });

    int n = people.size();
    vector<vector<int>> ans(n);

    for (const auto& person : people) {
        int spaces = person[1] + 1; // 人应该放到队列从左往右第ki+1个空位置处
        // 将人放到第ki+1个空位置处
        for (int i = 0; i < n; ++i) {
            if (ans[i].empty()) {
                --spaces;
                if (spaces == 0) {
                    ans[i] = person;
                    break;
                }
            }
        }
    }

    return ans;
}

// 将人从高到低排序，放入人时，保证其前面有ki个人就行
vector<vector<int>> reconstructQueue_1(vector<vector<int>>& people) {
    sort(people.begin(), people.end(),
        [] (const vector<int>& v1, const vector<int>& v2){
            return v1[0] > v2[0] || (v1[0] == v2[0] && v1[1] < v2[1]);
        });
    
    // list<vector<int>> lst;
    forward_list<vector<int>> lst;

    for (const auto& person : people) {
       if (lst.empty()) {
           lst.emplace_front(person);
       } else {
           lst.insert_after(next(lst.cbegin(), person[1]-1), person);
       }
    }

    return vector<vector<int>>(lst.cbegin(), lst.cend());
}
}

//! 田忌赛马==================
namespace __870advantageCount {
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        sort(nums1.begin(), nums2.end(), greater<int>());
        vector<pair<int, int>> sorted2(n);
        for (int i = 0; i < n; ++i) {
            sorted2[i] = {nums2[i], i};
        }
        sort(sorted2.begin(), sorted2.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
            return p1.first > p2.first;
        });

        vector<int> res(n);
        // 双指针记录A中来对战的马匹
        int l = 0, r = n -1;
        // 遍历B中所有的马匹
        for (int i = 0; i < n; ++i) {
            auto p = sorted2[i];
            //! A打不过B，找最弱的来
            if (nums1[l] <= p.first) {
                res[p.second] = nums1[r];
                --r;
            } else {
                //! 打的过，就直接比
                res[p.second] = nums1[l];
                ++l;
            }
        }
        return res;
    }
}
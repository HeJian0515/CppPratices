#pragma once
#include <limits.h>

#include <algorithm>
#include <numeric>

#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <climits>
#include <cmath>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

namespace _63dp {  //! 63. 不同路径 II

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int rowNum = obstacleGrid.size();
    if (rowNum < 1) return 0;
    int colNum = obstacleGrid[0].size();
    vector<vector<int>> dp(rowNum + 1, vector<int>(colNum + 1, 0));
    for (int i = 1; i <= rowNum; ++i) {
        for (int j = 1; j <= colNum; ++j) {
            if (obstacleGrid[i - 1][j - 1] == 1)
                dp[i][j] = 0;
            else {
                if (i == 1 && j == 1)
                    dp[1][1] = 1;
                else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
    }
    return dp[rowNum][colNum];
}

}  // namespace _63dp


namespace _120minTri {  //! 120. 三角形最小路径和
int minimumTotal(vector<vector<int>>& triangle) {
    int level = triangle.size();
    vector<vector<int>> dp(level, vector<int>(level));
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < level; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][j] + triangle[i][j];
            } else if (j == triangle[i].size() - 1) {
                dp[i][j] = dp[i - 1][j - 1] + triangle[i][j];
            } else {
                dp[i][j] = std::min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i][j];
            }
        }
    }
    return *min_element(dp[level - 1].begin(), dp[level - 1].end());
}

int minimumTotal2(vector<vector<int>>& triangle) {
    int level = triangle.size();
    vector<int> dp(level, 0);
    dp[0] = triangle[0][0];
    for (int i = 1; i < level; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j == 0) {
                dp[j] = dp[j] + triangle[i][j];
            } else if (j == i) {
                dp[j] = dp[j - 1] + triangle[i][j];
            } else {
                dp[j] = std::min(dp[j - 1], dp[j]) + triangle[i][j];
            }
        }
    }
    return *min_element(dp.begin(), dp.end());
}
}  // namespace _120minTri

//!==================矩阵路径===============
namespace _64minPathSum 
{
int minPathSum(vector<vector<int>>& grid)
{
    if (grid.empty() || grid[0].empty()) return 0;
    int rows = grid.size(); 
    int cols = grid[0].size(); 
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < rows; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    for (int j = 1; j < cols; ++j) {
        dp[0][j] = dp[0][j-1] + grid[0][j];
    }

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[rows - 1][cols - 1];
}
}


namespace _62uniquePaths
{
int uniquePaths(int m, int n) {
    auto dp = vector<vector<int>>(m, vector<int>(n, 0));
    for(int i = 0; i < m; ++i) {
        dp[i][0] = 1;
    }
    for (int j = 0; j < n; ++j) {
        dp[0][j] = 1;
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[m-1][n-1];
}
}

//!====================数组区间和========================

namespace _303NumArray
{
class NumArray
{
    vector<int> sums;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        sums.resize(n+1);
        for (int i = 0; i < n; ++i) {
            sums[i+1] = sums[i] + nums[i];
        }
    }

    inline int sumRange(int i, int j) {
        return sums[j+1] - sums[i];
    }
};
}

namespace _413numberOfArithmeticsSlices
{
int numberOfArithmeticSlices(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) return 0;
    // dp[i] 以标号i为尾的等差子数列个数
    vector<int> dp(n, 0);
    int sum = 0;
    for (int i = 2; i < n; ++i) {
        if (nums[i] - nums[i-1] == nums[i -1] - nums[i - 2]) {
            dp[i] = 1 + dp[i-1];
            sum += dp[i];
        }
    }
    return sum;
}
}

//!=====================分割类型=============================
//* 分割整数的最大乘积
namespace _343integerBreak
{
int integerBreak(int n) {
    // dp[i] 表示将正整数 i 拆分成至少两个正整数的和之后，这些正整数的最大乘积。
    vector<int> dp(n+1, 0); 
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            dp[i] = std::max({dp[i], j*(i-j), j * dp[i-j]});
        }
    }
    return dp[n];
}
}

//* 按平方数来分割整数
namespace _297numSquares
{
int numSquares(int n) {
    vector<int> dp(n+1, n);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = 1, max = static_cast<int>(sqrt(i)); j <= max; ++j) {
            dp[i] = std::min(dp[i], 1+dp[i - j*j]);
        }
    }
    return dp[n];
}
}

//* 分割整数构成字母字符串
namespace _91numDecoding
{
int numDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.length();
    vector<int> dp(n+1, 0);

    dp[0] = 1;
    dp[1] = 1;
    
    for (int i = 1; i < n; ++i) {
        if (s[i-1] == '1' || (s[i-1] == '2' && s[i] < '7')) {
            // 如果是20、10
            if (s[i] == '0') dp[i+1] = dp[i-1];
            else { // 11--19 21-26
                dp[i+1] = dp[i] + dp[i-1];
            }
        } else if (s[i] == '0') {
            return 0;
        } else {
            // i-1和i无法构成一个字母
            dp[i+1] = dp[i];
        }
    }

    return dp[n];
}
}

namespace _139workBreak 
{
bool wordBreak(string s, vector<string>& wordDict)
{
    int n = s.length();
    vector<char> dp(n+1, false);
    dp[0] = true;
    for (int  i = 1; i <= n; ++i) {
        for (const string& word : wordDict) {
            int len = word.length();
            if (i >= len && s.substr(i-len, len) == word) {
                dp[i] = dp[i] || dp[i-len];
            }
        }
    }
    return dp[n];
}
}

//!=================最长递增子序列===========================
namespace _300lengthOfLIS
{
int lengthOfLIS(vector<int>& nums) 
{
   int n = nums.size();
   // dp[i] 以nums[i]为尾的最长递增子序列长度
   vector<int> dp(n, 1);

   for (int i = 1; i < n; ++i) {
       for (int j = 0; j <i; ++j) {
           if (nums[i] > nums[j]) {
               dp[i] = std::max(dp[i], 1 + dp[j]);
           }
       }
   }
    return *std::max_element(dp.cbegin(), dp.cend());
}

int lengthOfLIS_1(vector<int>& nums)
{
    int len = 1, n = nums.size();
    if (n == 0) return 0;

    //! d[i] 长度为i的序列的最末尾元素的最小值
    vector<int> d(n+1, 0);
    d[len] = nums[0];
    //! 算法思想尽量保证长度为i的子序列末尾元素尽量小
    //!  如果nums[i] > d[len] 这直接加入d数组末尾 len = len+1, d[len] = nums[i]
    //! 否则在d数组中二分查找，找到第一个比nums[i]小的数d[k],并更新d[k+1] = nums[i]
    for (int i = 1; i < n; ++i) {
        if (nums[i] > d[len]) {
            d[++len] = nums[i];
        } else {
            // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
            int l = 0, r = len, pos = 0;
            while(l < r) {
                int mid = l + (r-l)/2;
                if (d[mid] < nums[i]) {
                    pos = mid;
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            d[pos + 1] = nums[i];
        }
    } 
    return len;
}

int lengthOfLIS_2(vector<int>& nums)
{
    int n = nums.size();
    if (n <= 1) return n;
    vector<int> d; d.reserve(n);
    d.push_back(nums[0]);

    for (int i = 1; i < n; ++i) {
        if (d.back() < nums[i]) {
            d.push_back(nums[i]);
        } else {
            auto itr = lower_bound(d.begin(), d.end(), nums[i]);
            *itr = nums[i];
        }
    }

    return d.size();
}

}

namespace _646findLongestChain
{
int findLongestChain(vector<vector<int>>& pairs) {
    int n = pairs.size();
    // dp[i]: 以pairs[i] 为尾的最长链
    vector<int> dp(n, 1);
    std::sort(pairs.begin(), pairs.end(), 
            [](const auto& v1,const auto& v2) {return v1[0] < v2[0];});
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (pairs[i][0] > pairs[j][1]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }
    return *std::max_element(dp.cbegin(), dp.cend());
}  

int findLongestChain_1(vector<vector<int>>& pairs)
{
    std::sort(pairs.begin(), pairs.end(),
        [](const auto& v1,const auto& v2) {return v1[1] < v2[1];});
    
    int cur = INT_MIN;
    int ans = 0;
    for (const auto& pair : pairs) {
        if (cur < pair[0]) {
            cur = pair[1];
            ++ans;
        }
    }
    return ans;
}
}

//* 摆动序列
namespace _376wiggleMaxLength
{
int wiggleMaxLength(vector<int>& nums) {
    // up[i]表示以前i个元素中的某一个为结尾的最长的 上升摆动序列 的长度
    // down[i]表示以前i个元素中的某一个文结尾的最长 下降摆动子序列 得长度
    int n = nums.size();
    if (n < 2) return n;

    vector<int> up(n), down(n);
    up[0] = down[0] = 1;
    for (int i = 1; i < n; ++i)
    {
        if (nums[i] > nums[i-1]) {
            up[i] = max(up[i-1], down[i-1]+1);
            down[i] = down[i-1];
        } else if (nums[i] < nums[i-1]) {
            up[i] = up[i-1];
            down[i] = max(up[i-1]+1, down[i-1]);
        } else {
            up[i] = up[i-1];
            down[i] = down[i-1];
        }
    }
    return max(up[n-1], down[n-1]);
}

int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return n;

    int prevdiff = nums[1] - nums[0];
    int ret = prevdiff != 0 ? 2 : 1;
    for (int i = 2; i < n; ++i) {
        int diff = nums[i] - nums[i-1];
        if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0)) {
            ++ret;
            prevdiff = diff;
        }
    }
    return ret;
}
}

namespace _354maxEnvelopes {

int maxEnvelopes(vector<vector<int>>& envelopes)
{
    if (envelopes.empty()) {
        return 0;
    }
    
    std::sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
        return e1[0]<e2[0] || (e1[0] == e2[0] && e1[1]>e2[1]);
    });

    int n = envelopes.size();
    vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (envelopes[j][1] < envelopes[i][1]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
    }

    return *max_element(dp.cbegin(), dp.cend());
}

}
//!==================最长公共子序列==========================
namespace _1143longestCommonSubsequence
{
// 定义：计算 s1[i..] 和 s2[j..] 的最长公共子序列长度
/* int dp(vector<vector<int>>& memo, const string& s1, int i, const string& s2, int j)
{
    if (i == s1.size() || j == s2.size()) return 0;

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    if (s1[i] == s2[j]) {
        memo[i][j] = 1 + dp(memo, s1, i+1, s2, j+1);
    } else {
        memo[i][j] = std::max(
            dp(memo, s1, i+1, s2, j),
            dp(memo, s1, i, s2, j+1)
        );
    }
    return memo[i][j];
}

int longestCommonSubsequence(string text1, string text2) 
{
    vector<vector<int>> memo(text1.size(), vector<int>(text2.size(), -1));
    return dp(memo, text1, 0, text2, 0);
} */

int longestCommonSubsequence(const string& text1,const string& text2) 
{
    // 定义：s1[0..i-1] 和 s2[0..j-1] 的 lcs 长度为 dp[i][j]
    // 目标：s1[0..m-1] 和 s2[0..n-1] 的 lcs 长度，即 dp[m][n]
    // base case: dp[0][..] = dp[..][0] = 0
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i-1] == text2[j-1]) {
                // s1[i-1] 和 s2[j-1] 必然在 lcs 中
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                // s1[i-1] 和 s2[j-1] 至少有一个不在 lcs 中
                dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }
    return dp[m][n];
}
}

//* 两个字符串的删除操作
namespace _583minDistance
{
int minDistance(const string& word1, const string& word2)
{
    int m = word1.size();
    int n = word2.size();

    // 求出最长公共子串
    vector<vector<int>>dp(m+1, vector<int>(n+1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return m-dp[m][n] + n-dp[m][n];
}
}

//*  两个字符串的最小ASCII删除和
namespace _712minimumDeleteSum
{
int minimumDeleteSum(const string& s1, const string& s2)
{
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MAX));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[0][i] = dp[0][i-1] + s2[i-1];
    }
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = dp[i-1][0] + s1[i-1];
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = std::min(
                        dp[i-1][j] + s1[i-1],
                        dp[i][j-1] + s2[j-1]
                );
            }
        }
    }

    return dp[m][n];
}
}


//!===================最长回文子序列=========================
namespace _516longestPalindromeSubseq {
int longestPalindromeSubseq(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j-1]+2;
            } else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    return dp[0][n-1];
}
}

//!================================ 字符串编辑 ==================================

//*将s1转换为s2所用的最少操作数
//dp(i, j) 返回s1[0..i)和s2[0..j)的最小编辑距离

namespace _72minDistance
{
vector<vector<int>> memo;
string_view sv1;
string_view sv2;
int maxLimit;
int dp(int i, int j)
{
    // 添加
    if (0 == i) {
        memo[0][j] = j;
        return memo[0][j];
    }
    // 删除
    if (0 == j) {
        memo[i][0] = i;
        return memo[i][0];
    }

    if (maxLimit != memo[i][j]) {
        return memo[i][j];
    }

    if (sv1[i-1] == sv2[j-1]) {
        memo[i][j] = dp(i-1, j-1);
    } else 
    {
        memo[i][j] = std::min({
            dp(i, j-1) + 1, // 插入
            dp(i-1, j) + 1, // 删除
            dp(i-1, j-1)+1  // 替换
        });
    }
    return memo[i][j];
}

int minDistance(string word1, string word2)
{
    int len1 = word1.size();
    int len2 = word2.size();
    sv1 = word1;
    sv2 = word2;
    vector<vector<int>>(len1+1, vector(len2+1, maxLimit)).swap(memo);
    return dp(len1, len2);
}

int minDistance(const string& word1, const string& word2)
{
    int len1 = word1.size();
    int len2 = word2.size();

    vector<vector<int>> dp(len1+1, vector(len2+1, std::max(len1, len2)+1));
    for (int i = 0; i <= len1; ++i) {
        dp[i][0] = i; // s2[0,0)为空,s1[0,i)只能全删除
    }
    for (int i = 0; i <= len2; ++i) {
        dp[0][i] = i; // s1[0,0)为空，只能添加成为s2[0, i)
    }

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if(word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = std::min({
                    dp[i][j-1] + 1, // 添加
                    dp[i-1][j] + 1, // 删除
                    dp[i-1][j-1] + 1 // 改
                });
            }
        }
    }
    return dp[len1][len2];
}
}


namespace _650minSteps
{
int minSteps(int n) {
    vector<vector<int>> dp(n+1, vector(n+1, n+1));
   dp[1][0] = 0;
    dp[1][1] = 1;

    for (int i = 1; i < n+1; ++i) {
        int minStep = dp[i][0];
        for (int j = 1; j <= i; ++j) {
            if (i > j) {
                dp[i][j] = min(dp[i-j][j]+1, dp[i][j]);
                minStep = min(minStep, dp[i][j]);
            } else if (i == j) {
                dp[i][j] = minStep + 1;
            }
        }
    }
    return dp[n][n] - 1;
}

int minSteps(int n) {
    vector<int> dp(n+1);
    int h = sqrt(n);

    for (int i = 2; i <= n; ++i) {
        dp[i] = i;
        for (int j = 2; j <= h; ++j) {
            if (i % j == 0) {
                dp[i] = dp[j] + dp[i/j];
                break;
            }
        }
    }
    return dp[n];
}

}

//!================================= 正则表达式 ==================================
namespace _10isMatch
{
// if (p[j] != '*) 
//      if matches(s[i], p[j]) dp[i][j] = dp[i-1][j-1]
//      else false
// else
//      if match(s[i], p[j-1]) dp[i][j] = dp[i-1][j] or dp[i][j-2] 要么丢弃s[i]要么丢弃p[j-1]*
//      else dp[i][j] = dp[i][j-2];
bool isMatch(string s, string p)
{
    int m = s.size(), n = p.size();
    vector<vector<char>> dp(m+1, vector<char>(n+1, false));
    dp[0][0] = true;
    // 以1开始
    auto matches = [&](const int i, const int j) {
        if (i == 0) {
            return false;
        }
        if (p[j-1] == '.') {
            return true;
        }
        return s[i-1] == p[j-1];
    };

    for (int i = 0; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (p[j-1] == '*') {
                dp[i][j] |= dp[i][j-2]; // 忽略 x*
                if (matches(i, j-1)) {
                    dp[i][j] |= dp[i-1][j]; // 继续使用'*'前面的那个字母
                }
            } else {
                if (matches(i, j)) {
                    dp[i][j] |= dp[i-1][j-1];
                }
            }
        }
    }
    return dp[m][n];
}

}


namespace _64minPathSum
{
int minPathSum(vector<vector<int>>& grid)
{
    int m = grid.size(), n = grid[0].size();
    // 从左上角到(i, j)的路径之和
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];

    for (int i = 1; i < n; ++i) {
        dp[0][i] = dp[0][i-1] + grid[0][i];
    }
    for (int i = 1; i < m; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[m-1][n-1];
}
}

//!==================================打家劫舍======================================
namespace __198rob {
// dp[i], 抢劫[0, ..., i]能获得的最大值
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < nums.size(); ++i) {
        dp[i] = max(dp[i-2] + nums[i], dp[i-1]);
    }
    return dp.back();
}
}

namespace __213rob {
// 198rob状态压缩得到
int robRange(vector<int>& nums, int start, int end) {
    int first = nums[start], second = max(nums[start], nums[start+1]);
    for (int i = start+2; i <= end; ++i) {
        int temp = second;
        second = max(first+nums[i], second);
        first = temp;
    }
    return second;
}

int rob(vector<int>& nums) {
    int len = nums.size();
    if (len == 1) {
        return nums[0];
    } else if (len == 2) {
        return max(nums[0], nums[1]);
    }
    return max(robRange(nums, 0, len-2), robRange(nums, 1, len-1));
}
}

namespace _337rob {
//! f(o)强o节点，g(o)不强o节点
//* f(o) = g(l) + g(r); g(o) = f(l) + f(r)

unordered_map<TreeNode*, int> f, g;
void dfs(TreeNode* node) {
    if (!node) return;

    dfs(node->left);
    dfs(node->right);
    f[node] = node->val + g[node->left] + g[node->right];
    g[node] = f[node->left] + f[node->right];
}

int rob(TreeNode* root) {
    dfs(root);
    return max(f[root], f[root]);
}
}

//! 剑指offer60投掷骰子
namespace _offer60 {
    vector<double> dicesProbability(int n) {
        vector<vector<int>> dp(n+1, vector<int>(6*n+1));
        for (int i = 1; i <= 6; ++i) {
            dp[1][i] = 1;
        }

        for (int i = 2; i <= n; ++i) {
            for (int j = i; j <= 6*i; ++j) {
                for (int cur = 1; cur <= 6; ++cur) {
                    if (j - cur <= 0) {
                        break;
                    }
                    dp[i][j] += dp[i-1][j-cur];
                }
            }
        }

        double all = 1.0 / pow(6, n);
        vector<double> ret; ret.reserve(5*n + 1);
        for (int i = n ; i <= 6*n; ++i) {
            ret.push_back(dp[n][i] * all);
        }
        return ret;
    }
}
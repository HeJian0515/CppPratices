#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <deque>
#include <array>
#include <unordered_set>
using namespace std;

//!====================0-1背包问题=================================================
namespace _01pack {
    // W：背包总体积 N:物品数量
    // dp(i, w):对于前i个物品，当前背包的容量为w，这种情况下可以装的最大价值是dp(i,w)。
    int knapsack(int W, int N, const vector<int>& wt, const vector<int>& val) {
        // vector 全填入0，base case 已初始化
        vector<vector<int>> dp(N+1, vector<int>(W+1,0));
        for (int i = 1; i <= N; ++i) {
            for (int w = 1; w <= W; ++w) {
                if (w - wt[i -1] < 0) { //! 当前背包容量装不下，只能选择不背包
                    dp[i][w] = dp[i - 1][w];
                } else {
                    // 装入或不装入背包，择优
                    dp[i][w] = std::max(dp[i-1][w - wt[i-1]] + val[i-1], dp[i-1][w]);
                }
            }
        }
        return dp[N][W];
    }
}

//* 划分数组为和相等的两部分
namespace _416DivideArray {
bool canPartition(vector<int>& nums) {
    int n = nums.size(); 
    if (n < 2) return false;
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 == 1) return false;
    sum /= 2;    

    // dp[i][j]：能否选择[0, i)之中的数，使之和为j
    vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false)); 
    for (int i = 0; i <=n; ++i){
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= sum; ++j) {
            if (j >= nums[i - 1]) {
                dp[i][j] = (dp[i-1][j] || dp[i-1][j - nums[i-1]]); 
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
}
}

//* 改变一组数的正负号使得它们的和为一给定数
namespace _494findTargetSumWays
{
int findTargetSumWays(vector<int>& nums, int S) {
    int nOrigin = nums.size();
    nums.erase(std::remove_if(nums.begin(), nums.end(),
            [](int x) { return x == 0;}), 
                                            nums.end());
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if(sum < abs(S) || (sum + S) % 2 == 1) {
        return 0;
    }
    
    sum = (sum + S) / 2;
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(sum+1, 0));
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= sum; ++j) {
            if (j < nums[i-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
            }
        }
    }
    return  dp[n][sum] * (1 << (nOrigin - n));
}
}


//* 多维 0-1 背包问题
namespace _474findMaxForm
{
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m+1, vector(n+1, 0));

    for (int k = 0; k < strs.size(); ++k) 
    {
        int zeros = std::count_if(strs[k].begin(), strs[k].end(), 
                                        [](const char ch) {return '0' == ch;});
        int ones = strs[k].size() - zeros;
        for (int i = m; i >= 0; --i) {
            for (int j = n; j >= 0; --j) {
                if (zeros <= i && ones <= j) {
                    dp[i][j] = std::max(dp[i][j], 1+ dp[i -zeros][j-ones]);
                }
            }   
        }
    }
    return dp[m][n];
}

int findMaxForm_1(vector<string>& strs, int m, int n)
{
    // dp[i][j]使用i个0和j个1，最多能拼出字符串的数目
    vector<vector<int>> dp(m+1, vector(n+1, 0));
    for (const string& str: strs)
    {
        int zeros = std::count_if(str.begin(), str.end(), 
                [](const char ch) {return '0' == ch;});
        int ones = str.size() - zeros;
        for (int mm = m; mm >= zeros; --mm) {
            for (int nn = n; nn >= ones; --mm) {
                dp[mm][nn] = std::max( dp[mm][nn],
                    1 + dp[mm - zeros][nn - ones]
                );
            }
        }
    }
    return dp[m][n];
}
}



//!=================硬币--完全背包问题=========================

//* 找零钱的最少硬币数
namespace _322coinChange
{
// dp[i][j]:使用前i种物品，最少使用多少个硬币
int coinChange_Orgin(vector<int>& coins, int amount)
{
    int m = coins.size();
    vector<vector<int>> dp(m+1, vector<int>(amount+1, amount+1));

    for (int i = 0; i <= m; ++i) {
        dp[i][0] = 0;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= amount; ++j) {
            if (j < coins[i-1]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j]);
            } else {
                dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i-1]]);
            }
        }
    }

    return dp[m][amount] == amount+1 ? -1 : dp[m][amount];
}

int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, amount+1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (const int coin : coins) {
            if (i >= coin){
                dp[i] = std::min(dp[i], 1+dp[i-coin]);
            } 
        }
    }
    return amount+1 == dp[amount] ? -1 : dp[amount];
}

int coinChange_1(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, amount+1);
    dp[0] = 0;
    for (int coin : coins) {
        for (int i = coin; i <=amount; ++i) {
            if (i == coin) {
                dp[i] = 1;
            } else {
                dp[i] = std::min(dp[i], dp[i-coin] + 1);
            }
        }
    }
    return dp[amount] == amount+1 ? -1 : dp[amount];
}
}

//! 凑硬币的方法总数
namespace _518change
{
int change(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<vector<int>> dp(n+1, vector<int>(amount+1));
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }

    for (int i = 1;  i <= n; ++i) {
        for (int j = 1; j <= amount; ++j) {
            if (j >= coins[i-1]) {
                dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][amount];
}

int change_1(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= amount; ++j) {
            if (j >= coins[i-1])  {
                dp[j] = dp[j] + dp[j - coins[i-1]];
            }
        }
    }
    return dp[amount];
}

}

//!==================带排列的完全背包问题==================================
namespace _139wordBreak
{
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string_view> wordDictSet(wordDict.cbegin(), wordDict.cend());
    string_view sv{s};

    int n = s.length();
    // dp[i] : 表示字符串 s 前 i个字符组成的字符串 s[0..i-1] 是否能被空格拆分成若干个字典中出现的单词。
    vector<bool> dp(n+1, false);
    dp[0] = true;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && wordDictSet.count(sv.substr(j, i-j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}
}

namespace _377combinationSum4
{
int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target+1, 0);
    dp[0] = 1;
    for (int i = 0; i <= target; ++i) {
        for (int j = 0; j <nums.size() ; ++j) {
            if (i - nums[i] >= 0 && dp[i] < INT_MAX - dp[i-nums[j]])
                    dp[i] += dp[i - nums[j]];
        }
    }
    return dp[target];
}
}

//! ================= 数组划分==========================================
// 从数组中划分出两堆，让他们差最小
namespace _1049lastStoneWeightII
{
int lastStoneWeightII(vector<int>& stones)
{
    int sum = accumulate(stones.cbegin(), stones.cend(), 0);
    const int n = stones.size(), m = sum/2;
    vector<vector<char>> dp(n+1, vector<char>(m+1));
    dp[0][0] = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j < stones[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = dp[i][j] || dp[i][j-stones[i]];
            }
        }
    }

    for (int j = m; ; --j) {
        if (dp[n][j]) {
            return sum - 2*j;
        }
    }
}
}
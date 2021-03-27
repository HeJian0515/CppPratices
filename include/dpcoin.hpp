#pragma once 
#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_set>
#include <limits>

using namespace std;

int coinChange(vector<int>& coins, int amount);
int dp(vector<int>& coins,vector<int>& memo, int n);

int coinChange(vector<int>& coins, int amount) {
    if (amount < 0) return -1;
    vector<int> dp(amount + 1, amount + 1); 
    // base case
    dp[0] = 0;
    // 外层 for 循环在遍历所有状态的所有取值
    for (int i = 0; i < dp.size(); ++i) {
        // 内层 for 循环在求所有选择的最小值
        for (int coin : coins) {
            // 子问题无解，跳过
            if (i - coin < 0) continue;
            dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
    }

    return (dp[amount] == amount + 1) ? -1 : dp[amount];
}



// int coinChange(vector<int>& coins, int amount) {
    
//     vector<int> memo(amount + 1,-1);
//     return dp(coins, memo, amount);

// }

int dp(vector<int>& coins,vector<int>& memo, int n) {
    if (n == 0) return 0; // 递归基
    if (n < 0) return -1;
    int res = INT_MAX;
    if ( memo[n] != -2) {
        return memo[n];
    }
        for (int coin : coins) {
            int subProblem = dp(coins, memo, n - coin);
            if (subProblem == -1) continue;
            res = min(res, subProblem + 1);
        }
        
    
    res = (res != INT_MAX ? res : -2);
    return memo[n] = res;
  }


//!=================硬币--完全背包问题=========================

//* 找零钱的最少硬币数
namespace _322coinChange
{
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

namespace _518change
{
int change(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<vector<int>> dp(n+1, vector(amount+1, 0));
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
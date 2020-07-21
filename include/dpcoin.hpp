#pragma once 
#include <algorithm>
#include <vector>
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



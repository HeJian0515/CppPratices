// 斐波那契数列 + 备忘录
#pragma once
#include <vector>

using namespace std;

int helper(vector<int>& memo, int n);
int fib(int N);
int fib_dpTable(int N);
int fib_dpTable_only2states(int N);

int fib(int N) {
    if (N < 1) return 0;
    // 备忘录全初始化为0
    vector<int> memo(N + 1, 0);
    // 进行带备忘录的递归
    return helper(memo, N);
}

int helper(vector<int>& memo, int n) {
    // base case 递归基
    if (n == 1 || n == 2) return 1;
    // 已经计算过的
    if (memo[n] != 0) return memo[n];
    memo[n] = helper(memo,n - 1) + helper(memo, n - 2);
    return memo[n];
}

int fib_dpTable(int N) {
    vector<int> dp(N + 1, 0);
    // base case
    dp[1] = dp[2] = 1;
    for (int i = 3; i <= N; i++)
        dp[i] = dp[i-1] + dp[i-2];
    return dp[N];
}

int fib_dpTable_only2states(int N) {
    if (N == 2 || N == 1)
        return 1;
    int prev = 1, curr = 1;
    for (int i = 3; i <= N; ++i) {
        int sum = prev + curr;
        prev = curr;
        curr = sum;
    }
    return curr;
}

//!====================== 斐波那契数列================================
namespace _70climbStairs
{
int climbStairs(int n) {
    int f1 = 1;
    int f2 = 2;
    for (int i = 3; i <= n; ++i) {
        int tmp = f1 + f2;
        f1 = f2;
        f2 = tmp;
    }
    return 1 == n ? f1 : f2;
}
}

namespace _198rob
{
int rob(vector<int>& nums) {
    int pre1 = 0;
    int pre2 = 0;
    for (int i = 0, n = nums.size(); i < n; ++i) {
        int cur = std::max(pre1 + nums[i], pre2);
        pre1 = pre2;
        pre2 = cur;
    }
    return pre2;
}
}

namespace _213rob
{
int myRob(vector<int>& nums, int first, int last) {
    int pre1 = 0;
    int pre2 = 0;
    for (int i = first; i <= last; ++i) {
        int cur = std::max(pre1 + nums[i], pre2);
        pre1 = pre2;
        pre2 = cur;
    }
    return pre2;
}
int rob(vector<int>& nums) {
    int n = nums.size();
    if (0 == n) return 0;
    if (1 == n) return nums[0];
    // 第0位和第n-1位不能同时取
    return std::max(myRob(nums, 0, n - 2), myRob(nums, 1, n -1));
}
}
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


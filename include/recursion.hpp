#pragma once
#include <vector>
using namespace std;

namespace _70recur {

    int helper (int n) {
        if (n == 1) return 1;
        else if (n == 2) return 2;
        else return helper(n - 1) + helper(n-2); 
    }
    int helper(vector<int>& memo, int n ) {
        for (int i = 3; i < memo.size(); ++i) {
            memo[i] = memo[i-1] + memo[i-2];
        }
        return memo[n];
    }
    int climbStairs(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        vector<int> memo(n+1, 0);
        memo[1] = 1;
        memo[2] = 2;
        return helper(memo, n);
    }
}
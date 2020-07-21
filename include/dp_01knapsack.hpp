#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <array>
using namespace std;


namespace _01pack {
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

namespace _416DivideArray {
    bool canPartition(vector<int>& nums) {
        if (nums.size() == 1 && nums[0] != 0) return false;
        int sum = 0;
        for (int num : nums) sum += num;
        if (sum % 2 != 0) return false; 
        int target = sum / 2;
        vector<deque<bool>> dp(nums.size()+1, deque<bool>(target+1, false));
        dp[0][0] = true;
        // 元素从第一个到第n个
        // 容量从0到target

        for (int i = 1; i <= nums.size(); ++i) {
            for (int j = 0; j <= target; ++j) {
                if (j >= nums[i-1])
                    dp[i][j] = dp[i-1][j] || dp [i-1][j - nums[i-1]];
                else
                    dp[i][j] = dp[i-1][j];
            }
        }
        return dp[nums.size()][target];
    }
}
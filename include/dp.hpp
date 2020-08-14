#pragma once
#include <limits.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

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

namespace _1143lcs {  //! 1143. 最长公共子序列

int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));

    for (int i = 1; i < text1.size() + 1; ++i) {
        for (int j = 1; j < text2.size() + 1; ++j) {
            if (text1[i - 1] == text2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[text1.size()][text2.size()];
}
}  // namespace _1143lcs

namespace _200lis {  //! 300. 最长上升子序列

int lengthOfLIS(vector<int>& nums) {
    vector<int> dp(nums.size(), 1);
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i])
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }
    int res = 0;
    for (int i = 0; i < dp.size(); ++i) {
        res = std::max(res, dp[i]);
    }
    return res;
}
}  // namespace _200lis

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

namespace _279Square {  //! 279. 完全平方数
int numSquares(int n) {
       vector<int> dp(n + 1, n);
        dp[0] = 0;
        dp[1] = 1;
    for (int i = 1; i <= n; ++i) {
        int max = static_cast<int>(std::sqrt(i));
        for (int j = 1; j <= max; ++j) {
            dp[i] = std::min(dp[i], dp[i-j*j]);
        }
        dp[i]+=1;
    }
    return dp[n];
}
}  // namespace _279Square
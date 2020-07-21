#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;


int minimumTotal(vector<vector<int>>& triangle) {
    int level = triangle.size();
    vector<vector<int>> dp(level, vector<int>(level));
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < level; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0){
                dp[i][j] = dp[i-1][j] + triangle[i][j];
            } else if (j == triangle[i].size()-1) {
                dp[i][j] = dp[i-1][j-1] + triangle[i][j];
            } else {
                dp[i][j] = std::min(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
            }  
        }
    }
    return *min_element(dp[level-1].begin(), dp[level-1].end());
}

int minimumTotal2(vector<vector<int>>& triangle) {
    int level = triangle.size();
    vector<int> dp(level,0);
    dp[0] = triangle[0][0];
    for (int i = 1; i < level; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j == 0) {
                dp[j] = dp[j] + triangle[i][j];
            } else if(j == i) {
                dp[j] = dp[j-1] + triangle[i][j];
            } else {
                dp[j] = std::min(dp[j-1], dp[j]) + triangle[i][j];
            }
        }
    }
    return *min_element(dp.begin(), dp.end());
}

int main() {
}
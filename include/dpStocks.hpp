#pragma once
#include <vector>
#include <array>
#include <limits>
using namespace std;

namespace _121dpStocks { //! 121. 买卖股票的最佳时机
    int maxProfit(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
        vector<vector<int>> dp(days, vector<int>(2, 0));
        dp[0][1] = -prices[0]; // 表示第0天买股票获得的利润
        for (int i = 1; i < days; ++i) {
            // 第i天获取的最大利润(没有买入)= max{前一天没买股票，前一天抛售股票} 
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][1] + prices[i]);
            // 第i天获取的最大利润(买入) = max{前一天已经买入， 现在才买入}
            dp[i][1] = std::max(dp[i-1][1], -prices[i]);
        }
        return dp[days-1][0];
    }

    int maxProfit2(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
        int dp_i_0 = 0;
        int dp_i_1 = -prices[0]; // 表示第0天买入股票获得的利润
        for (int i = 1; i < days; ++i) {
            // 第i天获取的最大利润(没有买入)= max{前一天没买股票，今天抛售股票} 
            dp_i_0 = std::max(dp_i_0, dp_i_1+prices[i]);
            // 第i天获取的最大利润(买入) = max{前一天已经买入， 现在才买入}
            dp_i_1 = std::max(dp_i_1, -prices[i]);
        }
       return dp_i_0;
    }
}

namespace _122dpStocks { //! 122. 买卖股票的最佳时机 II
     int maxProfit(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
        vector<vector<int>> dp(prices.size(), vector<int>(2,0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for (int i = 1; i < days; ++i) {
            dp[i][0] = std::max(dp[i-1][0], dp[i-1][1]+prices[i]);
            dp[i][1] = std::max(dp[i-1][1], dp[i-1][0]-prices[i]);
        }
        return dp[days-1][0];
    }

    int maxProfit2(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
        int dp_i_0 = 0;
        int dp_i_1 = -prices[0];
        for (int i = 1; i < days; ++i) {
            int tmp = dp_i_0;
            dp_i_0 = std::max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = std::max(dp_i_1, tmp - prices[i]);
        }
        return dp_i_0;
    }
}

namespace _123dpStocks { //! 123. 买卖股票的最佳时机 III
    int maxProfit(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
        vector<vector<vector<int>>> dp(days, vector<vector<int>>(3, vector<int>(2, 0)));
        for (int i = 0; i < days; ++i) {
            for (int k = 2; k >=1; --k) {
                if (i - 1 == -1)  { /*处理 base case */
                    dp[i][k][0] = 0;
                    dp[i][k][1] = -prices[0];
                    continue;
                }
                dp[i][k][0] = std::max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                dp[i][k][1] = std::max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);
            }
        }
        return dp[days-1][2][0];
    }

    int maxProfit2(vector<int>& prices) {
        int days = prices.size();
        if (days < 1) return 0;
       int dp_i10 = 0, dp_i11 = INT_MIN;
       int dp_i20 = 0, dp_i21 = INT_MIN;
       for (int price : prices) {
           dp_i20 = std::max(dp_i20, dp_i21 + price);
           dp_i21 = std::max(dp_i21, dp_i10 - price);
           dp_i10 = std::max(dp_i10, dp_i11 + price);
           dp_i11 = std::max(dp_i11, - price);
          
       }
       return dp_i20;
    }
}
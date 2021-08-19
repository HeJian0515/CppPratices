#pragma once
#include <iostream>
#include <unordered_map>
#include <utility>
#include <limits.h>
#include <tuple>
using namespace std;

namespace _887egg { //! 887. 鸡蛋掉落

    struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 
    unordered_map<pair<int,int>,int> memo;
    int dp(int K, int N) {
        // 递归基
        if (K == 1) return N; // 只有一个鸡蛋
        if (N == 0) return 0; // 0层

        // 避免重复计算
        pair<int, int> key(K, N);
        if (memo.find(key) != memo.end())  return memo[key];
        int res = INT_MAX;

        // 穷举所有的可能的选择
        for (int i = 1; i < N + 1; ++i) {
            // 在第i层扔，碎与不碎
            res = min(res, max(dp(K, N - i), dp(K-1, i-1))+1);
        }
        // 记录备忘录
        memo[pair<int,int> (K, N)] = res;
        return res;
    }

     int superEggDrop(int K, int N) {
         return dp(K, N);
    }
namespace _1 {
    unordered_map<int, int> memo;
    int dp(int k, int n) {
        if (memo.find(n*100+k) == memo.end()) {
            int ans;
            if (n == 0) {
                ans = 0;
            } else if (k == 1) {
                ans = n;
            } else {
                int lo = 1, hi = n;
                while (lo + 1 < hi) {
                    int x = (lo + hi) / 2;
                    int t1 = dp(k - 1, x - 1);
                    int t2 = dp(k, n - x);

                    if (t1 < t2) {
                        lo = x;
                    } else if (t1 > t2) {
                        hi = x;
                    } else {
                        lo = hi = x;
                    }
                }
                ans = 1 + min( max(dp(k-1, lo-1), dp(k, n - lo)), 
                               max(dp(k-1, hi-1), dp(k, n - hi)) );
            }
            memo[n * 100+ k] = ans;
        }
        return memo[n* 100 + k];
    }
    
    int superEggDrop(int k, int n) {
        return dp(k, n);
    }
}
}
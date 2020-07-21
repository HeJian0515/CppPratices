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
            res = min(res, max(dp(K, N - i), dp(K-1, i-1))+1);
        }
        // 记录备忘录
        memo[pair<int,int> (K, N)] = res;
        return res;
    }

     int superEggDrop(int K, int N) {
         return dp(K, N);
    }
}
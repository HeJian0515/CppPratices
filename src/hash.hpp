#pragma once
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>


using namespace std;

namespace _596findLHS {
    //! 找到x和x+1的个数即可
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> counter;
        for (int i : nums) ++counter[i];

        int ans = 0;
        for (auto& p : counter) {
            if (counter.count(p.first+1)) {
                ans = max(ans, p.second+ counter[p.first+1]);
            }
        }
        return ans;
    }

namespace _1 {
    //! 单次扫描
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> hash;
        int ans = 0;
        for (int num : nums) {
            ++hash[num];
            if (hash.count(num+1)) {
                ans = max(ans, hash[num] + hash[num+1]);
            }
            if (hash.count(num-1)) {
                ans = max(ans, hash[num] + hash[num-1]);
            }
        }
        return ans;
    }
}
}

namespace _128longestConsecutive {

int forward(unordered_map<int, int>& hash, int num) {
    if (!hash.count(num)) return 0;

    int cnt = hash[num];
    if (cnt > 1) return cnt;

    cnt = forward(hash, num+1) + 1;
    hash[num] = cnt;
    return cnt;
}

int maxCount(unordered_map<int, int>& hash) {
    int max = 0;
    for (auto& p : hash) {
        max = std::max(max, p.second);
    }
    return max;
}

int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> hash;
    for (int num : nums) hash[num] = 1;

    // 更新哈希表-->哈希表的意义变为以num开头的最长连续序列
    for(int num : nums) {
        forward(hash, num);
    }

    return maxCount(hash);
}
namespace _1 {
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.cbegin(), nums.cend());

        int ans = 0;
        for (const int& num : numSet) {
            //* 必须从一个新的数字开始 -—— 遍历num-1时，已经遍历过num了
            if (!numSet.count(num-1)) {
                int curNum = num;
                int curLen = 1;

                while (numSet.count(curNum+1)) {
                    ++curNum;
                    ++curLen;
                }
                ans = max(ans, curLen);
            }
        }
        return ans;
    }
}
}

namespace _1418displayTable {
vector<vector<string>> displayTable(vector<vector<string>>& orders)
{
    set<string> nameSet;
    map<int, unordered_map<string, int>> foodsCnt;

    for (auto& order : orders) {
        nameSet.insert(order[2]); // 统计餐品的名字

        int id = stoi(order[1]);
        ++foodsCnt[id][order[2]]; // 记录id号餐桌有餐品数量
    }

    vector<vector<string>> tables(foodsCnt.size()+1, vector<string>(nameSet.size()+1));
    tables[0][0] = "Table"s;
    copy(nameSet.begin(), nameSet.end(), tables[0].begin()+1);

    int row = 1;
    for (auto iter = foodsCnt.begin(); iter != foodsCnt.end(); ++iter) {
        tables[row][0] = to_string(iter->first);
        int col = 1;
        for (auto& name : nameSet) {
            tables[row][col] = to_string(iter->second[name]);
            ++col;
        }
        ++row;
    }
    return tables;

}
}
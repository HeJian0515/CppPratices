/*
 * @Author: He Jian
 * @Date: 2020-06-30 21:47:59
 * @LastEditTime: 2020-06-30 22:16:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \CPP\include\trackback.hpp
 */
#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <deque>
#include <numeric>
#include <functional>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//todo=============================================================================================
namespace _112Tree {  //! 112. 路径总和

bool backTrack(TreeNode* root, int sum) {
    // 结束条件
    if (root->left == nullptr && root->right == nullptr && sum - root->val == 0)
        return true;
    else if (root->left != nullptr && root->right != nullptr)
        return (backTrack(root->left, sum - root->val) || backTrack(root->right, sum - root->val));
    else if (root->right != nullptr)
        return backTrack(root->right, sum - root->val);
    else if (root->left != nullptr)
        return backTrack(root->left, sum - root->val);
    else
        return false;
}

bool hasPathSum(TreeNode* root, int sum) {
    if (root == nullptr) return false;
    return backTrack(root, sum);
}
}  // namespace _112Tree

//todo=============================================================================================
namespace _47back {  //!47. 全排列 II
vector<vector<int>> res;

void func(vector<int>& nums, vector<int>& current, vector<bool>& nums1) {
    if (current.size() == nums1.size())
        res.push_back(current);
    else {
        for (int i = 0; i < nums.size(); ++i) {
            //=====================================选择这一层=====================================
            // nums1[i]是记录对应位置的nums[i]是否被使用的bool数组
            // nums[i]没被上层选择则选择它
            if (nums1[i] == false) {
                // 当nums[i]与nums[i-1]相等且nums1[i-1]没有被选择
                // 因为此时选nums[i]和nums[i-1]都一样 所以只选第一个出现的 所以要对mums排序
                if (i > 0 && nums[i] == nums[i - 1] && nums1[i - 1] == false)  //! 除重
                    continue;
                current.push_back(nums[i]);
                nums1[i] = true;             //标记已被选择 下层不能重复选择nums[i]
                                             //=====================================选择这一层=====================================
                func(nums, current, nums1);  // 选择下层
                // 回退到这一层
                nums1[i] = false;
                current.pop_back();
            }
        }
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    if (nums.size() == 0)
        return {};
    else if (nums.size() == 1)
        return {{nums[0]}};
    else {
        vector<bool> nums1(nums.size(), false);
        vector<int> current;
        std::sort(nums.begin(), nums.end());
        func(nums, current, nums1);
        return res;
    }
}
}  // namespace _47back

//todo=============================================================================================
namespace _22bracket {
void backtrack(vector<string>& res, string& cur, int open, int close, int n) {
    if (cur.size() == 2 * n) {
        res.push_back(cur);
        return;
    }

    //? =================选择决策树下一层符号并减枝==========================
    if (open < n) {  //! 如果左括号数量不大于 n，我们可以放一个左括号
        cur.push_back('(');
        backtrack(res, cur, open + 1, close, n);
        cur.pop_back();
    }
    if (close < open) {  //! 如果右括号数量小于左括号的数量，我们可以放一个右括号。
        cur.push_back(')');
        backtrack(res, cur, open, close + 1, n);
        cur.pop_back();
    }
    //? =================选择决策树下一层符号并减枝==========================
}

vector<string> generateParenthesis(int n) {
    vector<string> res;
    string cur;
    backtrack(res, cur, 0, 0, n);
    return res;
}
}  // namespace _22bracket

//todo=============================================================================================
namespace _39backtrack {

void backtrack(vector<int>& candidates, vector<vector<int>>& res, vector<int>& track, int del) {
    if (del == 0) {
        res.push_back(track);
        return;
    }
    for (int select : candidates) {
        // del为离target的接近程度
        // 剪枝：1.当del 小于下一个选择时
        // 2.只选取的值从小到大排列的序列 防止产生[2,2,3]、[2,3,2]、[3,2,2]这样的重复结果
        if (del < select || (track.size() > 0 && select < track.back())) continue;
        del -= select;
        track.push_back(select);
        backtrack(candidates, res, track, del);
        track.pop_back();
        del += select;
    }
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> track;
    backtrack(candidates, res, track, target);
    return res;
}
}  // namespace _39backtrack


namespace _216backtrack {

void bcaktrack(vector<vector<int>>& res, vector<int>& trace, int k, int n) {
    if (trace.size() == k && n == 0) {
        res.push_back(trace);
    }

    for (int i = 1; i < 10; ++i) {
        //!===============================================================================
        if (n < 0 || (trace.size() > 0 && trace.back() >= i) || trace.size() > k) continue;
        //!===============================================================================
        trace.push_back(i);
        bcaktrack(res, trace, k, n - i);
        trace.pop_back();
    }
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> res;
    vector<int> trace;
    bcaktrack(res, trace, k, n);
    return res;
}

}  // namespace _216backtrack

namespace _351backtrack {  //! 351. 安卓系统手势解锁

// from为当先选中的点，to为下一个要选中的点
bool isValid(vector<bool>& isSelcet, int from, int to) {
    if (from == to) return false;
    int i = std::min(from, to), j = std::max(from, to);
    //! 1、9/3、7对角线 如果5被选择且to没被选择的话--合法
    if ((i == 1 && j == 9) || (i == 3 && j == 7)) return isSelcet[5] && !isSelcet[to];
    //! from、to在同一行 如果中间的被选择且to没被选择的话--合法
    if ((i == 1 || i == 4 || i == 7) && i + 2 == j) return isSelcet[i + 1] && !isSelcet[to];
    //! from、to在同一列 如果中间的被选择且to没被选择的话--合法
    if (i <= 3 && i + 6 == j) return isSelcet[i + 3] && !isSelcet[to];
    return !isSelcet[to];

    return false;
}

void backtrack(int m, int n, int count, vector<bool>& isSelected, int from, int& res) {
    if (count == n) {
        ++res;
        return;
    }
    if (count >= m) ++res;
    for (int i = 1; i < 10; ++i) {
        if (isValid(isSelected, from, i)) {
            isSelected[i] = true;
            backtrack(m, n, count + 1, isSelected, i, res);
            isSelected[i] = false;
        }
    }
}

int numberOfPatterns(int m, int n) {
    vector<bool> isSelected(10, false);
    int res = 0;
    for (int i = 1; i < 10; ++i) {
        isSelected[i] = true;
        backtrack(m, n, 1, isSelected, i, res);
        isSelected[i] = false;
    }
    return res;
}
}  // namespace _351backtrack

namespace _491findSubsequences {

class Solution {
   public:
    vector<vector<int>> ans;
    vector<int> temp;
    void dfs(int cur, int last, vector<int>& nums) {
        if (cur == nums.size()) {
            if (temp.size() >= 2) {
                ans.push_back(temp);
            }
            return;
        }

        if (nums[cur] >= last) {
            temp.push_back(nums[cur]);
            dfs(cur + 1, nums[cur], nums);
            temp.pop_back();
        }
        if (nums[cur] != last) {
            dfs(cur + 1, last, nums);
        }
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(0, INT_MIN, nums);
        return ans;
    }
};
}  // namespace _491findSubsequences

//*电话号码的组合
namespace _17LC {

void backtrack(vector<string>& combinations, const unordered_map<char, string> dic,
               const string& digits, int index, string& combination) {
    if (index == digits.length()) {
        combinations.emplace_back(combination);
    } else {
        char digit = digits[index];
        const string& letters = dic.at(digit);  // 根据数字找到对应字符
        for (auto letter : letters) {
            combination.push_back(letter);
            backtrack(combinations, dic, digits, index + 1, combination);
            combination.pop_back();
        }
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> combinations;
    if (digits.empty()) return combinations;

    unordered_map<char, string> dic{
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    string combination;
    backtrack(combinations, dic, digits, 0, combination);
    return combinations;
}

string tmp;
vector<string> res;
vector<string> board = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
void DFS(int pos, string digits) {
    if (pos == digits.size()) {
        res.push_back(tmp);
        return;
    }
    int num = digits[pos] - '0';
    for (int i = 0; i < board[num].size(); i++) {
        tmp.push_back(board[num][i]);
        DFS(pos + 1, digits);
        tmp.pop_back();
    }
}

vector<string> letterCombinations_1(string digits) {
    if (digits.size() == 0) return res;
    DFS(0, digits);
    return res;
}
}  // namespace _17LC

//*Ip地址划分
namespace _93LC {
static constexpr int SEG_COUNT = 4;
vector<string> ans;
vector<int> segments;

void dfs(const string& s, int segId, int segStart) {
    // 如果找到了4段IP地址并且遍历完了字符串，那么就是一种答案
    if (segId == SEG_COUNT) {
        if (segStart == s.size()) {
            // 拼接字符串
            string ipAddr;
            for (int i = 0; i < SEG_COUNT; ++i) {
                ipAddr += to_string(segments[i]);
                if (i != SEG_COUNT - 1) {
                    ipAddr += '.';
                }
            }
            ans.push_back(std::move(ipAddr));
        }
        return;
    }

    // 如果还没有找到 4 段 IP 地址就已经遍历完了字符串，那么提前回溯
    if (segStart == s.size()) return;

    //  由于不能有前导零，如果当前数字为 0，那么这一段 IP 地址只能为 0
    if (s[segStart] == '0') {
        segments[segId] = 0;
        dfs(s, segId + 1, segStart + 1);
    }

    // 一般情况，枚举每一种可能性并递归
    int addr = 0;
    for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {
        addr = addr * 10 + (s[segEnd] - '0');
        if (addr > 0 && addr <= 0xFF) {  // 截取的数字合法
            segments[segId] = addr;
            dfs(s, segId + 1, segEnd + 1);
        } else {
            break;
        }
    }
}
vector<string> restoreIpAddresses(string s) {
    segments.resize(SEG_COUNT);
    dfs(s, 0, 0);
    return ans;
}

//===================================================================================================================
int judgeIfIpSegment(const string& s, int left, int right) {
    int len = right - left + 1;
    // 大于 1 位的时候，不能以 0 开头
    if (len > 1 && s[left] == '0') return -1;

    // 转成int类型
    int res = 0;
    for (int i = left; i <= right; ++i) {
        res = res * 10 + (s[i] - '0');
    }
    if (res > 255) return -1;
    return res;
}

void dfs_1(const string& s, int len, int split, int begin, vector<string>& path, vector<string>& res) {
    if (begin == len) {
        if (split == 4) {
            // 拼接字符串
            string ipAddr;
            for (int i = 0; i < 4; ++i) {
                ipAddr += path[i];
                if (i != 3) {
                    ipAddr += '.';
                }
            }
            res.push_back(std::move(ipAddr));
        }
        return;
    }

    // 看到剩下的不够了，就退出（剪枝），len - begin 表示剩余的还未分割的字符串的位数
    if (len - begin < (4 - split) || len - begin > 3 * (4 - split)) {
        return;
    }

    for (int i = 0; i < 3; ++i) {
        if (begin + i >= len) {
            break;
        }

        int ipSegment = judgeIfIpSegment(s, begin, begin + i);
        if (ipSegment != -1) {
            // 在判断是 ip 段的情况下，才去做截取
            path.push_back(to_string(ipSegment));
            dfs_1(s, len, split + 1, begin + i + 1, path, res);
            path.pop_back();
        }
    }
}

vector<string> restoreIpAddresses_1(string s) {
    int len = s.size();
    vector<string> res;
    if (len < 4 || len > 12) return res;

    vector<string> path;
    int splitTimes = 0;
    dfs_1(s, len, splitTimes, 0, path, res);
    return res;
}
}  // namespace _93LC

//* 单词搜索
namespace _79LC {

void backtracking(int i, int j, vector<vector<char>>& board, string& word, 
    bool& find, vector<vector<char>>& visited, int pos)
{
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
        return;
    }

    if (visited[i][j] || find || board[i][j] != word[pos]) {
        return;
    }

    if (pos == word.size()-1) {
        find = true;
        return;
    }

    visited[i][j] = true;

    backtracking(i+1, j, board, word, find, visited, pos+1);
    backtracking(i-1, j, board, word, find, visited, pos+1);
    backtracking(i, j+1, board, word, find, visited, pos+1);
    backtracking(i, j-1, board, word, find, visited, pos+1);

    visited[i][j] = false;
}

bool exist(vector<vector<char>>& board, string word) {
    if (board.empty()) return false;
    int m = board.size(), n = board[0].size();
    vector<vector<char>> visited(m, vector<char>(n, false));
    bool find = false;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            backtracking(i, j, board, word, find, visited, 0);
        }
    }
    return find;
}
}  // namespace _79LC

//!==============================
namespace _47PermuteUnique{


}

// 组合
namespace _77Combine {
vector<vector<int>> ans;

void backtrack(int n, int k, int start, vector<int>& path)
{
    if (path.size() == k) {
        ans.push_back(path);
        return;
    }

    for (int i = start; i <= n; ++i)
    {
        path.push_back(i);
        backtrack(n, k, i+1, path);
        path.pop_back();
    }
}

vector<vector<int>> combine(int n, int k)
{   
    vector<int> path; path.reserve(k);
    backtrack(n, k, 1, path);
    return ans;
}
}

namespace _40backtrack {
vector<vector<int>> ans;

void backtrack(vector<int>& candidates, int index, vector<int>& path, int target)
{
    if (target == 0) {
        ans.push_back(path);
        return;
    }

    for (int i = index; i < candidates.size(); ++i) {
        if (candidates[i] > target) break;
        if (i > index && candidates[i-1] == candidates[i]) continue;

        path.push_back(candidates[i]);
        backtrack(candidates, i+1, path, target - candidates[i]);
        path.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<int> path;
    sort(candidates.begin(), candidates.end());
    backtrack(candidates, 0, path, target);
    return ans;
}
}  // namespace _40backtrack

//* 子集
namespace _78subsets
{
vector<vector<int>> ans;
void backtrack(const vector<int>& nums, vector<int>& path, int start)
{
    ans.push_back(path);

    for (int i = start; i < nums.size(); ++i) {
        path.push_back(nums[i]);
        backtrack(nums, path, i+1);
        path.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums)
{
    vector<int> path;
    backtrack(nums, path, 0);
    return ans;
}
}

//* n皇后问题
namespace _51solveNQueens
{
vector<string> generateBoard(vector<int>& queens, int n)
{
    vector<string> board(n, string(n, '.'));
    for (int i = 0;  i < n; ++i) {
        board[i][queens[i]] = 'Q';
    }
    return board;
}
void backtrack(vector<vector<string>>& ans, vector<int>& queens, 
                int n, int row, unordered_set<int>& col,
                unordered_set<int>& ddiag, unordered_set<int>& udiag)
{
   if (row == n) {
       ans.push_back(generateBoard(queens, n));
       return;
   } 

    for (int i = 0; i < n; ++i) { 
        if (col.count(i)) continue; // 同列已经有皇后

        int d = row - i;            
        if (ddiag.count(d)) continue; // 从左上角到右下角的对角线上有皇后

        int u = row + i;
        if (udiag.count(u)) continue; // 从左下角到右上角的对角线上有皇后

        queens[row] = i;
        col.insert(i);
        ddiag.insert(d);
        udiag.insert(u);

        backtrack(ans, queens, n, row+1, col, ddiag, udiag);

        queens[row] = -1;
        col.erase(i);
        ddiag.erase(d);
        udiag.erase(u);
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> ans;
    vector<int> queens(n, -1);
    unordered_set<int> col, ddiag, udiag;
    backtrack(ans, queens, n, 0, col, ddiag, udiag);
    
    return ans;
}
}


//! 划分子集
namespace _698canPartitionKSubsets
{
#if 1
bool canPartitionKSubsets(vector<int>& nums, int k)
{
    if (k == 1) return true;
    int sum = accumulate(nums.cbegin(), nums.cend(), 0);
    if (sum % k != 0) return false;

    int target = sum/k, n = nums.size();
    vector<int> bucket(k);
    sort(nums.begin(), nums.end(), greater<>());

    // 把第i个数放入桶中
    function<bool(int)> dfs = [&](int i) -> bool {
        if (i == n) return true;
        for (int j = 0; j < k; ++j)
        {
            if (nums[i] + bucket[j] <= target) {
                bucket[j] += nums[i];
                if (dfs(i+1)) return true;
                bucket[j] -= nums[i];
            }

            if (bucket[j] == 0) break;  // 后面的桶也是空桶，没有区别
        }
        return false;
    };

    return dfs(0);
}
#endif
}
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
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace _46back {  //! 46. 全排列

class Solution {
   private:
    // 路径：记录在track中
    // 选择列表：nums中不存在track的那些元素
    // 结束条件：nums中的元素全部都在track中
    void backtrack(vector<vector<int>>& res, vector<int>& nums, vector<int>& track) {
        // 触发结束条件
        if (track.size() == nums.size()) {
            res.push_back(vector<int>(track));
            return;
        }

        for (int i = 0; i < nums.size(); ++i) {
            // 排除不合法的选择
            if (std::find(track.begin(), track.end(), nums[i]) != track.end())
                continue;
            // 做选择
            track.push_back(nums[i]);
            // 进入下一层决策树
            backtrack(res, nums, track);
            // 取消选择
            track.pop_back();
        }
    }

   public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> track;

        backtrack(res, nums, track);
        return res;
    }
};
}  // namespace _46back

//todo=============================================================================================
namespace _51back {  //!  N皇后
class Solution {
   public:
    vector<vector<string>> res;
    bool isValid(vector<string>& board, int row, int col) {
        int n = board.size();  // 列数
        // 检查是否有皇后互相冲突
        for (int i = 0; i < n; ++i) {
            if (board[i][col] == 'Q')
                return false;
        }
        // 检查右上方是否有皇后冲突
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
            if (board[i][j] == 'Q')
                return false;
        }
        // 检查左上方是否有皇后互相冲突
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
            if (board[i][j] == 'Q')
                return false;
        }
        return true;
    }

    void backtrack(vector<string>& board, int row) {
        // 触发结束条件
        if (row == board.size()) {
            res.push_back(board);
            return;
        }

        int n = board.size();
        for (int col = 0; col < n; ++col) {
            if (!isValid(board, row, col))
                continue;
            // 做选择
            board[row][col] = 'Q';
            // 进入下一行决策
            backtrack(board, row + 1);
            // 撤销选择
            board[row][col] = '.';
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(board, 0);
        return res;
    }
};
}  // namespace _51back

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

//todo===============================================================================================
namespace _40backtrack {

void backtrack(vector<int>& candidates, vector<bool>& isSelect, vector<vector<int>>& res, vector<int>& trace, int del) {
    if (del == 0) {
        res.push_back(trace);
        return;
    }

    for (int i = 0; i < candidates.size(); ++i) {
        if (!isSelect[i]) {
            //!=========================================================================================================
            if (del < candidates[i] || (i > 0 && candidates[i - 1] == candidates[i] && !isSelect[i - 1])) continue;
            if ((trace.size() > 0 && candidates[i] < trace.back())) continue;
            //!=========================================================================================================
            isSelect[i] = true;
            del -= candidates[i];
            trace.push_back(candidates[i]);

            backtrack(candidates, isSelect, res, trace, del);

            trace.pop_back();
            del += candidates[i];
            isSelect[i] = false;
        }
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> trace;
    vector<bool> isSelected(candidates.size(), false);
    std::sort(candidates.begin(), candidates.end());
    backtrack(candidates, isSelected, res, trace, target);
    return res;
}
}  // namespace _40backtrack

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
        /*
*
*/
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

static constexpr int directions[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// 判断以网格的 (i, j) 位置出发，能否搜索到单词word[k..]
// word[k..]表示字符串word 从第 k个字符开始的后缀子串
bool dfs(const vector<vector<char>>& board, string& s, vector<vector<char>>& isVisited, int i, int j, int k) {
    if (board[i][j] != s[k]) {
        return false;
    } else if (k == s.length() - 1) {
        return true;
    }

    isVisited[i][j] = true;
    bool result = false;
    for (auto& dir : directions) {
        int newi = i + dir[0];
        int newj = j + dir[1];
        // 判断newi和newj是否在board范围内
        if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {
            if (!isVisited[newi][newj]) {
                bool flag = dfs(board, s, isVisited, newi, newj, k + 1);
                if (flag) {
                    result = true;
                    break;
                }
            }
        }
    }
    isVisited[i][j] = false;
    return result;
}
bool exist(vector<vector<char>>& board, string word) {
    int h = board.size(), w = board[0].size();
    vector<vector<char>> isVisited(h, vector<char>(w, false));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            bool flag = dfs(board, word, isVisited, i, j, 0);
            if (flag) return true;
        }
    }
    return false;
}
}  // namespace _79LC

//*二叉树的所有路径
namespace _257LC {

// 根据路径构建路径字符串
string buildPath(const vector<int>& path) {
    string str;  // 编译器应该会优化
    for (int i = 0; i < path.size(); ++i) {
        str.append(to_string(path[i]));
        if (i != path.size() - 1) {
            str.append("->");
        }
    }
    return str;
}

// 回溯法
void dfs(TreeNode* root, vector<int>& path, vector<string>& ans) {
    if (root != nullptr) {
        path.push_back(root->val);
        // root 是叶子节点
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(buildPath(path));
        } else {
            dfs(root->left, path, ans);
            dfs(root->right, path, ans);
        }
        path.pop_back();
    }
}

vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    if (root == nullptr) return ans;

    vector<int> path;
    dfs(root, path, ans);
    return ans;
}
}  // namespace _257LC

//* 全排列
namespace _46LC {

// 表示从左往右填到第 first 个位置，当前排列为 output。
// 我们可以将题目给定的 n 个数的数组 nums[] 划分成左右两个部分，左边的表示已经填过的数，右边表示待填的数，我们在递归搜索的时候只要动态维护这个数组即可。
void dfs(vector<vector<int>>& res, vector<int>& output, int first, int len ) {
    if (first == len) {
        res.emplace_back(output);
        return;
    }
    for (int i = first; i < len; ++i) {
        // 动态维护数组
        std::swap(output[i], output[first]);
        dfs(res, output, first+1, len );
        std::swap(output[i], output[first]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    dfs(res, nums, 0, (int)nums.size());
    return res;
}

void backtracking(vector<int>& path, vector<vector<int>>& res, vector<bool>& visited, vector<int>& nums) {
   if (path.size() == nums.size()) {
       res.emplace_back(path);
       return;
   } 
   for (int i = 0; i < visited.size(); ++i) {
       if (visited[i]) continue; // 如果
       visited[i] = true;
       path.emplace_back(nums[i]);
       backtracking(path, res, visited, nums);
       path.pop_back();
       visited[i] = false;
   }
}

vector<vector<int>> permute_1(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    vector<bool> hasVisited(nums.size());
    backtracking(path, res, hasVisited, nums);
    return res;
}
}  // namespace _46LC
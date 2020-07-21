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
            if (n < 0 || (trace.size()>0 && trace.back() >= i) || trace.size() > k ) continue;
            //!===============================================================================
            trace.push_back(i);
            bcaktrack(res, trace, k, n - i);
            trace.pop_back();
        }
    }

     vector<vector<int>> combinationSum3(int k, int n) {
         vector<vector<int>> res;
         vector<int> trace;
         bcaktrack(res, trace, k,n);
         return res;
    }

}  // _216backtrack

namespace _351backtrack { //! 351. 安卓系统手势解锁

    // from为当先选中的点，to为下一个要选中的点
    bool isValid(vector<bool>& isSelcet, int from, int to) {
        if (from == to) return false;
        int i = std::min(from, to), j = std::max(from, to);
        //! 1、9/3、7对角线 如果5被选择且to没被选择的话--合法
        if ((i==1 && j ==9) || (i==3 && j==7)) return isSelcet[5] && !isSelcet[to];
        //! from、to在同一行 如果中间的被选择且to没被选择的话--合法
        if ((i==1 || i==4 || i==7) && i+2==j) return isSelcet[i+1] && !isSelcet[to];
        //! from、to在同一列 如果中间的被选择且to没被选择的话--合法
        if (i<=3 && i+6==j) return isSelcet[i+3] && !isSelcet[to];
        return !isSelcet[to];

        return false;
    }

    void backtrack(int m, int n, int count,vector<bool>& isSelected, int from, int& res) {
        if (count == n) {
            ++ res;
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
}


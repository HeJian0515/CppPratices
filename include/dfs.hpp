#pragma once
#include <limits.h>

#include <cstddef>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
namespace _92dfs {

bool isValidBST_helper(TreeNode* root, const long& lower, const long upper);

bool isValidBST(TreeNode* root) {
    return isValidBST_helper(root, LONG_MIN, LONG_MAX);
}

bool isValidBST_helper(TreeNode* root, const long& lower, const long upper) {
    if (root == nullptr) return true;
    if (root->val <= lower || root->val >= upper) return false;
    return isValidBST_helper(root->left, lower, root->val) && isValidBST_helper(root->right, root->val, upper);
}
}  // namespace _92dfs
//TODO ***************************************************************************************************************

namespace _200dfs { //! 200. 岛屿数量
void dfs(vector<vector<char>>& grid, int row, int col) {
    int rowNum = grid.size();
    int colNum = grid[0].size();
    grid[row][col] = '0';                                                        // 访问标记
    if (row - 1 >= 0 && grid[row - 1][col] == '1') dfs(grid, row - 1, col);      // 上
    if (row + 1 < rowNum && grid[row + 1][col] == '1') dfs(grid, row + 1, col);  // 下
    if (col - 1 >= 0 && grid[row][col - 1] == '1') dfs(grid, row, col - 1);      // 左
    if (col + 1 < colNum && grid[row][col + 1] == '1') dfs(grid, row, col + 1);  // 右
}

int numIslands(vector<vector<char>>& grid) {
    int rowNum = grid.size();
    if (rowNum < 1) return 0;
    int colNum = grid[0].size();

    int islandsNum = 0;
    for (int r = 0; r < rowNum; ++r) {
        for (int c = 0; c < colNum; ++c) {
            if (grid[r][c] == '1') {
                ++islandsNum;
                dfs(grid, r, c);
            }
        }
    }
    return islandsNum;
}

}  // namespace _100dfs

//TODO ================================================================================================
namespace _105BiTree { //! 105.从前序与中序遍历序列构造二叉树
/**
 * @brief: 由前序遍历和中序遍历构建二叉树
 * @name: He Jian
 * @param preorder 前序遍历数组
 * @param inorder 中序遍历数组
 * @param leftpre  在前序数组中，二叉树的左边界
 * @param rightpre 在前序数组中， 二叉树的右边界 左闭右开
 * @param leftin  在中序数组中，二叉树的左边界
 * @param rightin 在中序数组中， 二叉树的右边界 左闭右开
 * @return: 
 */
TreeNode* helper(vector<int>& preorder, vector<int>& inorder, int leftpre, int rightpre, int leftin, int rightin) {
    if (leftpre >= rightpre || leftin >= rightin) return nullptr;
    TreeNode* root = new TreeNode(preorder[leftpre]);// 前序遍历第一个节点是根节点
    //! =========================在中序数组中找到根节点的索引=========================================
    int rootin = leftin;
    while (rootin < rightin && inorder[rootin] != preorder[leftpre]) ++rootin;// 在中序遍历中找到根节点
    //! =========================在中序数组中找到根节点的索引=========================================
    int left = rootin - leftin; // 左子树的节点个数 从中序遍历得到
    // 构建左子树
    root->left = helper(preorder, inorder, leftpre + 1, leftpre + left + 1, leftin, rootin);
    // 构建右子树                              
    root->right = helper(preorder, inorder, leftpre + left + 1, rightpre, rootin + 1, rightin);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return helper(preorder, inorder, 0, preorder.size(), 0, inorder.size());
}
}  // namespace _105BiTree

//TODO ==========================================================================================================
namespace _106BiTree { //! 106.从中序与后序遍历序列构造二叉树
    TreeNode* helper(vector<int>& inorder, vector<int>& postorder,int left_in, int right_in, int left_post, int right_post) {
        if (left_in >= right_in || left_post >= right_post) return nullptr;
        TreeNode* root = new TreeNode(postorder[right_post-1]); // 后序遍历最后一个节点是树的根
        int root_in = left_in; // 在中序数组中找根的索引
        while (root_in<right_in && inorder[root_in]!=postorder[right_post-1]) ++root_in;
        int lchild_num = root_in - left_in; // 左孩子的个数
        // 构建左子树
        root->left = helper(inorder, postorder, left_in, root_in, left_post, left_post + lchild_num);
        // 构建右子树
        root->right = helper(inorder, postorder, root_in+1, right_in, left_post+lchild_num,  right_post-1);
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return helper(inorder, postorder, 0, inorder.size(), 0, postorder.size());
    }
}

//todo========================================================================================================
namespace _111BiTree { //! 111. 二叉树的最小深度

    int helper(TreeNode* root) {
        if (root == nullptr) return 0;
        if (root->left != nullptr && root->right != nullptr) { // 两边都不为空时 res = min(左子树深度， 右子树深度) + 1
            int leftDepth = helper(root->left);
            int rightDepth = helper(root->right);
            return leftDepth < rightDepth ? leftDepth + 1: rightDepth + 1;
        } else if (root->right == nullptr && root->left != nullptr) { // 左子树不为空且右子树为空时 res = （左子树深度）+ 1
            return helper(root->left) + 1;
        } else if (root->left ==nullptr && root->right != nullptr) { // 右子树不为空且右子树为空时 res = （右子树深度）+ 1
            return helper(root->right) + 1;
        }
        else {
            return 1;// 左右子树都为空时 res = 1
        } 
    }
    int minDepth(TreeNode* root) {
        return helper(root);
    }
}


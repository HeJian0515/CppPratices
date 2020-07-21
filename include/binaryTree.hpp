#pragma once 
#include <cstddef>

using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace _98IsBST { //! 98. 验证二叉搜索树

    bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
        if (root == nullptr) return true;
        if (min != nullptr && root->val <= min->val) return false;
        if (max != nullptr && root->val >= max->val) return false;
        return isValidBST(root->left, min, root) && isValidBST(root->right, root, max);
    }

     bool isValidBST(TreeNode* root) {
        return isValidBST(root, nullptr, nullptr);
    }
}

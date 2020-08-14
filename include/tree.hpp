#pragma once
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace _95BST { //! 95. 不同的二叉搜索树 II

    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) return {nullptr};
        vector<TreeNode*> allTrees;

        // 枚举可行根节点
        for (int i = start; i<=end; ++i) {
            // 获得所有可行的左子树集合
            vector<TreeNode*> leftTrees = generateTrees(start, i-1);
            // 获得所有可行的右子树集合
            vector<TreeNode*> rightTrees = generateTrees(i+1, end);
            // 从左子树集合中选出一颗左子树，从右子树集合中选出一颗右子树，拼接到根节点上
            for (auto& left : leftTrees) {
                for (auto& right: rightTrees) {
                    TreeNode * currTree = new TreeNode(i);
                    currTree->left = left;
                    currTree->right = right;
                    allTrees.push_back(currTree);
                }
            }
        }
        return allTrees;
    }
    vector<TreeNode*> generateTrees(int n) {
        if (n < 1) return {};
        return generateTrees(1, n);
    }
}

namespace _145Tree { //! 145. 二叉树的后序遍历 DFS
 vector<int> postorderTraversal(TreeNode* root) {
     stack<TreeNode*> s;
     vector<int> res;
     TreeNode* lastVisited = nullptr; // 上一个被访问的节点
        while (!s.empty() || root) {
            if (root) {
                s.push(root);
                root = root->left;
            } else {
                TreeNode* topNode = s.top();
                if (topNode->right && lastVisited != topNode->right) { // 判断右子节点是否访问 若未访问
                    root = topNode->right;
                } else { // 若右子节点不存在或已被访问  则topNode左右无节点 或 左右节点已被访问
                    res.push_back(topNode->val);
                    lastVisited = topNode;
                    s.pop();
                }
            }
        }
        return res;
    }
}

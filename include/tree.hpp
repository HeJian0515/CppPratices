#pragma once
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
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

//!========================中序遍历=============================
namespace _94inorderTraversal {
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> s;
    while (!s.empty() || root) {
        while (root) {
            s.push(root);
            root = root->left;
        }
        root = s.top(); s.pop();
        ans.push_back(root->val);
        root = root->right;
    }
    return ans;
}

namespace __Morris{
//* 1. x无左孩子，将x的值加入答案，再访问右孩子 x = x.right
//* 2. 有左孩子，找到x左子树上最右的节点（即左子树中序遍历的自后一个节点，x在中序遍历的前驱节点）计为predecessor
//*    - 如果predecessor的右孩子为空，则将其右右孩子指向x, 然后访问x的左孩子，即想x = x.left
//*    - 如果predecessor的右孩子不为空，则此时其右孩子指向x，说明已经遍历完x的左子树，将predecessor的右孩子置空，将x加入答案数组，然后访问x的右孩子，即x=x.right

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    TreeNode* predecessor = nullptr;

    while (root) {
        if (root->left) {
            // 找到前驱节点
            predecessor = root->left;
            while (predecessor->right && predecessor->right != root) {
                predecessor = predecessor->right;
            }

             // 让predecessor的右指针指向root,继续遍历左子树
            if (predecessor->right == nullptr) {
                predecessor->right = root;
                root = root->left;
            }
            else { // 说明左子树已经访问完了，需要断开连接
                ans.push_back(root->val);
                predecessor->right = nullptr;
                root = root->right;
            }
        }
        else { // 没有左孩子，则直接访问右孩子
            ans.push_back(root->val);
            root = root->right;
        }
    }

    return ans;
}
}
}


//! 二叉树的前序遍历
namespace _144preorderTraversal {
vector<int> preorderTraversal(TreeNode* root) {
    stack<TreeNode *> s;
    vector<int> ans;
    while (!s.empty() || root) {
        while (root) {
            ans.push_back(root->val);
            s.push(root->right);
            root = root->left;
        }

        if (s.empty())  break;
        root = s.top(); s.pop();
    }

  return ans;
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

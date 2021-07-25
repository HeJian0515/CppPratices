#pragma once 
#include <cstddef>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) 
        : val(x), left(left), right(right) {}
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


class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


//! 填充每个节点的下一个右侧节点指针
namespace _116connect {

void connect(Node* leftChild, Node* rightChild) {
    if (nullptr == leftChild || nullptr == rightChild) return;

    leftChild->next = rightChild;

    connect(leftChild->left, leftChild->right);
    connect(rightChild->left, rightChild->right);
    connect(leftChild->right, rightChild->left);
}

Node* connect(Node* root) {
    if (nullptr == root) return nullptr;
    connect(root->left, root->right);
    return root;
}

}

//! 二叉树转换为链表
namespace _114flatten {

void flatten(TreeNode* root) {
    if (nullptr == root) return;

    flatten(root->left);
    flatten(root->right);

    // 1. 左右子树已经被拉平成一条链表
    TreeNode* leftChild = root->left;
    TreeNode* rightChild = root->right;

    // 2. 将左子树作为右子树
    root->left = nullptr;
    root->right = leftChild;

    // 3. 将原先的右子树接到当前右子树的末端
    TreeNode* p = root;
    while (nullptr != p->right) {
        p = p->right;
    }
    p->right = rightChild;
}

}


namespace _654constructMaximumBinaryTree {

TreeNode* build(vector<int>::const_iterator lo, vector<int>::const_iterator hi){
    if (lo == hi) return nullptr; 

    auto it = std::max_element(lo, hi);
    TreeNode* left = build(lo, it);
    TreeNode* right = build(std::next(it), hi);
    return new TreeNode(*it, left, right);
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return build(nums.cbegin(), nums.cend());
}

}


namespace _105buildTree {

/* vector<int>* pre;
vector<int>* in;

unordered_map<int, int> iMap;

TreeNode* buildTree(int pLo, int pHi, int iLo, int iHi) {
    if(pLo >= pHi || iLo >= iHi) return nullptr;

    int rootValue = (*pre)[pLo];
    int iRoot = iMap[rootValue];
    int numOfLeftTree = iRoot - iLo;

    TreeNode* leftSubTree = buildTree(pLo+1, pLo+1+numOfLeftTree, iLo, iRoot);
    TreeNode* rightSubTree = buildTree(pLo+1+numOfLeftTree, pHi, iRoot+1, iHi);

    return new TreeNode(rootValue, leftSubTree, rightSubTree);  
}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
   pre = &preorder;
   in = &inorder;
   int n = preorder.size();
   for (int i = 0; i < n; ++i) {
       iMap[inorder[i]] = i;
   }
   
   return buildTree(0, n, 0, n);
} */

using It = vector<int>::const_iterator;

unordered_map<int, It> iMap;

TreeNode* buildTree(It pLo, It pHi, It iLo, It iHi) {
    if (pLo == pHi || iLo == iHi) return nullptr;

    int rootValue = *pLo;
    It inRootIt = iMap[rootValue];
    int numOfLeftTreeNode = inRootIt - iLo;
    
    It leftEnd = next(pLo, 1+numOfLeftTreeNode);

    TreeNode* left = buildTree(next(pLo), leftEnd, iLo, inRootIt);
    TreeNode* right = buildTree(leftEnd, pHi, next(inRootIt), iHi);

    return new TreeNode(rootValue, left, right);
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    
    for (It start = inorder.cbegin(), end = inorder.cend(); start != end; ++start) {
        iMap.emplace(*start, start);
    }
    return buildTree(preorder.cbegin(), preorder.cend(), inorder.cbegin(), inorder.cend());
}

}


namespace _106buildTree {

vector<int>* post;

unordered_map<int, int> iMap;

TreeNode* buildTree(int iLo, int iHi, int pLo, int pHi) {
    if (iLo >= iHi || pLo >= pHi) return nullptr;

    int rootValue = (*post)[pHi-1];
    TreeNode* root = new TreeNode(rootValue);

    int iRootPos = iMap[rootValue];
    int numleftNode = iRootPos - iLo;

    root->left = buildTree(iLo, iRootPos, pLo, pLo+numleftNode);
    root->right = buildTree(iRootPos+1, iHi, pLo+numleftNode, pHi-1);
    return root; 
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {

    post = &postorder;
    int n = inorder.size();
    for (int i = 0; i < n; ++i) {
        iMap.emplace(inorder[i], i);
    }

    return buildTree(0, n, 0, n);
}
}


namespace _652findDuplicateSubtrees {
unordered_map<string, int> count;
vector<TreeNode*> ans;

string Collect(TreeNode* node) {
    if (nullptr == node) return "#";
    string serial = to_string(node->val) + "," 
                    + Collect(node->left) + "," + Collect(node->right);
    int num = (++count[serial]);
    if (num == 2) {
        ans.push_back(node);
    }
    return serial;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    count.clear();
    ans.clear();
    Collect(root);
    return ans;
}
}


namespace _230kthSmallest {
int res = -1;
int rank = 0;

void traverse(TreeNode* root, int k) {
    if (nullptr == root) return;
    traverse(root->left, k);

    ++rank;
    if (k == rank) {
        res = root->val;
        return;
    }

    traverse(root->right, k);
}

int kthSmallest(TreeNode* root, int k) {
    traverse(root, k);
    return res;
}
}

namespace _538convertBST{

int sum = 0;
void traverse(TreeNode* root) {
    if (nullptr == root) return;

    traverse(root->right);

    sum += root->val;
    root->val = sum;

    traverse(root->left);
}
TreeNode* convertBST(TreeNode* root) {
    traverse(root);
    return root;
}
}

namespace _98isValidBST {
bool isValidBST(TreeNode* root, TreeNode* min, TreeNode* max) {
    if (nullptr == root) return true;
    if (min && root->val <= min->val) return false;
    if (max && root->val >= max->val) return false;

    return isValidBST(root->left, min, root) 
        &&  isValidBST(root->right, root, max);
}

bool isValidBST(TreeNode* root) {
    return isValidBST(root, nullptr, nullptr);
}
}

namespace _700searchBST {
TreeNode* searchBST(TreeNode* root, int val) {
    if (nullptr == root) return nullptr;

    if (root->val == val) return root;
    else if (root->val < val) {
        return searchBST(root->right, val);
    } else {
        return searchBST(root->left, val);
    }
}
}

namespace _701insertIntoBST {
// 往BST中插入一个节点，并返回树的根节点
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (nullptr == root) return new TreeNode(val);
    
    if (root->val < val) {
        root->right = insertIntoBST(root->right, val);
    } else {
        root->left = insertIntoBST(root->left, val);
    }

    return root;
}
}


namespace _450_deleteNode {

TreeNode* getMin(TreeNode* node) {
    // BST 最左边的就是最小的
    while(node->left) {
        node = node->left;
    }
    return node;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (nullptr == root) return nullptr;
    if (root->val == key) {
        // 1.被删除节点为叶子节点 2. 被删除节点只有一个孩子
        if (nullptr == root->left) return root->right;
        if (nullptr == root->right) return root->left;

        // 3. 被删除节点有两个孩子
        auto minNode = getMin(root->right); // 找到右子树最小的节点
        root->val = minNode->val; // 最小节点与被删除节点进行交换，此时被删除节点为叶子节点
        root->right = deleteNode(root->right, minNode->val);

    } else if (root->val > key) {   
        root->left  = deleteNode(root->left, key);
    } else {
        root->right = deleteNode(root->right, key);
    }
    return root;
}
}


// 二叉树的最近公共祖先
namespace _236lowestCommonAncestor
{
TreeNode* ans;
// 以x为根节点的树包不包含p或q
bool dfs(TreeNode* x, TreeNode* p, TreeNode* q) {
    if ( x == nullptr) return false;
    bool lson = dfs(x->left, p, q);
    bool rson = dfs(x->right, p, q);

    if ((lson && rson) || ( (x == p || x == q) && (lson || rson)) ) {
        ans = x;
    }
    return lson || rson || x == p || x == q;

}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    dfs(root, p, q);
    return ans;
}

// 找到每个节点的父节点， 问题变成两条链表相交的问题
namespace __Hash {
unordered_map<TreeNode*, TreeNode*> fa;
unordered_map<TreeNode*, bool> vis;

// 记录结点的父节点
void dfs(TreeNode* root) {
    if (root->left != nullptr) {
        fa[root->left] = root;
        dfs(root->left);
    }
    if (root->right != nullptr) {
        fa[root->right] = root;
        dfs(root->right);
    }
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    fa[root] = nullptr;
    dfs(root);

    // 将p到根节点的路径上的每个点都记录下来
    while (p != nullptr) {
        vis[p] = true;
        p = fa[p];
    }

    // q一路走向根节点，如果碰到已经标记过的结点，就返回
    while (q != nullptr) {
        if (vis[q]) return q;
        q = fa[q];
    }
    return nullptr;
}

}
}


//* 完全二叉树的判定
namespace _958isCompleteTree {
bool isCompleteTree(TreeNode* root) {
    queue<TreeNode*> q;
    bool reachNull = false;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();
        if (curr == nullptr) {
            reachNull = true;
            continue;
        } else {
            // 发现了空节点，右发现了非空节点
            if (reachNull) {
                return false;
            }
            // 继续遍历左右节点
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return true;
}

namespace _1 {
bool isCompleteTree(TreeNode* root) {
    vector<pair<TreeNode*, int>> nodes;
    nodes.push_back({root, 1});
    int i = 0;
    while (i < nodes.size()) {
        auto node = nodes[i++];
        if (node.first != nullptr) {
            if (nodes.back().second != nodes.size()) return false;
            nodes.push_back({node.first->left, node.second*2});
            nodes.push_back({node.first->right, node.second*2 + 1});
        }
    }
    return nodes.back().second == nodes.size();
}
}
}
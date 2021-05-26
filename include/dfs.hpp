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

//*200 岛屿数量
namespace _200dfs {  //! 200. 岛屿数量
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
//todo========================================================================================================
constexpr static int directions[][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int row, col;

inline bool inGrid(int r, int c) {
    return r >= 0 && r < row && c >= 0 && c < col;
}

//! 将深度优先遍历到的位置全部置为0
void _dfs(vector<vector<char>>& grid, int r, int c) {
    grid[r][c] = '0';
    for (int i = 0; i < 4; ++i) {
        int next_r = r + directions[i][0];
        int next_c = c + directions[i][1];
        if (inGrid(next_r, next_c) && grid[next_r][next_c] == '1') _dfs(grid, next_r, next_c);
    }
}

int numIslands(vector<vector<char>>& grid) {
    row = grid.size();
    if (row < 1) return 0;
    col = grid[0].size();

    int ans = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == '1') {
                ++ans;
                _dfs(grid, i, j);
            }
        }
    }
    return ans;
}

}  // namespace _200dfs

//TODO ================================================================================================
namespace _105BiTree {  //! 105.从前序与中序遍历序列构造二叉树
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
    TreeNode* root = new TreeNode(preorder[leftpre]);  // 前序遍历第一个节点是根节点
    //! =========================在中序数组中找到根节点的索引=========================================
    int rootin = leftin;
    while (rootin < rightin && inorder[rootin] != preorder[leftpre]) ++rootin;  // 在中序遍历中找到根节点
    //! =========================在中序数组中找到根节点的索引=========================================
    int left = rootin - leftin;  // 左子树的节点个数 从中序遍历得到
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
namespace _106BiTree {  //! 106.从中序与后序遍历序列构造二叉树
TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int left_in, int right_in, int left_post, int right_post) {
    if (left_in >= right_in || left_post >= right_post) return nullptr;
    TreeNode* root = new TreeNode(postorder[right_post - 1]);  // 后序遍历最后一个节点是树的根
    int root_in = left_in;                                     // 在中序数组中找根的索引
    while (root_in < right_in && inorder[root_in] != postorder[right_post - 1]) ++root_in;
    int lchild_num = root_in - left_in;  // 左孩子的个数
    // 构建左子树
    root->left = helper(inorder, postorder, left_in, root_in, left_post, left_post + lchild_num);
    // 构建右子树
    root->right = helper(inorder, postorder, root_in + 1, right_in, left_post + lchild_num, right_post - 1);
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return helper(inorder, postorder, 0, inorder.size(), 0, postorder.size());
}
}  // namespace _106BiTree

//todo========================================================================================================
namespace _111BiTree {  //! 111. 二叉树的最小深度

int helper(TreeNode* root) {
    if (root == nullptr) return 0;
    if (root->left != nullptr && root->right != nullptr) {  // 两边都不为空时 res = min(左子树深度， 右子树深度) + 1
        int leftDepth = helper(root->left);
        int rightDepth = helper(root->right);
        return leftDepth < rightDepth ? leftDepth + 1 : rightDepth + 1;
    } else if (root->right == nullptr && root->left != nullptr) {  // 左子树不为空且右子树为空时 res = （左子树深度）+ 1
        return helper(root->left) + 1;
    } else if (root->left == nullptr && root->right != nullptr) {  // 右子树不为空且右子树为空时 res = （右子树深度）+ 1
        return helper(root->right) + 1;
    } else {
        return 1;  // 左右子树都为空时 res = 1
    }
}
int minDepth(TreeNode* root) {
    return helper(root);
}
}  // namespace _111BiTree

//*695. 岛屿的最大面积
namespace _695maxAreaOfIsland {

// 从(x, y) 位置位置开始深度遍历
int dfs(vector<vector<int>>& grid, int x, int y, int m, int n)
{
    grid[x][y] = 0;
    int area = 1;

    if (x<m-1 && grid[x+1][y]==1) area += dfs(grid, x+1, y, m, n); // 向下
    if (x>0 && grid[x-1][y]==1) area += dfs(grid, x-1, y, m, n); // 向上

    if (y<n-1 && grid[x][y+1]==1) area += dfs(grid, x, y+1, m, n); // 向右
    if (y>0 && grid[x][y-1]==1) area += dfs(grid, x, y-1, m, n); // 向左

    return area;
}

int maxAreaOfIsland(vector<vector<int>>& grid)
{
    int m = grid.size(), n = grid[0].size();

    int maxArea = 0;
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == 1) {
                maxArea = max(maxArea, dfs(grid, i, j, m, n));
            }
        }
    }
    return maxArea;
}

}  // namespace _695LC

//* 朋友圈
namespace _547LC {

void dfs(vector<vector<int>>& m, vector<bool>& visited, int i) {
    visited[i] = true;
    for (int j = 0; j < m.size(); ++j) {
        if (m[i][j] == 1 && visited[j] == false) {
            dfs(m, visited, j);
        }
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    int cnt = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i){
        if (visited[i] == false) {
            dfs(isConnected, visited, i);
            ++cnt;
        }
    }
    return cnt;
}

}  // namespace _547LC

//*130被围绕的区域
namespace _130LC {
int row, col;

void dfs(vector<vector<char>>& board, int r, int c) {
    if (r < 0 || r >= row || c < 0 || c >= col || board[r][c] != 'O') return;
    board[r][c] = 'V';  // 标记开始的'O'及其连通的'O', 'V'表示已访问
    dfs(board, r + 1, c);
    dfs(board, r - 1, c);
    dfs(board, r, c + 1);
    dfs(board, r, c - 1);
}
void solve(vector<vector<char>>& board) {
    row = board.size();
    if (row == 0) return;
    col = board[0].size();

    // 每一行的边界
    for (int i = 0; i < row; ++i) {
        dfs(board, i, 0);
        dfs(board, i, col - 1);
    }

    // 每一列的边界
    for (int i = 1; i < col - 1; ++i) {
        dfs(board, 0, i);
        dfs(board, row - 1, i);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (board[i][j] == 'V') {
                board[i][j] = 'O';
            } else if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}
}  // namespace _130LC


//*417太平洋大西洋水流问题
namespace _417LC {
vector<vector<char>> P, A;
vector<vector<int>> ans;
int m, n;

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
{
    m = heights.size();
    n = heights[0].size();
    P = A = vector<vector<char>>(m, vector<char>(n, 0));

    // 左右两边加上下两边出发
    for (int i = 0; i < m; ++i) {
        dfs(heights, P, i, 0); // 左边
        dfs(heights, A, i, n-1); // 右边
    }
    for (int i = 0; i < n; ++i) {
        dfs(heights, P, 0, i);
        dfs(heights, A, m-1, i);
    }
    return ans;
}

void dfs(vector<vector<int>>& M, vector<vector<char>>& visited, int i, int j)
{
    if (visited[i][j]) return;
    visited[i][j] = 1;

    if (P[i][j] && A[i][j]) ans.push_back({i, j});

    //上下左右深搜
    if(i-1 >= 0 && M[i-1][j] >= M[i][j]) dfs(M, visited, i-1, j);
    if(i+1 < m && M[i+1][j] >= M[i][j]) dfs(M, visited, i+1, j); 
    if(j-1 >= 0 && M[i][j-1] >= M[i][j]) dfs(M, visited, i, j-1);
    if(j+1 < n && M[i][j+1] >= M[i][j]) dfs(M, visited, i, j+1); 
}

}  // namespace _417LC

namespace _70recur {

    int helper (int n) {
        if (n == 1) return 1;
        else if (n == 2) return 2;
        else return helper(n - 1) + helper(n-2); 
    }
    int helper(vector<int>& memo, int n ) {
        for (int i = 3; i < memo.size(); ++i) {
            memo[i] = memo[i-1] + memo[i-2];
        }
        return memo[n];
    }
    int climbStairs(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        vector<int> memo(n+1, 0);
        memo[1] = 1;
        memo[2] = 2;
        return helper(memo, n);
    }
}
#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

namespace __111bfs {  //! 111. 二叉树的最小深度
int minDepth(TreeNode* root) {
    if (root == nullptr) return 0;

    queue<TreeNode*> q;
    q.push(root);
    int step = 1;

    while (!q.empty()) {
        int sz = q.size();

        // 把同一层的节点全部遍历、弹出
        for (int i = 0; i < sz; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            // 判断是否到达叶子节点
            if (cur->left == nullptr && cur->right == nullptr) return step;
            // 将cur的相邻节点加入队列
            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }
        ++step;
    }
    return step;
}
}  // namespace __111bfs

namespace _752bfs {  //!  打开转盘锁
// 将 s[j] 向上拨动一次
string plusOne(string s, int j) {
    if (s[j] == '9')
        s[j] = '0';
    else
        s[j] += 1;
    return s;
}

// 将 s[j] 向下拨动一次
string minusOne(string s, int j) {
    if (s[j] == '0')
        s[j] = '9';
    else
        s[j] -= 1;
    return s;
}

// BFS
void BFS(string target) {
    queue<string> q;
    q.push("0000");

    while (!q.empty()) {
        int sz = q.size();
        // 将当前队列中的所有节点向周围扩散
        for (int i = 0; i < sz; ++i) {
            string cur = q.front();
            q.pop();
            // 判断是否到达终点
            cout << cur << endl;

            // 将相邻节点加入队列
            for (int j = 0; j < 4; ++j) {
                string up = plusOne(cur, j);
                string down = minusOne(cur, j);
                q.push(up);
                q.push(down);
            }
        }
        // 增加步数
    }
    return;
}
/*
     int openLock(vector<string>& deadends, string target) {
         // 记录需要跳过的死亡密码
         unordered_set<string> deads;
         for (string s : deadends) deads.insert(s);

         // 记录已穷举的密码，防止走回头路
         unordered_set<string> visited;
         queue<string> q;
         // 从起点开始启动广度优先搜索
         int step = 0;
         q.push("0000");
         visited.insert("0000");

         while (!q.empty()) {
             int sz = q.size();
             // 将当前队列中的所有节点向周围扩散 一层
             for (int i = 0; i < sz; ++i) {
                 string cur = q.front();
                 q.pop();

                 // 判断是否到达终点
                 if (deads.find(cur) != deads.end()) continue;
                 if (cur == target) return step;

                 // 将一个节点的未遍历的相邻节点加入队列
                 for (int j = 0; j < 4; ++j) {
                     string up = plusOne(cur, j);
                     if (visited.find(up) == visited.end()) {
                         q.push(up);
                         visited.insert(up);
                     }
                     string down = minusOne(cur, j); 
                     if (visited.find(down) == visited.end()) {
                        q.push(down);
                        visited.insert(down);
                     } 
                 }
             }
             ++step;
         }
         return -1;
     }
     */

// 双向BFS
int openLock(vector<string>& deadends, string target) {
    unordered_set<string> deads;
    for (string s : deadends) deads.insert(s);
    // 用集合不用队列，可以快速判断元素是否存在
    unordered_set<string> q1;  // 从上往下一层的节点
    unordered_set<string> q2;  // 从下往上一层的节点
    unordered_set<string> visited;

    int step = 0;
    q1.insert("0000");
    q2.insert(target);

    while (!q1.empty() && !q2.empty()) {
        // 哈希集合在遍历的过程中不用修改，用 temp 存储
        unordered_set<string> temp;  // 将下一层的节点放入temp中

        // 将q1中的所有节点向周围扩散
        for (string cur : q1) {
            // 判断是否到达终点
            if (deads.find(cur) != deads.end()) continue;
            if (q2.find(cur) != q2.end()) return step;
            visited.insert(cur);

            // 将一个节点的未遍历相邻节点加入集合
            for (int j = 0; j < 4; ++j) {
                string up = plusOne(cur, j);
                if (visited.find(up) == visited.end()) temp.insert(up);
                string down = minusOne(cur, j);
                if (visited.find(down) == visited.end()) temp.insert(down);
            }
        }
        // 在这里增加步数
        ++step;
        // temp 相当于 q1
        // 这里交换 q1 q2，下一轮 while 就是扩散 q2
        q1.swap(q2);
        q2.swap(temp);
    }
    return -1;
}
}  // namespace _752bfs

//*二进制矩阵中的最短路径
namespace _1091LC {
//!八个可以走的方向
constexpr static int directions[][2] = {{0, 1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {-1, -1}, {-1, 0}, {-1, 1}};
int row, col;

inline bool inGrid(int x, int y) {
    return x >= 0 && x < row && y >= 0 && y < col;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    row = grid.size();
    col = grid[0].size();

    if (grid[0][0] == 1 || grid[row - 1][col - 1]) return -1;
    queue<pair<int, int>> pos;
    grid[0][0] = 1;  //!标记已经访问过 并设为路径长度
    pos.push({0, 0});
    while (!pos.empty() && grid[row - 1][col - 1] == 0) {
        auto [x, y] = pos.front();
        pos.pop();
        int preLen = grid[x][y];
        //! 将上下左右的节点可以走的加入队列
        for (int i = 0; i < 8; ++i) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];
            //! 判断下一步是否再格子中 并判断是否可以走
            if (inGrid(newX, newY) && grid[newX][newY] == 0) {
                pos.push({newX, newY});
                grid[newX][newY] = preLen + 1;
            }
        }
    }
    return grid[row - 1][col - 1] == 0 ? -1 : grid[row - 1][col - 1];
}
}  // namespace _1091LC

//*完全平方数
namespace _279LC {
unordered_set<int> square_nums;
//! n是否可以被count个平方数相加得到
bool is_divided_by(int n, int count) {
    if (count == 1) return square_nums.count(n);

    for (int square : square_nums) {
        if (is_divided_by(n - square, count - 1)) {
            return true;
        }
    }
    return false;
}

//!可以不用返回确切的组合
int numSquares(int n) {
    square_nums.clear();

    for (int i = 1; i * i <= n; ++i) {
        square_nums.emplace(i * i);
    }
    int count = 1;
    for (; count <= n; ++count) {
        if (is_divided_by(n, count)) {  //!是否可以被count数组合而成
            return count;
        }
    }
    return count;
}

int numSquares_1(int n) {
    vector<int> asquare_nums;
    for (int i = 0; i * i <= n; ++i) {
        asquare_nums.emplace_back(i * i);
    }

    unordered_set<int> que;
    que.emplace(n);

    int level = 0;
    while (que.size() > 0) {
        level += 1;
        unordered_set<int> next_que;
        for (int remainder : que) {
            for (int square : asquare_nums) {
                if (remainder == square) {
                    return level;
                } else if (remainder < square) {
                    break;
                } else {
                    next_que.emplace(remainder - square);
                }
            }
        }
        que = next_que;
    }
    return level;
}

int numSquares_2(int n) {
    //! 记录所有小于n的平方数
    vector<int> squares;
    for (int i = 1; i * i <= n; ++i) {
        squares.emplace_back(i * i);
    }

    queue<int> que;
    vector<int> marked(n + 1, false);  //! 用来标记最快到达next的level
    que.push(n);
    marked[n] = true;
    int level = 0;

    while (!que.empty()) {
        int size = que.size();
        level++;
        while (size-- > 0) {
            int cur = que.front();
            que.pop();
            for (int s : squares) {
                int next = cur - s;
                if (next < 0) {
                    break;
                } else if (next == 0) {
                    return level;
                }

                if (marked[next]) continue;

                marked[next] = true;
                que.push(next);
            }
        }
    }
    return level;
}
}  // namespace _279LC

//!单词接龙
namespace _127LC {

bool isOneCharDifferent(const string& s1, const string& s2) {
    int count = 0;
    for (int i = 0; i < s1.length(); ++i) {
        if (s1[i] != s2[i]) {
            ++count;
            if (count > 1) return false;
        }
    }
    return count == 1;
}
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.cbegin(), wordList.cend());
    if (!wordSet.count(endWord)) return 0;

    unordered_set<string> upTodown({beginWord});
    unordered_set<string> downToup({endWord});

    int word_size = beginWord.size();
    int list_size = wordList.size();

    vector<int> marked(list_size, false); //!标记wordList已经访问过的元素
    int res = 2;

    while (!upTodown.empty()) {
        unordered_set<string> next;  // 下一层元素
        for (auto& word : upTodown) {
            for (int i = 0; i < list_size; ++i) {
                // 找到下一层元素
                if (isOneCharDifferent(word, wordList[i])) {
                    //! 是否已连接
                    if (downToup.count(wordList[i])) return res;
                    // 下一层元素入队
                    if (!marked[i]) next.insert(wordList[i]);
                    marked[i] = true; // 标记已访问元素
                }
            }
        }
        ++res;
        if (next.size() <= downToup.size()) {
            upTodown = next;
        } else {
            upTodown = downToup;
            downToup = next;
        }
    }
    return 0;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    //!记录所有节点
    unordered_set<string> wordDict(wordList.cbegin(), wordList.cend());
    if (!wordDict.count(endWord)) return 0; 

    unordered_set<string> beginSet{beginWord};
    unordered_set<string> endSet{endWord};

    int step = 1;
    while (!beginSet.empty()) {
        unordered_set<string> next; // 前面入队节点的下一层子节点
        ++step;
        for (auto& s: beginSet) { // 删除已经访问过的上一层节点
            wordDict.erase(s);
        }

        for (auto& s: beginSet) {
            for (int i = 0; i < s.size(); ++i) {
                string str(s);
                for (char c = 'a'; c <= 'z'; ++c) {
                    str[i] = c;//! 只将上一层节点字符串改变一个字符
                    //! 判断下一层是否有 上一层字符串 只改变一个字符 的字符串
                    if (!wordDict.count(str)) {
                        continue;
                    }
                    if (endSet.count(str)) {
                        return step;
                    }
                    next.insert(str);//下一层要访问的节点入队
                }
            }
        }
        //始终保持路径短的一侧开始遍历
        if (next.size() < endSet.size()) {
            beginSet = next;
        } else {
            beginSet = endSet;
            endSet = next;
        }
    }
    return 0;
}

}  // namespace _127LC
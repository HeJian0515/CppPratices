#include <bits/stdc++.h>
using namespace std;

// 网易互娱
namespace _netease_kuyv{
// 宝箱和麦哈顿距离
namespace _1 {

int dir[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
vector<vector<char>> G;
vector<vector<char>> vis;
vector<vector<int>> alldis;
vector<vector<char>> inq;
int m, n;
int startx, starty;
int boxNum;


struct pos {
    int x, y;
    pos(int nx, int ny): x(nx), y(ny)
    {}
};

// 寻找曼哈顿距离最小的位置
void findk(int px, int py, int& tarx, int& tary) {
    int mindis = INT_MAX;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (isdigit(G[i][j])) {
                int dis = abs(px -i) + abs(py - j);
                if (dis < mindis) {
                    tarx = i; tary = j;
                    mindis = dis;
                } else if (dis == mindis && G[i][j] < G[tarx][tary]) {
                    tarx = i; tary = j;
                }
            }
        }
    }
    return;
}

// 从目标位置开始广度优先遍历，使之到达开始位置
void bfs(int tarx, int tary) {
    queue<pos> q;
    int nowdis = 0;
    q.push({tarx, tary});
    inq[tarx][tary] = true;
    while (!q.empty()) {
        int nowSize = q.size();
        for (int i = 0; i < nowSize; ++i) {
            pos nowp = q.front(); q.pop();
            alldis[nowp.x][nowp.y] = nowdis;
            for (int i = 0; i < 4; ++i) {
                pos nextPos{ nowp.x+dir[i][0], nowp.y+dir[i][1] };
                if (nextPos.x >= 0 && nextPos.x < m && nextPos.y >= 0 && nextPos.y < n) {
                    if (G[nextPos.x][nextPos.y] != '#' && inq[nextPos.x][nextPos.y] == false) {
                        inq[nextPos.x][nextPos.y] = true;
                        q.push(nextPos);
                    }
                }
            }
            nowdis++;
        }
        
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        boxNum = 0;
        cin >> m >> n;
        vector<vector<char>>(m, vector<char>(n)).swap(G);
        vector<vector<char>>(m, vector<char>(n, false)).swap(vis);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> G[i][j];
                if (G[i][j] == '*') {
                    startx = i; starty = j;
                } else if (isdigit(G[i][j])) {
                    ++boxNum;
                }
            }
        }

        int ans = 0;
        bool e_flag = false;
        while (boxNum > 0) {
            int tarx = -1, tary = -1;
            findk(startx, starty, tarx, tary); // 寻找距离最小的宝盒
            // 计算麦哈顿距离
            if (-1 != tarx || -1 != tary) {
                vector<vector<int>>(m, vector<int>(n, INT_MAX)).swap(alldis);
                vector<vector<char>>(m, vector<char>(n, false)).swap(inq);
                // 从目标位置开始bfs，计算其他位置离他的距离
                bfs(tarx, tary);
            }
            // 无法到达
            if (alldis[startx][starty] == INT_MAX) {
                ans = -1;
                break;
            } else { // 走一步缩小与k的麦哈顿距离
                vis[startx][starty] = true;
                for (int i = 0; i < 4; ++i) {
                    pos newPos{startx+dir[i][0], starty+dir[i][1]}; // 从开始位置出发
                    if (newPos.x >= 0 && newPos.x < m && newPos.y >= 0 && newPos.y < n && alldis[newPos.x][newPos.y] < alldis[startx][starty]) {
                        if (vis[newPos.x][newPos.y] == true) { // 在左右横跳，陷入死循环
                            ans = -1;
                            e_flag = true;
                            break;
                        }
                        startx = newPos.x;
                        starty = newPos.y;
                        if (isdigit(G[startx][starty])) { // 找到一个宝箱
                            --boxNum;
                            if (G[startx][starty] == G[tarx][tary]) { // 一般而言距离最小的宝箱是k,走一步之后距离缩小1，所以一般最小还是k
                                vector<vector<char>>(m, vector<char>(n, false)).swap(vis);
                            }
                            G[startx][starty] = '.';
                        }
                        break;
                    }
                }
                if (e_flag) break;
                ++ans;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

}

// 十字斩
namespace _2 {

void tencut(vector<vector<int>>& vec, int sz) {
    int m = sz;
    if (m == 1) cout << 1 << " " << 1 << '\n';
    else if ( m > 0 ) {
        int row = 0, col = 0, maxNum = 0;
        vector<vector<int>>sum(m, vector<int>(2)); // 记录每行每列的总和
        for (int i = 0; i < m; ++i) {
            int colsum = 0, rowsum = 0;
            for (int j = 0; j < m; ++j) {
                rowsum += vec[i][j];
                colsum += vec[j][i];
            }
            sum[i][0] = rowsum;
            sum[i][1] = colsum;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                int alsum = sum[i][0] + sum[j][1] - vec[i][j];
                if (alsum > maxNum) {
                    maxNum = alsum;
                    row = i; col = j;
                }
            }
        }
        cout << row+1 << " " <<  col+1 << '\n';

        int rr = 0, cc = 0; // 在原数组上进行修改
        for (int i = 0; i < m; ++i) {
            if (i == row) continue;
            cc = 0;
            for (int j = 0; j < m; ++j) {
                if (j == col) continue;
                vec[rr][cc] = vec[i][j];
                cc++;
            }
            rr++;
        }
        tencut(vec, m-1);
    }
}

namespace _other_1{
constexpr int N = 505;
int ph[N], pl[N];
int a[N][N];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            pl[i] += a[i][j]; // 行
            ph[j] += a[i][j]; // 列
        }
    }

    for (int k = 0; k < n; ++k) {
        int x = 1, y = 1;
        int pre = pl[x] + ph[y] - a[x][y];
        for (int i = 1; i <= n-k; ++i) {
            for (int j = 1; j <= n-k; ++j) { 
                int now =pl[i] + ph[j] - a[i][j];
                if (now > pre) {
                    x = i; y = j;
                    pre = now;
                }
            }
        }
        cout << x << " " << y << endl;
        for(int i=1;i<=n-k;i++) ph[i] -= a[x][i];
        for(int i=1;i<=n-k;i++) pl[i] -= a[i][y];

        for(int i=x;i<n-k;i++)  for(int j=1;j<y;j++) a[i][j] = a[i+1][j];
        for(int i=1;i<x;i++)  for(int j=y;j<n-k;j++) a[i][j] = a[i][j+1];

        for(int i=x;i<n-k;i++)  for(int j=y;j<n-k;j++) a[i][j] = a[i+1][j+1];
        for(int i=x;i<n-k;i++) pl[i] = pl[i+1];
        for(int i=y;i<n-k;i++) ph[i] = ph[i+1];
    }
}

}

int main() {
    int size = 0;
    while (cin >> size) {
        vector<vector<int>> vec(size, vector<int>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> vec[i][j];
            }
        }
        tencut(vec, size);
    }
}

}


namespace _3 {
// 1.提取独立的数字以及字母存储到列表当中
// 2.判断独立数字个数是否大于等于7 以及 独立字母个数是否大于等于3
int main() {
    int T; cin >> T;
    while (T--) {
        string s;
        unordered_set<int> intset;
        unordered_set<char> charset;
        for (int i = 0; i < 7; ++i) {
            cin >> s;
            intset.insert(s[0] - '0');
            charset.insert(s[1]);
        }
        
        if (intset.size() == 7 && charset.size() == 3) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
}
}

}

//! 网易互联网 
namespace _netease_HuLianWang {

// 环 发纸(发糖)  
namespace _1 {
    vector<int> mySplit(string& s) {
        regex re(" "s);
        vector<string> ss(sregex_token_iterator(s.begin(), s.end(), re, -1),
                          sregex_token_iterator());
        vector<int> ret; ret.reserve(ss.size());
        for (auto& str : ss) ret.push_back(stoi(str));
        return ret;
    }

    int main() {
        string s;
        getline(cin, s);
        vector<int> nums = mySplit(s);
        int n = nums.size();

        vector<int> dp(n, 1);

        while (true) {
            bool flag = false;
            for (int i = 0; i < n; ++i) {
                if (nums[i] > nums[(i+n-1)%n]) {
                    if (dp[i] <= dp[(i+n-1)%n]) {
                        ++dp[i];
                        flag = true;
                    }
                }

                if (nums[i] > nums[(i+n+1)%n]) {
                    if (dp[i] <= dp[(i+n+1)]%n) {
                        ++dp[i];
                        flag = true;
                    }
                }
            }
            if (!flag) break;
        }
        cout << accumulate(dp.cbegin(), dp.cend(), 0LL);
    }
}

// 图 水路 陆路 障碍 
namespace _2 {

int min_cost = -1;
const int dir[][2] = {{0, 1}, {1, 0}};

void newdfs(vector<vector<int>>& grid, int x, int y, int cost, vector<vector<char>>& vis) {
    int n = grid.size();
    int m = grid[0].size();
    if (x == n - 1 && y == m - 1) {
        if (min_cost == -1) {
            min_cost = cost;
        } else {
            min_cost = min(min_cost, cost);
        }
    }

    if (!vis[x][y]) {
        vis[x][y] = true;
        for (int i = 0; i < 2; ++i) {
            int tx = x + dir[i][0];
            int ty = y + dir[i][1];
            if (tx >= 0 && tx < n && ty >=0 && ty < m && grid[tx][ty] != 2) {
                if (grid[tx][ty] == 0) {
                    newdfs(grid, tx, ty, cost+2, vis);
                } else {
                    newdfs(grid, tx, ty, cost+1, vis);
                }
            }
        }
        vis[x][y] = false;
    }
}

int minSailCost(vector<vector<int>>& input) {
    vector<vector<char>> vis(input.size(), vector<char>(input[0].size()));

    return min_cost;
}

}
}
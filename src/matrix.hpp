#include <vector>
#include <queue>
#include <climits>
using namespace std;

// 01矩阵
namespace _542updateMatrix
{
static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dist(m, vector<int>(n));
    vector<vector<int>> seen(m, vector<int>(n));
    queue<pair<int, int>> q;

    // 将所有的0添加到队列中
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                q.emplace(i, j);
                seen[i][j] = 1;
            }
        }
    }

    // 广度优先搜索
    while (!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int ni = i + dirs[d][0];
            int nj = j + dirs[d][1];
            if (ni >= 0 && ni < m && nj >=0 && nj < n && !seen[ni][nj]) {
                dist[ni][nj] = dist[i][j] + 1;
                q.emplace(ni, nj);
                seen[ni][nj] = 1;
            }
        }
    }
    return dist;
}


vector<vector<int>> updateMatrix_1(vector<vector<int>>& mat)
{
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX/2));
    // 如果(i, j)的元素为0，那么距离为0
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
            }
        }
    }

    // 由向左， 向上推导过来
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i - 1 >= 0) {
                dist[i][j] = min(dist[i][j], dist[i-1][j] + 1);
            }
            if (j - 1 >= 0) {
                dist[i][j] = min(dist[i][j], dist[i][j-1] + 1);
            }
        }
    }

    // 由向右，向下推导过来
    for (int i = m-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j) {
            if (i+1 < m) {
                dist[i][j] = min(dist[i][j], dist[i+1][j] + 1);
            }
            if (j+1 < n) {
                dist[i][j] = min(dist[i][j], dist[i][j+1] + 1);
            }
        }
    }
    return dist;
}


}
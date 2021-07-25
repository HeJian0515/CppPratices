#include <vector>
#include <queue>
#include <string>
#include <regex>

using namespace std;

//! 并查集
namespace _684findRedundantConnection
{

class Djset {
public:
    vector<int> parent; // 记录结点的根
    vector<int> rank; // 记录根节点的深度 用于优化
    Djset(int n) : parent(vector<int>(n)), rank(vector<int>(n)) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 寻找根
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool merge(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty]) {
                std::swap(rootx, rooty);
            }
            parent[rooty] = rootx;

            if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            return false; // 根节点不同，返回false
        }
        // 根节点相同，返回true
        return true;
    }
};

class Solution {
public:
    int Find(vector<int>& parent, int index) {
        if (parent[index] != index) {
            parent[index] = Find(parent, parent[index]);
        }
        return parent[index];
    }

    void Union(vector<int>& parent, int index1, int index2) {
        parent[Find(parent, index1)] = Find(parent, index2);
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int nodesCount = edges.size();
        vector<int> parent(nodesCount + 1);
        for (int i = 1; i <= nodesCount; ++i) {
            parent[i] = i;
        }

        for (auto& edge : edges) {
            int node1 = edge[0];
            int node2 = edge[1];
            if (Find(parent, node1) != Find(parent, node2)) {
                Union(parent, node1, node2);
            } else {
                return edge;
            }
        }
        return {};
    }

};
} 



//! 二分图的遍历:广度优先+染色
namespace _785isBipartite
{
bool isBipartite(vector<vector<int>>& graph)
{
    int n = graph.size();
    if (n == 0) return true;

    vector<char> color(n, 0);
    queue<int> q;
    //* 0代表未检查的节点，用1和2来表示两种不同的颜色
    for (int i = 0; i < n; ++i) {
        // 将未染色的节点加入队列，开始广度优先搜索
        if (!color[i]) {
            q.push(i);
            color[i] = 1;
        }

        // 广度优先遍历 + 染色
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            // 与node相连的节点
            for (const int& j : graph[node]) {
                if (color[j] == 0) { //* 与node相连的节点未被检查，则将其染为与node向反的颜色
                    q.push(j);
                    color[j] = color[node] == 2 ? 1 : 2;
                } else if(color[node] == color[j]) { 
                    return false;
                }
            }
        }
    }
    return true;
}
}

//! 拓扑排序 -- 遍历有顺序

namespace _207canFinish
{
vector<vector<int>> edges;
vector<int> indeg;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    edges.resize(numCourses);
    indeg.resize(numCourses);

    // 构建图
    for (const vector<int>& info : prerequisites) {
        edges[info[1]].push_back(info[0]); // 1 -- > 0
        ++indeg[info[0]]; // 0 入度+1
    }

    queue<int> q;
    // 入度为0的节点入队
    for (int i = 0; i < numCourses; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    int visited = 0;
    while (!q.empty()) {
        ++visited;
        int u = q.front();
        q.pop();
        for (int v : edges[u]) {
            --indeg[v];
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    return visited == numCourses;
}
}

namespace _210findOrder
{
// 有向图
vector<vector<int>> edges;
// 存储每个节点的入度
vector<int> indeg;
vector<int> result;
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
{
    edges.resize(numCourses);
    indeg.resize(numCourses);
    result.reserve(numCourses);

    for (const auto& info : prerequisites) {
        edges[info[1]].push_back(info[0]);
        ++indeg[info[0]];
    }

    queue<int> q;
    // 将入度为0的节点放入队列中
    for (int i = 0; i < numCourses; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front(); q.pop();
        result.push_back(u);
        // 将相邻节点的入度 -1 , 如果入度为0了就加入队列中
        for (int v : edges[u]) {
            --indeg[v];
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    if (result.size() != numCourses) {
        return {};
    }
    return result;
}

}

namespace _vivo_{
// 将 字符串"1,2,-1,1"转化成vector<int>{1,2,-1,1}
vector<int> split(const string& str) {
    regex reg(",");
    vector<string> intsStr(sregex_token_iterator(str.cbegin(), str.cend(), reg, -1),
        sregex_token_iterator{});

    vector<int> ints; ints.reserve(intsStr.size());
    for (const auto& intStr : intsStr) {
        ints.push_back(stoi(intStr));
    }

    return ints;
}

string compileSeq(string input) {
    vector<int> pre = split(input);
    int n = pre.size();
    
    vector<char> visited(n, false);
    // 保证当两节点没有依赖时，序号小的节点在前面
    priority_queue<int, vector<int>, greater<int>> q;

    vector<vector<int>> edges(n);
    vector<int> indeg(n);
    // 找到入度为0的节点，加入队列
    for (int i = n-1; i >= 0; --i) {
        if (pre[i] == -1) {
            q.push(i);
        } else {
            edges[pre[i]].push_back(i);
            ++indeg[i];
        }
    }

    string res;
    while (!q.empty()) {
        int node = q.top(); q.pop();
        res += to_string(node) + ",";
        for (int v : edges[node]) {
            --indeg[v];
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }
    res.pop_back();
    return res;
}

}

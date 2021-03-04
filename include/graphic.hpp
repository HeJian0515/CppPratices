#include <vector>

using namespace std;

// 并查集
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

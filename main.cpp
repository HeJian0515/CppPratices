#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M, C;
    cin >> N >> M;
    vector<unordered_set<int>> children(N+1), parent(N+1);
    while (M--) {
        cin >> C; // 知道C个运动员的相对位置
        int pre = -1, x;
        while (C--) {
            cin >> x;
            if (pre != -1) {
                children[pre].emplace(x);
                parent[x].emplace(pre);
            }
            pre = x;
        }
    }

    vector<int> indeg(N+1);
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        indeg[i] = parent[i].size();
        if (indeg[i] == 0) {
            q.emplace(i);
        }
    }

    vector<int> ans;
    while (!q.empty()) {
        // 每次只有一个入度为0的节点
        if (q.size() != 1) {
            break;
        }
        int u = q.front(); q.pop();
        ans.emplace_back(u);
        while (!children[u].empty()) {
            int v = *children[u].begin();
            if (--indeg[v] == 0) {
                q.emplace(v);
            }
            children[u].erase(v); // 删除边
        }
    }
    if (ans.size() != N) {
        cout << "NO\n";
    } else {
        for (int i = 0; i < N; ++i) {
            cout << ans[i] << " \n"[i == N-1];
        }
    }
}

int main() {
    int T; cin >> T;
    while(T--) {
        solve();
    }
}
  
#include <bits/stdc++.h>
using namespace std;

namespace _Alibaba_1 {

namespace _1 {
// 将属性1按从小到大排序，若属性1相等，则按属性2从大到小排序
// 最终问题变成求属性2的最长递增子序列
int solve(vector<vector<int>>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end(), [] (const vector<int>& v1, const vector<int>& v2){
        return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
    });

    int res = 0;
    vector<int> seq; // seq[len]表示长度为(len+1)的子序列以seq[len]结尾
    for (int i = 0; i < n; ++i) {
        if (!seq.empty() && nums[seq.back()][1] > nums[i][1]) {
            int pos = lower_bound(seq.begin(), seq.end(), nums[i][1], [&](auto& idx, auto& val){
                return nums[idx][1] < val;
            }) - seq.begin();
            seq[pos] = i;
        } else if (seq.empty() || nums[seq.back()][1] < nums[i][1]) {
            seq.push_back(i);
        }
    }
    return seq.size();
}

int main() {
    int T, N;
    cin >> T;
    while (T--) {
        cin >> N;
        vector<vector<int>> nums(N, vector<int>(2));
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> nums[j][i];
            }
        }
        cout << solve(nums) << endl;
    }

    return 0;
}

}

//!===========================================================
namespace _2 {

constexpr int mod = 1e9 + 7;

int solve(long long A, long long B, int n) {
    vector<long long> dp(n+1);
    dp[0] = 2;
    dp[1] = A % mod;
    for (int i = 2; i <= n; ++i) {
        dp[i] = A*dp[i-1] - B*dp[i-2];
        dp[i] %= mod;
    }
    return dp.back() < 0 ? dp.back()+mod : dp.back();
}

int main() {
    int T, A, B, n;
    cin >> T;
    while (T--) {
        cin >> A >> B >> n;
        cout << solve(A, B, n) << endl;
    }
}

}

//!卡特兰数===================================================
namespace _3 {

int n, m;
constexpr int mod = 1e9 + 7;
int f[55][55] = {{0}};
long long dfs(long long n, long long m) {
    if (n <= 1) return 1;
    if (f[n][m]) return f[n][m];

    long long ans = 0, i;
    for (i = 0; i < n; ++i) {
        // m-1层最多有 2^(m-1) - 1 个节点
        if(i <= (1LL<<(m-1))-1 && n-1-i <= (1LL<<(m-1))-1) {
            ans += (dfs(i, m-1) * dfs(n-1-i, m-1)) % mod;
            ans %= mod;
        }
    }

    return f[n][m] = ans;
}

int main() {
    cin >> n >> m;
    cout << dfs(n, m) << '\n';

    return 0;
}

}

//! bfs=======================================================
namespace _4 {

struct node {
    int x, y, t;
};

int n, m, start_x, start_y, end_x, end_y, visit[505][505][6];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char graph[505][505];

queue<node> q;
void bfs(int x, int y) {
    visit[x][y][0] = 1;
    int new_x, new_y;
    q.push({x, y, 0});
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y, t = q.front().t;
        q.pop();
        //! 下一步有5种走法，上下左右和瞬移
        for (int i = 0; i < 5; ++i) {
            if (i == 4) {
                if (t < 5) {
                    new_x = n+1-x, new_y = m+1-y;
                    ++t;
                } else {
                    continue;
                }
            } else {
                new_x = x + dx[i];
                new_y = y + dy[i];
            }

            if (new_x >= 1 && new_x <= n && new_y >=1 && new_y <= m 
                && graph[new_x][new_y] != '#' && visit[new_x][new_y][t] == 0) {
                if (i == 4) {
                    visit[new_x][new_y][t] = visit[x][y][t-1]+1;
                } else {
                    visit[new_x][new_y][t] = visit[x][y][t] + 1;
                }

                if (graph[new_x][new_y] == 'E') return;
                q.push({new_x, new_y, t});
            }
        }
        
    }
}

int main() {
    cin >> n >> m;
    int ans = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == 'S') {
                start_x = i, start_y = j;
            } else if (graph[i][j] == 'E') {
                end_x = i, end_y = j;
            }
        }
    }

    bfs(start_x, start_y);
    for (int i = 0; i < 6; ++i) {
        if (visit[end_x][end_y][i]) {
            ans = visit[end_x][end_y][i] - 1;
        }
    }
    cout << ans;
}

}

namespace _5 {

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ab(n);
    for (int i = 0; i < n; ++i) {
        cin >> ab[i].first >> ab[i].second;
    }

    sort(ab.begin(), ab.end(), [](const auto& p1, const auto& p2) {
        return abs(p1.first - p1.second) < abs(p2.first - p2.second);
    });
    int ans = 0;

    int xMax = ab[0].first, yMax = ab[0].second;
    for (int i = 1; i < n; ++i) {
        int cur;
        if (ab[i].first < ab[i].second) cur = xMax + ab[i].first;
        else cur = ab[i].second + yMax;

        ans = max(cur, ans);
        xMax = max(xMax, ab[i].first);
        yMax = max(yMax, ab[i].second);
    }
    cout << (double)ans / 2 << endl;
}


}

//!图的遍历===================================================
namespace _6 {

using ll = long long;
int n, a[5005], root, ans = 1e9;
vector<int> e[5005];
// f代表前一个遍历的节点
void dfs(int r, int f, int deep) {
    if (r != root && a[r] == a[root]) {
        ans = min(ans, deep);
        return;
    }
    for (int i = 0; i < e[r].size(); ++i) {
        // 防止回头
        if (e[r][i] != f) {
            dfs(e[r][i], r, deep+1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int i, j, x, y;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        root = i;
        dfs(i, 0, 0);
    }
    cout << (ans == 1e9 ? -1 : ans);
    return 0;
}

}

//!01背包问题===================================================
namespace _7 {

constexpr int N = 1e5;
int n, m, k;
int a[N], b[N];


int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = 1;
    }
    cin >> k;
    
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        a[x] += a[y]; a[y] = 0;
        b[x] += b[y]; b[y] = 0;
    }
    
    vector<vector<int>> f(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
           if (j >= a[i]) {
               f[i][j] = max(f[i-1][j], f[i-1][j-a[i]] + b[i]);
           } else {
               f[i][j] = f[i-1][j];
           }
        }
    }

    cout << f[n][m] << endl;
    return 0;
}

}

//!动态规划——矩阵地图路径========================================
namespace _8 {

constexpr int N = 105;
int n, m;
int a[N][N];

int solve() {
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    dp[1][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 1) continue;
            for (int k = i; k >= 1 && k >= i-20; --k) {
                for (int l = j; l >= 1 && l >= j-20; --l) {
                    if (i-k+j-l <= a[k][l]) {
                        dp[i][j] = (dp[i][j] + dp[k][l]) % 10000;
                    }
                }
            }
        }
    }
    return dp[n][m];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
            }
        }
        cout << solve() << endl;
    }

}

}

//! 滑动窗口===================================================
namespace _9 {

constexpr int N = 400005;
int n, m;
int a[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    unordered_map<int, int> cnt;
    int valid = 0;
    int l = 1, r = 1;
    long long ans = 0;
    while (r <= n) {
        while (r <= n && valid == 0) {
            ++cnt[a[r]];
            if (cnt[a[r]] == m) {
                ++valid;
            }
            ++r;
        }

        while (valid > 0) {
            ans += (n - r + 2);

            if (cnt[a[l]] == m) {
                --valid;
            }
            --cnt[a[l]];
            ++l;
        }
    }

    cout << ans;
}
}

//! 转化成最大连续上升子序列问题，子序列里面的元素可以不移动，
//! 子序列之外的元素需要移动插入到子序列中去，所以答案就是序列总长度减去最大连续上升子序列长度。
namespace _10 {

using ll = long long;
int n, a[100005], b;
map<int, int> mp;

int main() {
    int i, j, ans = 0, cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b;
        mp[b] = i;
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = mp[a[i]];
    }

    for (int i = 1; i <= n; ++i) {
        // 求最大连续上升子段
        if (a[i] > a[i-1]) {
            ans = max(ans, ++cnt);
        } else {
            cnt = 1;
        }
    }
    cout << n - ans;
}

}

} 


namespace _Alibaba_2 {
//*************************************************************************
namespace _1 {


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k;
    cin >> n >> k;
    map<vector<int>, int> pool;
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> cur;
        vector<int> rev;
        int prev;
        cin >> prev;
        for (int j = 1; j < k; ++j) {
            int curr; cin >> curr;
            cur.push_back(curr - prev);
            rev.push_back(prev -curr);
        }
        if (pool.find(rev) != pool.end()) {
            ans += pool[rev];
        }
        pool[cur] += 1;
    }
    cout << ans << endl;
}

}

//**************************************************************************
namespace _2 {

vector<vector<int>> ans;
int n, m;
void backtrack(vector<int>& path) {
    if (path.size() == m) {
        ans.push_back(path);
    }

    int start = path.empty() ? 1 : path.back() + 1;
    for (int i = start; i <= n; ++i) {
        path.push_back(i);
        backtrack(path);
        path.pop_back();
    }
}

int main() {
    cin >> n >> m;
    vector<int> path;
    backtrack(path);
    for (const vector<int>& v : ans) {
        for (int i : v) cout << i << " ";
        cout << '\n';
    }
}

}

//**************************************************************************
namespace _3 {

int crossRiver(vector<int>& p) {
    sort(p.begin(), p.end());
    int n = p.size();
    int time = 0;
    while ( n >= 4) {
        // 1. 最轻的每次都过去将船开回来， 每次载一个
        // 2. 最轻的俩先过去， 最轻的那个开船回来让最重的两个过去， 次轻的开回来
        time += min(p[0]*2 + p[n-2] + p[n-1], p[0] + p[1]*2 + p[n-1]);
       n -= 2;
    }
    if (n == 3) time += p[0] + p[1] + p[2]; // 最轻的依次把其他人运过去
    else if (n == 2) time += p[1];
    else if (n == 1) time += p[0];

    return time;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];
        cout << crossRiver(p) << '\n';
    }
}

}

//***************************************************************************
namespace _4 {

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    while (b != 0) {
        int temp = a % b;
        a = b;
        b =temp;
    }
    return a;
}

int main() {
    int A, B, a, b;
    cin >> A >> B >> a >> b;
    
    int d = gcd(a, b);
    a /= d; b /= d;
    int u = min(A / a, B / b);
    cout << u * a << " " << u * b;
}

}

//***************************************************************************
namespace _5 {

int main() {
    int n; cin >> n;
    vector<int> xs(n);
    for (int i = 0, tmp; i < n; ++i) {
        cin >> xs[i] >> tmp;
    }

    nth_element(xs.begin(), next(xs.begin(), n/2), xs.end());
    int mid = xs[n/2];
    long long res = 0;
    for (int x : xs) res += abs(x - mid);
    cout << res;
}

}

// 为保证绝对值差之和最大，就要保证所有数对的绝对值尽可能均匀
namespace _6 {

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    vector<int> ans; ans.reserve(n);
    int mid = n % 2 == 0 ? n/2 : n/2+1;
    int p1 = 0, p2 = mid;
    while (p1 < mid && p2 < n) {
        ans.push_back(a[p1++]);
        ans.push_back(a[p2++]);
    }
    if (p1 < mid) ans.push_back(a[p1]);
    if (p2 < n) ans.push_back(a[p2]);
    long long sum = 0;

    for (int i = 0; i < n-1; ++i) sum += abs(ans[i] - ans[i+1]);
    cout << sum + abs(ans[0] - ans.back()) << '\n';
    for (int val : ans) cout << val << " ";
}


}

//***************************************************************************
//动态规划 绝对值
namespace _7 {

int main() {
    int n; cin >> n;
    vector<vector<int>> a(3, vector<int>(n));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    vector<vector<long long>> dp(3, vector<long long>(n));
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < 3; ++i) {
            dp[i][j] = min({
                abs(a[i][j] - a[0][j-1]) + dp[0][j-1],
                abs(a[i][j] - a[1][j-1]) + dp[1][j-1],
                abs(a[i][j] - a[2][j-1]) + dp[2][j-1]
            });
        }
    }
    cout << min({dp[0][n-1], dp[1][n-1], dp[2][n-1]});
}

}

namespace _8 {

int main() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int>b(n+1, 1);
    for (int i = n; i >= 1; --i) b[a[i]] += b[i];
    for (int i = 1; i <= n; ++i) cout << b[i] << '\n';
}

}

namespace _9 {

int main() {
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<char> str(n);
        for (int i = 0; i < n; ++i) cin >> str[i];

        vector<char> res;
        m = n - m;
        for (int i = 0; i < n; ++i) {
            while (!res.empty() && str[i] < res.back() && res.size()+n-i >m) {
                res.pop_back();
            }
            if(res.size() < m) res.push_back(str[i]);
        }
        for (int i = 0; i < m; ++i) cout << res[i];
        cout << '\n';
    }
}

}

} // namespace
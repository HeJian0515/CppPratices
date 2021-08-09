#include <bits/stdc++.h>
using namespace std;

// 原地旋转图像(nxn矩阵) 顺时针90°
namespace _48rotate
{
//! 对于矩阵中第i行和第j个元素，在旋转后，他出现在倒数第i列的第j个位置
// matrix_new[col][n-row-1] = matrix[row][col]
void rotate(vector<vector<int>>& matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < (n+1)/2; ++j) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n-j-1][i];
            matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
            matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
            matrix[j][n-i-1] = temp;
        }
    }
}
}

// 按上述方法轮转4次
namespace _5776findRotation
{
bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target)
{   
    int n = mat.size();
    // 最多旋转4次
    int temp;
    for (int k = 0; k < 4; ++k) {
        // 旋转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n+1)/2; ++j) {
                temp = mat[i][j];
                mat[i][j] = mat[n-j-1][i];
                mat[n-j-1][i] = mat[n-i-1][n-j-1];
                mat[n-i-1][n-j-1] = mat[j][n-i-1];
                mat[j][n-i-1] = temp;
            }
        }
        if (mat == target) return true;
    }
    return false;
}
}

namespace _5777reductionOperations
{
int reductionOperations(vector<int>& nums)
{
    map<int, int> mp;
    for (int num : nums) {
        ++mp[num];
    }

    int ans = 0, acc = 0;
    for (auto it = mp.crbegin(); it != mp.crend(); ++it)
    {
        int f = it->second;
        ans += acc; // 最大的值变为次大的值 完成一次操作
        acc += f; // 记录现在最大的值有
    }
    return ans;
}
}

namespace _5578minFlips
{
int minFlips(string s)
{
    auto I = [](char ch, int x) -> int {
        return ch - '0' == x;
    };

    int n  = s.size();
    vector<vector<int>> pre(n, vector<int>(2));

    // pre[i][j] 变成以j结尾的交替字符串需要的1类型操作
    for (int i = 0; i < n; ++i) {
        pre[i][0] = (i == 0 ? 0 : pre[i-1][1]) + I(s[i], 1);
        pre[i][1] = (i == 0 ? 0 : pre[i-1][0]) + I(s[i], 0);
    } 

    int ans = min(pre[n-1][0], pre[n-1][1]);   

    if (n % 2 == 1)
    {
        // 如果n是奇数，还需要求出suf
        vector<vector<int>> suf(n, vector<int>(2));

        // 如果n是奇数，还需要求出suf; suf[i][j]     
        for (int i = n - 1; i >= 0; --i) {
            suf[i][0] = (i == n-1 ? 0 : suf[i+1][1]) + I(s[i], 1);
            suf[i][1] = (i == n-1 ? 0 : suf[i+1][0]) + I(s[i], 0);
        }

        for (int i = 0; i+1 < n; ++i) {
            ans = min(ans, pre[i][0] + suf[i+1][0]);
            ans = min(ans, pre[i][1] + suf[i+1][1]);
        }
    }
    return ans;
}
}

namespace _128longestConsecutive
{
int longestConsecutive(vector<int>& nums)
{
    unordered_set<int> numSet(nums.cbegin(), nums.cend());
    int ans = 0;

    for (const int& num : numSet) {
        if (!numSet.count(num-1)) {
            int curNum = num;
            int curLen = 1;

            while (numSet.count(curNum + 1)) {
                ++curNum;
                ++curLen;
            }
            ans = max(ans, curLen);
        }
    }
    return ans;
}
}


namespace _645findErrorNums
{
vector<int> findErrorNums(vector<int>& nums)
{
    vector<int> ans; ans.reserve(2);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        // 如果i+1位置 不等于nums[i]
        while (i+1 != nums[i]) { 
            // 如果nums[i]-1位置的元素等于nums[i] 则nums[i]重复
            if (ans.empty() && nums[i] == nums[nums[i] - 1]) {
                ans.push_back(nums[i]); 
                break;
            }

            // 如果又访问到重复的元素 跳过
            if (!ans.empty() && nums[i]==ans[0]) break;
            swap(nums[i], nums[nums[i]-1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != i+1) {
            ans.push_back(i+1);
            break;
        }
    }
    return ans;
}

vector<int> findErrorNums_1(vector<int>& nums)
{
    int n = nums.size();
    int dup = -1;

    for (int i = 0; i < n; ++i) {
        int index = abs(nums[i]) - 1;
        // nums[index] 小于0 则说明重复访问
        if (nums[index] < 0) {
            dup = abs(nums[i]);
        } else {
            nums[index] = -nums[index];
        }
    }

    int missing = -1;
    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            missing = i + 1;
        }
    }
    
    return {dup, missing};
}
}


// 二分查找山峰
namespace _852peakIndexInMountainArray
{
int peakIndexMountainArray(vector<int>& arr)
{   
    int n = arr.size();
    int l = 1, r = n - 2, ans = 0;

    while (l <= r) {
        int mid = l + (r - l)/2;
        if (arr[mid] > arr[mid+1]) {
            ans = mid;
            r = mid -1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}
}

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

namespace _temp {

void solve() {
    int t, e, s;
    int N; cin >> N;
    stack<pair<int, int>> id_st;
    int child_time;
    int max_time_id = INT_MAX;
    int max_time = -1;
    while (N--) {
        child_time = 0;
        cin >> t >> e >> s;
        if (s == 0) {
            id_st.push({t, e});
        } else if (s == 1) {
            while (id_st.top().second == -1) {
                child_time += id_st.top().first;
                id_st.pop();
            }
            int temp_time = t - id_st.top().first - child_time;
            if (max_time < temp_time || (max_time == temp_time && max_time_id > e)) {
                max_time = temp_time;
                max_time_id = e;
            }
            id_st.pop();
            id_st.push({temp_time + child_time, -1});
        }
    }
    cout << max_time_id << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
}

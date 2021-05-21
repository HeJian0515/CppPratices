#include <queue>
#include <vector>
#include <functional>
#include <limits.h>
using namespace std;


namespace _502findMaximizedCapital
{

int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
{   
    bool speedUp = true;
    for (int c : capital) if (w < c) speedUp = false;

    // 全都可以选择
    if (speedUp) {
        priority_queue<int, vector<int>, greater<int>> pq ;
        for (int p : profits) {
            pq.push(p);
            if (pq.size() > k) pq.pop();
        }

        while (!pq.empty()) {
            w += pq.top();
            pq.pop();
        }
        return w;
    }

    int n = profits.size();

    // 构造节点
    struct Node{
        int capital;
        int profit;
    };
    vector<Node> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i].capital = capital[i];
        nodes[i].profit = profits[i];
    }
    // 按所需资本排列成小顶堆
    auto cmp = [](const Node* n1, const Node* n2) { return n1->capital > n2->capital;};
    priority_queue<Node*, vector<Node*>, decltype(cmp)> projects(cmp);
    for (int i = 0; i < n; ++i) {
        projects.push(&nodes[i]);
    }

    // 1. 每次拥有本金w 大于等于所需资本时，从 选取队列 中取出节点加入 可行队列 中，
    // 2. 从可行队列中取出利润最大的节点，更新拥有本金，继续1
    priority_queue<int> available;
    while (k > 0)
    {
        while (!projects.empty() && projects.top()->capital <= w) {
            available.push(projects.top()->profit);
            projects.pop();
        }
        if (!available.empty())
        {
            w += available.top();
            available.pop();
            --k;
        } else {
           break;
        }
    }

    return w;
}
}


namespace _871minRefuelStops
{
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations)
{
    // 距离小的排在前面
    auto cmp_dis = [&](const int i, const int j) {
        return stations[i][0] > stations[j][0];
    };
    // 加油多的排在前面
    auto cmp_fuel = [&](const int i, const int j) {
        return stations[i][1] < stations[j][1];
    };

    // 按距离从小到大建堆
    priority_queue<int, vector<int>, decltype(cmp_dis)> disHeap(cmp_dis);
    int n = stations.size();
    for (int i = 0; i < n; ++i) {
        disHeap.push(i);
    }

    //! 算法思想，每次油用光了，找到已经路过的能加油最多的加油站加油
    int ans = 0;
    priority_queue<int, vector<int>, decltype(cmp_fuel)> fuelHeap(cmp_fuel);
    int distance = startFuel; // 汽车能行驶的里程
    while (true) {
        // 判断当前油量能否走完全程
        target -= startFuel;
        if (target <= 0) return ans;

        // 将油耗光前路过的加油站放入 候选队列
        while (!disHeap.empty() && stations[disHeap.top()][0] <= distance) {
            fuelHeap.push(disHeap.top());
            disHeap.pop();
        }

        if (fuelHeap.empty()) return -1;

        // 取出路过的能加油最多的加油站加油
        startFuel = stations[fuelHeap.top()][1];
        distance += startFuel; // 更新汽车能走过的里程
        fuelHeap.pop();// 将该加油站从候选队列中删除
        ++ans;
    }

    return ans;
}
}

namespace _253minMeetingRooms
{
int minMeetingRooms(vector<vector<int>>& intervals)
{
    int n = intervals.size();
    if (n == 0) return 0;

    sort(intervals.begin(), intervals.end(), 
        [](const vector<int>& v1, const vector<int>& v2) {return v1[0] < v2[0];});
    // 小顶堆
    auto cmpByStart = [&intervals](const int i, const int j) {return intervals[i][1] > intervals[j][1];};
    vector<int> v; v.reserve(n);
    priority_queue<int, vector<int>, decltype(cmpByStart)> minHeap(cmpByStart, v);

    minHeap.push(0); // 将第一个开始的会议加入队列

    // 最小堆堆顶中元素代表最早结束的会议
    // 如果后面的会议的开始时间在在这结束之后，这可以把这个会议室给后面的会议， 更新结束时间
    // 对应是弹出堆顶元素，再加入新元素
    for (int i = 1; i < n; ++i) {
        if (intervals[i][0] >= intervals[minHeap.top()][1]) {
            minHeap.pop();
        }

        minHeap.push(i);
    }

    return minHeap.size();
}
}

namespace _787findCheapestsPrice
{
namespace dfs {
vector<vector<int>> graph;
vector<char> visited;
int ans = INT_MAX;

// 从src出发， 到dst为止，最多经过k站
void dfs(int src, int dst, int k, int cost)
{
    if (src == dst) {
        ans = cost;
        return;
    }

    if (k == 0) return;

    for (int i = 0; i < graph[src].size(); ++i)
    {
        if (graph[src][i] > 0) {
            if (visited[i]) continue;

             // 剪枝
            if (cost + graph[src][i] > ans) {
            continue;
            }

            visited[i] = true;
            dfs(i, dst, k-1, cost + graph[src][i]);
            visited[i] = false;
        }
    }
}
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{   
    k = min(k, n-1); 

    vector<vector<int>>(n, vector<int>(n, 0)).swap(graph);
    for (vector<int>& flight : flights) {
        graph[flight[0]][flight[1]] = flight[2];
    }

    vector<char>(n, false).swap(visited);

    dfs(src, dst, k+1, 0);

    if (ans == INT_MAX) return -1;
    return ans;
}
}

namespace Dijkstra
{
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{
    vector<vector<int>> graph(n, vector<int>(n)); // 邻接矩阵， 0表示不连通
    for (vector<int>& flight : flights) {
        graph[flight[0]][flight[1]] = flight[2];
    }

    auto cmp_dis = [](const array<int, 3>& v1, const array<int, 3>& v2) { return v1[1] > v2[1];};
    // 向集合中添加一个记录(起点，费用，站数限制)的数组，K+1可以表示走过的站点个数
    priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(cmp_dis)> minHeap(cmp_dis);
    minHeap.push({src, 0, k+1});

    while (!minHeap.empty())
    {   
        auto [v, price, k] = minHeap.top(); minHeap.pop();
        if (v == dst) {
            return price;
        }

        if (k > 0) {
            for (int i = 0; i < n; ++i) {
                // 并且存在一条有向边
                if (graph[v][i] > 0) {
                    // 优先队列中存入：有向边指向的顶点 i、从起点 src 到 i 的总路径长度、还有多少站可以中转
                    minHeap.push({i, price+graph[v][i], k-1});
                }
            }
        }
    }
    return -1;
}
}

namespace dp 
{
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
{
    // dp[i][k]是经过最多k个中点站后到达站i的最小费用
    vector<vector<int>> dp(n, vector<int>(k+1, INT_MAX));
    
    for (vector<int>& flight : flights) {
        if (flight[0] == src) {
            dp[flight[1]][0] = flight[2];
        }
    }
    
    // 循环初始化数组中dst == src的行
    for (int i = 0; i <= k; ++i) {
        dp[src][i] = 0;
    }

    //直达的已经初始化了（即k = 0的情况），现在从k = 1 的开始，即只有一个中转站开始
    for (int i = 1; i <= k; ++i) {
        for (vector<int>& flight : flights) {
            if (dp[flight[0]][i-1] != INT_MAX) {
                dp[flight[1]][i] = min(dp[flight[1]][i], dp[flight[0]][i-1] + flight[2]);
            }
        }
    }

    return dp[dst][k] == INT_MAX ? -1 : dp[dst][k];
}
}
}
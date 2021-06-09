#include <queue>
#include <vector>
#include <functional>
#include <limits.h>
#include <set>
#include <iostream>
using namespace std;


class MaxHeap
{
    vector<int> heap;

public:
    int top() { return heap[0];}

    // 插入任意值; 把新的数字放在最后一位，然后上浮
    void push(int k)
    {
        heap.push_back(k);
        swim(heap.back());
    }

    // 删除最大值：把最大值挪到开头，然后下沉
    void pop()
    {
        heap[0] = heap.back();
        heap.pop_back();
        sink(0);
    }

private:
    // 上浮
    void swim(int pos)
    {
        // 孩子大于父亲
        while (pos > 1 && heap[(pos-1)/2] < heap[pos]) {
            swap(heap[(pos-1)/2], heap[pos]);
            pos = (pos - 1) / 2;
        }
    }

    void sink(int pos)
    {
        while (2 * pos < heap.size())
        {
            int i = 2 * pos + 1;
            if (i < heap.size()-1 && heap[i] < heap[i+1]) ++i; // 取出孩子中大的索引
            if (heap[pos] >= heap[i]) break;
            swap(heap[pos], heap[i]);
            pos = i;
        }
    }
};


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
    const int n = intervals.size();
    if (n == 0) return 0;

    sort(intervals.begin(), intervals.end(), 
        [](const vector<int>& v1, const vector<int>& v2) {return v1[0] < v2[0];});
    // 小顶堆
    auto cmpByStart = [&intervals](const int i, const int j) {return intervals[i][1] > intervals[j][1];};
    priority_queue<int, vector<int>, decltype(cmpByStart)> minHeap(cmpByStart);

    minHeap.push(0); // 将第一个开始的会议加入队列

    // 最小堆堆顶中元素代表最早结束的会议
    // 如果后面的会议的开始时间在在这结束之后，这可以把这个会议室给后面的会议， 更新这个会议室的最终结束时间
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

//!==============================================================
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

namespace _218getSkyline
{
namespace multiset__
{
vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
{
    multiset<pair<int, int>> all;
    vector<vector<int>> res;

    // 左坐标相同时, 高的在前面
    // 右坐标相同时, 低的在前面
    // 一左一右是， 左坐标在前
    for (auto& e : buildings) {
        all.insert(make_pair(e[0], -e[2]));
        all.insert(make_pair(e[1], e[2]));
    }

    multiset<int> heights{{0}}; // 保存当前位置所有高度
    vector<int> last = {0, 0}; // 保存上一个位置的横坐标以及高度

    for (auto& p : all)
    {
        if (p.second < 0) {
            heights.insert(-p.second); // 左端点，高度入堆
        } else {
            heights.erase(heights.find(p.second)); // 右端点，移除高度
        }

        // 当前关节点，最大高度
        auto maxHeight = *heights.rbegin();

        // 当前最大高度如果不同于上一个高度，说明这是一个转折点
        if (last[1] != maxHeight) {
            // 更新last，并加入结果集
            last[0] = p.first;
            last[1] = maxHeight;
            res.push_back(last);
        }
    }
    return res;
}

vector<vector<int>> getSkyline_1(vector<vector<int>>& buildings)
{
    int n = buildings.size();
    vector<pair<int, int>> points;  points.reserve(2*n);
    for (const auto& building : buildings) {
        points.emplace_back(make_pair(building[0], -building[2]));
        points.emplace_back(make_pair(building[1], building[2]));
    }

    sort(points.begin(), points.end());
    multiset<int> heights;
    heights.insert(0);
    int MaxH = 0;

    vector<vector<int>> keyPts;
    for (auto [x_pos, hei] : points)
    {
        if (hei < 0) {
            heights.insert(-hei);
        } else {
            heights.erase(heights.find(hei));
        }

        int curMaxH = *heights.rbegin();
        // 看新加入/删除的建筑高度是否影响了建筑的最大高度
        // 当前最大高度不等于原先的最大高度就表示这是一个高度突变点
        if (curMaxH != MaxH) {
            keyPts.push_back({x_pos, curMaxH});
            MaxH = curMaxH;
        }
    }
   return keyPts;

}

}


vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
{
    vector<vector<int>> ans;
    // 获取目前会拔高天际线，且妨碍到前一个建筑物(的右端端点)的下一个建筑物
    priority_queue<pair<int, int>> max_heap; // 高度，右端
    int i= 0, len = buildings.size();
    int curX, curH;
    while (i < len || !max_heap.empty())
    {
        // 当前建筑一部分在 队内建筑内
        if (max_heap.empty() || (i < len && buildings[i][0] <= max_heap.top().second))
        {
            curX = buildings[i][0];
            while (i < len && curX == buildings[i][0]) {
                max_heap.emplace(buildings[i][2], buildings[i][1]);
                ++i;
            }
        } else { 
            curX = max_heap.top().second;
            while (!max_heap.empty() && curX >= max_heap.top().second) {
                max_heap.pop();
            }
        }
        curH = (max_heap.empty() ? 0 : max_heap.top().first);
        if (ans.empty() || curH != ans.back()[1]) {
            ans.push_back({curX, curH});
        }
    }
    return ans; 
}

}

// 从空闲服务器队列取出服务器，加入忙服务器队列
// 任务完成后,忙服务器从队列中取出，继续加入空闲服务器
// 空闲服务器根据权重由小到大排列
// 忙服务器根据结束时间由前向后排列
namespace _1882assignTasks
{
using PII = pair<int, int>;

vector<int> assignTasks(vector<int>& servers, vector<int>& tasks)
{
    int m = servers.size();
    int n = tasks.size();

    // 工作中的服务器，存储二元组(t， idx)  ---t 结束时间
    priority_queue<PII, vector<PII>, greater<PII>> busy;
    // 空闲的服务器，存储二元组(w, idx)   ---w 权重
    priority_queue<PII, vector<PII>, greater<PII>> idle; 
    for (int i = 0; i < m; ++i) {   
        idle.emplace(servers[i], i);
    }  

    int ts = 0; 
    // 将优先队列busy中满足 t <= ts 依次取出并放入优先队列 idle
    auto release = [&]() {
        while (!busy.empty() && busy.top().first <= ts) {
            auto&& [_, idx] = busy.top();
            idle.emplace(servers[idx], idx);
            busy.pop();
        }
    };

    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        ts = max(ts, i);
        release();

        if (idle.empty()) {
            ts = busy.top().first;
            release();
        }

        auto&& [_, idx] = idle.top();
        ans.push_back(idx);
        busy.emplace(ts+tasks[i], idx);
        idle.pop();
    }

    return ans;

}
}

// 每次从队列取出要投放的广告，更新其结束时间在放回去
namespace _TX_04_18_2
{
struct node
{
    int t;      // 间隔多少才能再次投放
    int id; 
    int stamp; // 结束的时间

    bool operator<(const node& other) const {
        return stamp == other.stamp ? id > other.id : stamp > other.stamp;
    }
};


int main(void)
{
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    priority_queue<node> q;

    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        q.push(node{t, i, t});
    }

    int ts = 0;
    while (k--)
    {
        node x = q.top(); q.pop();
        cout << x.id;
        q.push(node{x.t, x.id, x.stamp + x.t});
    }
    
    return 0;
}
}
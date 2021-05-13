#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

void merge(vector<int>& input, int lo, int mid, int hi, vector<int>& temp) {
    int i = lo;       // 第一段序列下标
    int j = mid;  //第二段序列的下标
    int k = 0;        // 临时存放合并序列的下标

    // 扫描第一段和第二段序列，直到有一个扫描结束
    while (i < mid && j < hi) {
        // 判断第一段和第二段取出的数哪个更小，将其存入合并序列，并继续向下扫描
        if (input[i] <= input[j])
            temp[k++] = input[i++];
        else
            temp[k++] = input[j++];
    }

    // 若第一段序列还没扫描完，将其全部复制到合并序列中
    while (i < mid) {
        temp[k++] = input[i++];
    }
    // 若第二段段序列还没扫描完，将其全部复制到合并序列中
    while (j < hi) {
        temp[k++] = input[j++];
    }

    k = 0;
    // 将合并序列复制到原始序列中
    while (lo < hi) {
        input[lo++] = temp[k++];
    }
}

void mergeSort(vector<int>& input, int lo, int hi, vector<int>& temp) {
    if (hi - lo < 2) return;
    int mid = (lo + hi) / 2;
    mergeSort(input, lo, mid, temp);
    mergeSort(input, mid, hi, temp);
    merge(input, lo, mid, hi, temp);
}

void mergeSort(vector<int>& input) {
    vector<int> temp(input.size());
    mergeSort(input, 0, input.size(), temp);
}


// 桶排序===============================================================
namespace __451frequencySort
{
string frequencySort(string s)
{
    unordered_map<char,int> cntMap;
    int maxCnt = 0;
    for (const char c : s) {
        maxCnt = max(maxCnt, ++cntMap[c]);
    }

    vector<vector<char>> buckets(maxCnt+1);

    for (const auto&[k, v] : cntMap)
    {
        buckets[v].push_back(k);
    }

    string ans;
    ans.reserve(s.size());

    for (int i = maxCnt; i >= 0; --i) {
       for (int j = buckets[i].size()-1; j >= 0; --j) {
           int cnt = i;
           while (cnt--) {ans.push_back(buckets[i][j]);}
       }
    }
    return ans;
}

// 优先队列
string frequencySort_1(string s)
{
    unordered_map<char, int> chCntMap;
    for (char c : s) { ++chCntMap[c]; }

    using pair_ = pair<char, int>;
    auto cmp = [](const pair_& p1, const pair_& p2) {
        return p1.second < p2.second;
    };
    priority_queue<pair_, vector<pair_>, decltype(cmp)> pq(cmp);
    for (auto& it : chCntMap) {
        pq.emplace(it.first, it.second);
    }

    string ans; ans.reserve(s.size());

    while (!pq.empty()) {
        auto& p = pq.top();
        int cnt = p.second;
        while(cnt--) ans.push_back(p.first);

        pq.pop();
    }

    return ans;
}
}

// 桶排序
namespace _347topKFrequent
{
vector<int> topKFrequent(vector<int>& nums, int k)
{
    unordered_map<int, int> cntMap;
    int maxCnt = 0;
    for (int num : nums) {
        maxCnt = max(maxCnt, ++cntMap[num]);
    }

    vector<vector<int>> buckets(maxCnt+1);
    for (auto& [num, f] : cntMap) {
        buckets[f].push_back(num);
    }

    vector<int> ans;
    ans.reserve(k);
    for (int i = maxCnt; i >= 0; --i)
    {
        if (!buckets[i].empty()) {
            for (int num : buckets[i]) {
                if (ans.size() == k) return ans;
                ans.push_back(num);
            }
        }
    }

    return ans;
}

vector<int> topKFrequent_1(vector<int>& nums, int k)
{
    unordered_map<int, int> cntMap;
    int maxCnt = 0;
    for (int num : nums) {
        maxCnt = max(maxCnt, ++cntMap[num]);
    }

    using pair_ = pair<int, int>; // 1 频率 2 数字
    auto cmp = [](const pair_& p1, const pair_& p2) {
        return p1.first < p2.first;
    };
    priority_queue<pair_, vector<pair_>, decltype(cmp)> pq(cmp);
    for (auto& [num, f] : cntMap) {
        pq.emplace(f, num);
    }

    vector<int> ans; ans.reserve(k);
    while (k--) {
        auto& p = pq.top();
        ans.push_back(p.second);
        pq.pop();
    }
    return ans;
}
}
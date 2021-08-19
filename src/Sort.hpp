#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <random>
#include <unordered_map>

using namespace std;

//! 快速选择出第n大的数
namespace _215findKthLargest
{
int QuickSort(vector<int>& nums, int l, int r)
{
    int randIndex = l + rand()%(r-l+1);
    int pivot = nums[randIndex];
    swap(nums[l], nums[randIndex]);

    while (l < r)
    {
        while (l < r && nums[r] > pivot) {
            --r;
        }
        nums[l] = nums[r];

        while (l < r && nums[l] <= pivot) {
            ++l;
        }
        nums[r] = nums[l];
    }

    nums[l] = pivot;
    return l;
}

int findKthLargest(vector<int>& nums, int k)
{   
    int n = nums.size();
    k = n - k;
    srand(time(NULL));
    int l = 0, r = n-1;
    for (;;)
    {
        int pos = QuickSort(nums, l, r);
        if (pos == k) {
            return nums[pos];
        } else if (pos < k) {
            l = pos+1;
        } else {
            r = pos-1;
        }
    }
    return -1;
}
}

//! 桶排序求出现频率最高的的数
namespace _347topKFrequent
{
vector<int> topKFrequent(vector<int>& nums, int k)
{
    unordered_map<int, int> mp;
    int maxNum = 0;
    for (int n : nums) {
        maxNum = max(maxNum, ++mp[n]);
    }

    vector<vector<int>> buckets(maxNum+1);

    for (auto& [n, k] : mp)
    {
        buckets[k].push_back(n);
    }

    vector<int> ans; ans.reserve(k);
    for (int i = buckets.size()-1; i >= 0; --i)
    {
        if (!buckets[i].empty()) {
            for (int v : buckets[i]) {
                ans.push_back(v);
                if (ans.size() == k) {
                    return ans;
                }
            }
        }
    }
    return ans;
}
}

//! 桶排序——按出现频率排序字符
namespace _451frequencySort
{
string frequencySort(string s)
{
    unordered_map<char, int> chCnt;
    
    int maxNum = 0;
    for (char ch : s) {
        maxNum = max(maxNum, ++chCnt[ch]);
    }

    vector<vector<char>> buckets(maxNum+1);
    for (auto& [ch, cnt] : chCnt) {
        buckets[cnt].push_back(ch);
    }

    string ans; ans.reserve(s.size());

    for (int i = maxNum; i >= 0; --i)
    {
        if (!buckets[i].empty()) {
            
            for (char ch : buckets[i]) {
                for (int j = 0; j < i; ++j) {
                    ans.push_back(ch);
                }
            }
        }
    }
    return ans;
}
}

//! 荷兰国旗问题
namespace _75sortColor
{
void sortColors(vector<int>& nums)
{
    int p0 = 0, p2 = nums.size()-1;
    int cur = 0;

    while (cur <= p2) 
    {
        while (cur <= p2 && nums[cur] == 2) {
            swap(nums[cur], nums[p2]);
            --p2;
        }

        if (nums[cur] == 0) {
            swap(nums[p0], nums[cur]);
            ++p0;
        }
        ++cur;
    }
}
}

//! 计数排序
namespace _countingSort {
void countingSort(vector<int>& a, int n) {
    if (n <= 1) return;
    int max = a[0];
    for (int i = 1; i < n; ++i) {
        if (max < a[i]) max = a[i];
    } 

    vector<int> c(max+1);
    // 计算每个元素的个数，放入数组中
    for (int i = 0; i < n; ++i) ++c[a[i]];
    // 依次累加
    for (int i = 1; i < max; ++i) {
        c[i] = c[i-1] + c[i];
    }
    // 临时数组r，存储排序之后的结果
    vector<int> r(n);
    for (int i = n-1; i >= 0; --i) {
        int index = c[a[i]]-1;
        r[index] = a[i];
        --c[a[i]];
    }
    // 将结果复制给数组a
    for (int i = 0; i < n; ++i) a[i] = r[i];
}
}
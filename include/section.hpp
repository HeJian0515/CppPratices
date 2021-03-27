//! 区间问题
#include <algorithm>
#include <vector>

using namespace std;

namespace _1288removeCoveredIntervals
{
int removeCoveredIntervals(vector<vector<int>>& intervals)
{
    std::sort(intervals.begin(), intervals.end(),
        [](const auto& v1, const auto& v2) {
            if (v1[0] == v2[0]) {
                return v1[1] > v2[1];
            }
            return v1[0] < v2[0];
        });
    
    // 记录合并区间的起点和终点
    int left = intervals[0][0];
    int right = intervals[0][1];

    int res = 0;
    const int sizeIntervals = intervals.size();
    for (int i = 1; i < sizeIntervals; ++i){
        const vector<int>& v = intervals[i];

        // 情况一，找到覆盖区间
        if (right >= v[1]) {
            ++res;
        } // 情况二，区间有相交，合并区间
        else if (right >= v[0] && right < v[1]) {
            right = v[1];
        } // 情况三，区间完全不相交,更新left right
        else if (right < v[0]) {
            left = v[0];
            right =v[1];
        }
    }
    return sizeIntervals - res;    
}
}
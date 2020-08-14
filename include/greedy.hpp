#pragma once

#include <algorithm>
#include <vector>

using namespace std;

namespace _435Interval {  //! 435. 无重叠区间

static bool compare(vector<int>& a1, vector<int>& a2) {
    return a1.back() < a2.back();
}
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.size() < 1) return 0;
    std::sort(intervals.begin(), intervals.end(), [](vector<int>& a1, vector<int>& a2)->bool { return a1.back() < a2.back();});
    // 至少有一个区间相交
    int count = 1;
    int x_end = intervals[0].back();
    for (int i = 1; i < intervals.size(); ++i) {
        int x_start = intervals[i].front();
        if (x_start >= x_end) {
            ++count;
            x_end = intervals[i].back();
        }
    }
    return intervals.size() - count;
}
}  // namespace _435Interval
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;


namespace _69MySqrt{
int mySqrt(int x) {
    if (x <= 1) return x;
    int low = 1;
    int high = x;
    
    while (low <= high) {
        int mid = low + (high - low) >> 2;
        int sqrt = x / mid;
        if (sqrt == mid) {
            return mid;
        } else if (mid > sqrt) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return high;
}
}

namespace _875minEatingSpeed {

inline int TimeOf(int n, int speed) {
    return (n / speed) + ((n % speed > 0) ? 1 : 0);
}

bool CanFinish(const vector<int>& piles, int speed, int h)
{
    int time = 0;
    for (int n : piles) {
        time += TimeOf(n, speed);
    }
    return time <= h;
}

int minEatingSpeed(vector<int>& piles, int h)
{
    int left = 1;
    int right = (*std::max_element(piles.cbegin(), piles.cend())) + 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (CanFinish(piles, mid, h)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
}

namespace _1011shipWithinDay
{

// 如果载重为cap，能否在D天内运完货物
bool canFinish(const vector<int>& ws, int d, int cap) {
    int i = 0;
    for (int day = 0; day < d; ++day) {
        int maxCap = cap;
        while ((maxCap -= ws[i]) >= 0) {
            ++i;
            if (i == ws.size()) return true;
        }
    }
    return false;
}

int shipWithinDays(vector<int>& weights, int D) {
    int left = *(std::max_element(weights.cbegin(), weights.cend()));
    int right = std::accumulate(weights.cbegin(), weights.cend(), 0) + 1;
    while (left < right) {
        int mid = left + (right - left)/2;
        if (canFinish(weights, D, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
}


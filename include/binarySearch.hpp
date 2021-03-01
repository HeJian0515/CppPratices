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
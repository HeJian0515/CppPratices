#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;


namespace _461hammingDistance
{
int hammingDitance(int x, int y)
{
    return bitset<32>(x^y).count();
}

int hammingDistance(int x, int y) {
    int z = x ^ y;
    int distance = 0;
    // 统计z中有多少个 1
    while (z != 0) {
        ++distance;
        z = z & (z - 1); 
    }
    return distance;
}
}

namespace _136singleNumber
{
int singleNumber(vector<int>& nums)
{
    int ans = 0;
    for (int num : nums) {
        ans ^= num;
    }
    return ans;
}
}

namespace _268missingNumber
{
int missingNumber(vector<int>& nums)
{
    int missing = nums.size();
    for (int i = 0, n = missing; i < n; ++i) {
        missing ^= i ^ nums[i];
    }
    return missing;
}
}

namespace _260singleNumber
{
    vector<int> singleNumber(vector<int>& nums)
    {
        int ret = 0;
        for (int n : nums) {
            ret ^= n;
        }
        int div = 1;
        // 找到ret不为0的位
        while (0 == (div & ret)) {
            div <<= 1;
        }
        int a = 0;
        int b = 0;
        for (int n : nums) {
            if (div & n) {
                a ^= n;
            } else {
                b ^= n;
            }
        }
        return vector<int>{a, b};
    }
}

namespace _190reverseBits
{
uint32_t reverseBits(uint32_t n) {
    uint32_t ret = 0, power = 31;
    while (n != 0) {
        ret += (n & 1) << power; // 取出最后一位，移到前面的对应位置
        n = n >> 1; // 更新最后一位
        power -= 1;
    }
    return ret;
}
}

namespace _231isPowerTwo
{
    bool isPowerOfTwo(int n) {
        return n > 0 && 0 == (n & (n -1));
    }
}

namespace _693hasAlternatingBits
{
    bool hasAlternatingBits(int n) {
        int num = (n ^ (n >> 1));
        return 0 == (num & (num + 1));
    }
}
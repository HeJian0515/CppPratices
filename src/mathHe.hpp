#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>

using namespace std;

// 最大公因数
constexpr int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 最小公倍数
constexpr int lcm(int a, int b) {
    return a*b / gcd(a, b);
}

int xGCD(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, gcd = xGCD(b, a%b, x1, y1);
    x = y1, y = x1-(a-b)*y1;
    return gcd;
}

namespace _204countPrimes {
// 从1到n遍历，假设当前遍历到m，则把所有小于n的、且是m的倍数的整数标为合数
int countPrimes(int n)
{
    if (n <= 2) return 0;
    vector<char> prime(n, true);

    int cnt = n-2; // 去掉不是质数的1
    for (int i = 2; i < n; ++i) {
        if (prime[i]) {
            for (int j = 2*i; j < n; j += i) {
                if (prime[j]) {
                    prime[j] = false;
                    --cnt;
                }
            }
        }
    }
    return cnt;
}

int countPrimes_1(int n)
{
    if (n <= 2) return 0;
    vector<char> prime(n, true);
    int i = 3, sqrtn = sqrt(n), cnt = n / 2; // 偶数一定不是质数
    while (i <= sqrtn) { // 最小质因子一定小于等于开方数
        for (int j = i*i; j < n; j += 2*i) { // 只遍历奇数 i^2 + 2i + 4i + 6i
                --cnt;
                prime[j] = false;
        }
        do {
            i += 2;
        } while (i <= sqrtn && !prime[i]); // 避免偶数和重复遍历
    }
    return cnt;
}
}

namespace _504Base7
{
string convertToBase(int num)
{
    if (num == 0) return "0";
    bool isNeg = num < 0;
    if (isNeg) num = -num;

    string ans;
    while (num) {
        int a = num / 7, b = num % 7;
        ans = to_string(b) + ans;
        num = a;
    }

    return isNeg ? "-" + ans : ans;
}
}

namespace _172trailingZeroes
{
int trailingZeros(int n) {
    return n == 0 ? 0 : n / 5 + trailingZeros(n / 5);
}
}

namespace QuickPow
{
using LL = long long;

// 泛型的非递归快速幂
// 只要a的数据类型支持乘法且满足结合律，快速幂的算法都是有效的。
template <typename T>
T QuickPow(T a, LL n)
{
    T ans = 1;
    while (n) 
    {
        if (n & 1) {
            ans = ans * a; // 赋值为乘法单位元，可能要根据构造函数修改
        }
        n >>= 1;
        a = a * a; // 这里就最好别用自乘了，不然重载完*还要重载*=，有点麻烦。
    }
    return ans;
}


// 求出的斐波那些数列 Fn % 10^9+7 的值
#define MOD 1000000007
struct matrix
{   
    LL a11, a12, a21, a22;
    matrix (LL a11_, LL a12_, LL a21_, LL a22_) : a11(a11_), a12(a12_), a21(a21_), a22(a22_)
    {}

    matrix& operator=(const matrix& ) = default;

    matrix operator*(const matrix& y)
    {
        return matrix(
            (a11*y.a11 + a12*y.a21) % MOD,
            (a11*y.a12 + a12*y.a22) % MOD,
            (a21*y.a11 + a22*y.a21) % MOD,
            (a21*y.a12 + a22*y.a22) % MOD
        );
    }
};

matrix Qpow(matrix a, LL n)
{
    matrix ans(1, 0, 1, 0);
    while (n)
    {
        if (n & 1) {
            ans = ans * a;
        }
        a = a*a;
        n >>= 1;
    }
    return ans;
}
}

namespace _Mod_Factorial
{
// n!后面0的个数
int trailingZeros(int n)
{
    int res = 0;
    for (int d = n; d/5 > 0; d = d/5) {
        res += d/5;
    }
    return res;
}
//***********************************************************************************
//***********************************************************************************
// 现在是给你一个非负整数 K，问你有多少个 n，使得 n! 结果末尾有 K 个 0。
//! n!是递增的，所以找到最小的n就行

// trailingZeroes(n) == K的右侧边界
long right_bound(int target) 
{
    long lo = 0, hi = LONG_MAX;
    while (lo < hi) {
        long mid = lo + (hi -lo)/2;
        int zeros = trailingZeros(mid);
        if (zeros < target) {
            lo = mid + 1;
        } else if (zeros > target) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
// trailingZeros == k的左边界
long left_bound(int target) {
    long lo = 0, hi = LONG_MAX;
    while (lo < hi) {
        long mid = lo + (hi-lo)/2;
        int zeros = trailingZeros(mid);
        if (zeros < target) {
            lo = mid + 1;
        } else if (zeros > target) {
            hi = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int preimageSizeFZF(int K)
{
    // 左边界和右边界之差+1就是答案
    return right_bound(K) - left_bound(K) + 1;
}

//***********************************************************************************
//***********************************************************************************
int base = 1337;
//! a^[...] mod base
int mypow(int a, int k) {
    a %= base;
    int res = 1;
    for (int i = 0; i < k; ++i) {
        res *= a;
        res %= base;
    }
    return res;
}  

int superPow(int a, vector<int>& b) {
    if (b.empty()) return 1;
    int last = b.back();
    b.pop_back();

    int part1 = mypow(a, last);
    int part2 = mypow(superPow(a, b), 10);

    return (part1 * part2) % base;
}

}


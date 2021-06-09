#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// 原地旋转图像(nxn矩阵) 顺时针90°
namespace _48rotate
{
//! 对于矩阵中第i行和第j个元素，在旋转后，他出现在倒数第i列的第j个位置
// matrix_new[col][n-row-1] = matrix[row][col]
void rotate(vector<vector<int>>& matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n / 2; ++i) {
        for (int j = 0; j < (n+1)/2; ++j) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n-j-1][i];
            matrix[n-j-1][i] = matrix[n-i-1][n-j-1];
            matrix[n-i-1][n-j-1] = matrix[j][n-i-1];
            matrix[j][n-i-1] = temp;
        }
    }
}
}

// 按上述方法轮转4次
namespace _5776findRotation
{
bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target)
{   
    int n = mat.size();
    // 最多旋转4次
    int temp;
    for (int k = 0; k < 4; ++k) {
        // 旋转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n+1)/2; ++j) {
                temp = mat[i][j];
                mat[i][j] = mat[n-j-1][i];
                mat[n-j-1][i] = mat[n-i-1][n-j-1];
                mat[n-i-1][n-j-1] = mat[j][n-i-1];
                mat[j][n-i-1] = temp;
            }
        }
        if (mat == target) return true;
    }
    return false;
}
}

namespace _5777reductionOperations
{
int reductionOperations(vector<int>& nums)
{
    map<int, int> mp;
    for (int num : nums) {
        ++mp[num];
    }

    int ans = 0, acc = 0;
    for (auto it = mp.crbegin(); it != mp.crend(); ++it)
    {
        int f = it->second;
        ans += acc; // 最大的值变为次大的值 完成一次操作
        acc += f; // 记录现在最大的值有
    }
    return ans;
}
}

namespace _5578minFlips
{
int minFlips(string s)
{
    auto I = [](char ch, int x) -> int {
        return ch - '0' == x;
    };

    int n  = s.size();
    vector<vector<int>> pre(n, vector<int>(2));

    // pre[i][j] 变成以j结尾的交替字符串需要的1类型操作
    for (int i = 0; i < n; ++i) {
        pre[i][0] = (i == 0 ? 0 : pre[i-1][1]) + I(s[i], 1);
        pre[i][1] = (i == 0 ? 0 : pre[i-1][0]) + I(s[i], 0);
    } 

    int ans = min(pre[n-1][0], pre[n-1][1]);   

    if (n % 2 == 1)
    {
        // 如果n是奇数，还需要求出suf
        vector<vector<int>> suf(n, vector<int>(2));

        // 如果n是奇数，还需要求出suf; suf[i][j]     
        for (int i = n - 1; i >= 0; --i) {
            suf[i][0] = (i == n-1 ? 0 : suf[i+1][1]) + I(s[i], 1);
            suf[i][1] = (i == n-1 ? 0 : suf[i+1][0]) + I(s[i], 0);
        }

        for (int i = 0; i+1 < n; ++i) {
            ans = min(ans, pre[i][0] + suf[i+1][0]);
            ans = min(ans, pre[i][1] + suf[i+1][1]);
        }
    }
    return ans;
}
}

namespace _128longestConsecutive
{
int longestConsecutive(vector<int>& nums)
{
    unordered_set<int> numSet(nums.cbegin(), nums.cend());
    int ans = 0;

    for (const int& num : numSet) {
        if (!numSet.count(num-1)) {
            int curNum = num;
            int curLen = 1;

            while (numSet.count(curNum + 1)) {
                ++curNum;
                ++curLen;
            }
            ans = max(ans, curLen);
        }
    }
    return ans;
}
}


namespace _645findErrorNums
{
vector<int> findErrorNums(vector<int>& nums)
{
    vector<int> ans; ans.reserve(2);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        // 如果i+1位置 不等于nums[i]
        while (i+1 != nums[i]) { 
            // 如果nums[i]-1位置的元素等于nums[i] 则nums[i]重复
            if (ans.empty() && nums[i] == nums[nums[i] - 1]) {
                ans.push_back(nums[i]); 
                break;
            }

            // 如果又访问到重复的元素 跳过
            if (!ans.empty() && nums[i]==ans[0]) break;
            swap(nums[i], nums[nums[i]-1]);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (nums[i] != i+1) {
            ans.push_back(i+1);
            break;
        }
    }
    return ans;
}

vector<int> findErrorNums_1(vector<int>& nums)
{
    int n = nums.size();
    int dup = -1;

    for (int i = 0; i < n; ++i) {
        int index = abs(nums[i]) - 1;
        // nums[index] 小于0 则说明重复访问
        if (nums[index] < 0) {
            dup = abs(nums[i]);
        } else {
            nums[index] = -nums[index];
        }
    }

    int missing = -1;
    for (int i = 0; i < n; ++i) {
        if (nums[i] > 0) {
            missing = i + 1;
        }
    }
    
    return {dup, missing};
}
}
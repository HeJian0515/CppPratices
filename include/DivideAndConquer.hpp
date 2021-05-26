#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cassert>
using namespace std;



namespace _241DiffWaysToCompute {

unordered_map<string, vector<int>> memo;

vector<int>& Divide(const string& s)
{   
    if (memo.count(s)) return memo[s];

    vector<int> res;
    for (int i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if (c == '+' || c == '-' || c == '*')
        {
            vector<int>& left = Divide(s.substr(0, i));
            vector<int>& right = Divide(s.substr(i+1));
            res.reserve(left.size() * right.size());

            for (const int l : left) {
                for (const int r : right) {
                    switch (c) {
                        case '+': res.push_back(l+r); break;
                        case '-': res.push_back(l-r); break;
                        case '*': res.push_back(l*r); break;
                    }
                }
            }
            assert(res.size() == left.size()*right.size());
        }
    }
    
    if (res.empty()) res.push_back(stoi(s));
    vector<int>& ans = memo[s] = std::move(res);
    return ans;
}

vector<int> diffWaysToCompute(string expression)
{
    return Divide(expression);
}
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

namespace _95GenerateTrees {

vector<TreeNode*> GenetateTrees(int left, int right) {
    if (left > right) return {nullptr};
    vector<TreeNode*> allTrees;
    for (int i = left; i <= right; ++i) {
        // 左子树集合
        vector<TreeNode*> leftTress = GenetateTrees(left, i - 1);
        // 右子树集合
        vector<TreeNode*> rightTress = GenetateTrees(i+1, right);
        allTrees.reserve(leftTress.size() * rightTress.size());
        // 左右子树和根节点组成一颗树
        for (auto& leftRoot : leftTress) {
            for (auto& rightRoot : rightTress) {
                allTrees.emplace_back(new TreeNode(i, leftRoot, rightRoot));
            }
        }
    }
    return allTrees;
}

vector<TreeNode*> generateTrees(int n) {
    if (0 == n) return {};
    return GenetateTrees(1, n);
}
}

namespace _932beautifulArray
{
unordered_map<int, vector<int>> memo;

// 对[1,...,N],将其等分为两部分，left和right，如果left和right都是漂亮数组
// 同时left全是奇数,right全是偶数，那么left+right也是漂亮数组
// 如果知道了N的漂亮数组，通过变换让N->2N的奇部
vector<int>& f(int n)
{
    if (memo.count(n)) return memo[n];

    vector<int> res(n);
    if (n == 1) {
        res[0] = 1;
    } else {
        int t = 0;
        for (int x : f((n+1)/2)) { // 奇数放在左边
            res[t++] = 2*x - 1;
        }
        for (int x : f(n/2)) { // 偶数放在右边
            res[t++] = 2*x;
        }
    }
    memo[n] = move(res);
    return memo[n];
}

vector<int> beautifulArray(int n)
{
    return f(n);
}
}

namespace _312maxCoins
{
vector<vector<int>> rec;
vector<int> val;

int solve(int left, int right)
{
    if (left >= right-1) {
        return 0;
    }

    if (rec[left][right] != -1) {
        return rec[left][right];
    }

    for (int i = left+1; i < right; ++i) {
        int sum = val[left] * val[i] * val[right];
        sum += solve(left, i) + solve(i, right);
        rec[left][right] = max(rec[left][right], sum);
    }

    return rec[left][right];
}


int maxCoins(vector<int>& nums)
{
    int n = nums.size();
    val.resize(n+2);
    for (int i = 1; i <= n; ++i) {
        val[i] = nums[i-1];
    }
    val[0] = val[n+1] = 1;
    vector<vector<int>>(n+2, vector<int>(n+2, -1)).swap(rec);
    return solve(0, n+1);
}
}
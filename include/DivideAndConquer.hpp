#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cassert>
using namespace std;

namespace _241DiffWaysToCompute {

inline bool IsOperation(char c) {
    return '+'==c || '-'==c || '*'==c;
}

int caculate(int num1 , char c, int num2) {
    assert(IsOperation(c));
    switch (c)  {
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num1 - num2;
            break;
        case '*':
            return num1 * num2;
            break;
        default:
            return  0;
            break;
    }
}
// 备忘录——递归时去重
unordered_map<string, vector<int>> strVecMap;

bool iSDigital(const string& str) {
    for (int i = 0; i < str.size(); ++i) {
        if (IsOperation(str[i])) return false;
    }
    return true;
}
vector<int> DiffWaysToCompute(const string& input) {
    if (input.empty())  return {};

    if (strVecMap.count(input)) return strVecMap[input];

    vector<int> res;
    // 如果输入字符不包含操作符，只包含数字
    if (iSDigital(input)) {
        res.emplace_back(std::atoi(input.c_str()));
        strVecMap[input] = res;
        return res;
    }
    
    for (int i = 0; i < input.size(); ++i) {
        // 运算符将字符串分成两部分
        if (IsOperation(input[i])) {
            vector<int> LeftCalcRes = DiffWaysToCompute(input.substr(0, i));
            vector<int> RightCalcRes = DiffWaysToCompute(input.substr(i+1));
            // 将左右两个结果组合
            res.reserve(LeftCalcRes.size() * RightCalcRes.size());
            for (auto l : LeftCalcRes) {
                for (auto r : RightCalcRes) {
                    res.emplace_back(caculate(l, input[i], r));
                }
            }
        }
    }
    strVecMap[input] = res;
    return res;
}
vector<int> diffWaysToCompute(string input) {
    strVecMap.clear();
    return DiffWaysToCompute(input);
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
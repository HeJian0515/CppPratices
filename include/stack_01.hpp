#pragma once
#include <algorithm>
#include <numeric>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>
#include <climits>
#include <deque>
using namespace std;

// 栈实现队列
namespace _232MyQueue {
class MyQueue {
    stack<int> s1, s2;

void in2out() {
    if (s2.empty()) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }
}
public:
    MyQueue() {
    }

    void push(int x) {
        s1.push(x);
    }

    int pop() {
        in2out();
        int ret = s2.top();
        s2.pop();
        return ret;
    }

    int peek() {    
        in2out();
        return s2.top();
    }

    bool empty() {  
        return s1.empty() && s2.empty();
    }
};
}

namespace _84largestRectangleInHistogram {
int largestRectangleArea(vector<int>& heights) {
    heights.push_back(0);
    int len = heights.size();

    stack<int> increaseStack;  // 单调递增栈存放的是位置
    int ret = 0;
    for (int i = 0; i < len; ++i) {
        while (!increaseStack.empty() && heights[increaseStack.top()] > heights[i]) {
            // 找出当前的位置
            int pos = increaseStack.top();
            increaseStack.pop();
            // 左边界为l,右边界为i
            int l = increaseStack.empty() ? -1 : increaseStack.top();
            ret = std::max(ret, heights[pos] * (i - 1 - l));
        }
        increaseStack.push(i);
    }
    return ret;
}

int largestRectangleArea2(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);

    stack<int> mono_stack;
    // 左边第一个比i 低的为其左边界
    for (int i = 0; i < n; ++i) {
        while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
            mono_stack.pop();
        }
        left[i] = mono_stack.empty() ? -1 : mono_stack.top();  // 左边界
        mono_stack.push(i);
    }
    mono_stack = stack<int>{};
    for (int i = n - 1; i >= 0; --i) {
        while (!mono_stack.empty() && heights[mono_stack.top() >= heights[i]]) {
            mono_stack.pop();
        }
        right[i] = mono_stack.empty() ? n : mono_stack.top();  //右边界
        mono_stack.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    }
    return ans;
}
}  // namespace _84largestRectangleInHistogram

namespace _20stack {  //! 20. 有效的括号
bool isValid(string s) {
    int n = s.size();
    if (n % 2 == 1) return false;
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    stack<char> stk;
    for (char ch : s) {
        if (pairs.count(ch)) { // 判断ch是否为右括号
            if (stk.empty() || stk.top() != pairs[ch]) { // 栈顶元素与 ch不匹配
                return false;
            }
            stk.pop(); // 栈顶元素与ch匹配，弹出栈顶
        } else {
            stk.push(ch); // ch如果为左括号则压入栈中
        }


    }
    return stk.empty();
}
}  // namespace _20stack

namespace _678checkValidString {
bool checkValidString(string s)
{
    int n = s.length();
    stack<int> leftStk;
    stack<int> starStk;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            leftStk.push(i);
        } else if (s[i] == '*') {
            starStk.push(i);
        } else {
            // 当匹配到')' 时优先使用 '('进行匹配
            if (!leftStk.empty()) {
                leftStk.pop();
            } else {
                if(!starStk.empty()) {
                    starStk.pop();
                } else {
                    return false;
                }
            }
        }
    }

    if (starStk.size() < leftStk.size()) return false;
    
    while (!leftStk.empty()) {
        // 要保证'*' 在'(' 右边
        if (leftStk.top() > starStk.top()) {
            return false;
        }
        leftStk.pop(); starStk.pop();
    }
    
    return true;
}
}

//! 括号匹配问题
namespace _ShopeeComputeString {
string computeString(string str) {
    int n = str.size();
    stack<pair<int, string>> stk;
    int curNum = 0;
    string curStr;

    for (int i = 0; i < n; ++i) {
        if (str[i] == '*') continue;

        if ('0' <= str[i] && str[i] <= '9') {
            curNum = curNum * 10 + (str[i] - '0');
        } else if (str[i] == '[') {
            // 保存 []之前的字符串和数字
            stk.push(make_pair(curNum, curStr));
            curNum = 0;
            curStr.clear(); // curStr表示[]里的字符串
        } else if (str[i] == ']') {
            auto& t = stk.top(); // 将[]之前的 字符串 + 数字取出
            string tmp;
            for (int i = 0; i < t.first; ++i) tmp += curStr;
            curStr = t.second + move(tmp);
            stk.pop();
        } else {
            curStr += str[i];
        }
    }

    return curStr;
}
}


//!单调栈======================================================
//? 去除字符串中重复的字母，并保证返回的字典序最小
//? "bcabc" ---> "abc"; "cbacdcbc"  ---> "acdb"
namespace _316removeDuplicateLetters{
    //! s[i] > s[i+1]; s[i] --> 关键字符
string removeDuplicateLeters(string s)
{
    // 分别记录元素是否在栈中 和 元素的个数
    vector<int> vis(26), num(26);
    for (char ch : s) num[ch-'a']++;

    string stk;
    for (char ch : s) {
        if (!vis[ch - 'a']) {
            while (!stk.empty() && stk.back() > ch) {
                if (num[stk.back() - 'a'] > 0) { // 后面还有栈顶这个字符，就弹出去
                    vis[stk.back() - 'a'] = 0;
                    stk.pop_back();
                } else {
                    break;
                }
            }
            vis[ch - 'a'] = 1;
            stk.push_back(ch);
        }
        num[ch - 'a'] -= 1;
    }
    return stk;
}
}

namespace _496NextGreaterNumber {
//* 暴力解法，在nums2中找到nums1[i], 再在nums2中找到比nums1[i]大的数
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    vector<int> res(n1);
    if (n1 < 1) return res;

    for (int i = 0; i < n1; ++i) {
        int curVal = nums1[i];
        // 在nums2中找到 nums1[i]
        auto j = find(nums2.begin(), nums2.end(), curVal);
        // 在nums2中找到比nums1[i]大的数
        auto nextJ = find_if(next(j), nums2.end(), [curVal](const int val){
                        return val > curVal;
                    });
        res[i] = nextJ == nums2.end() ? -1 : *nextJ;
    }
    return res;
}
//* 单调栈解法=======================================
namespace _1{
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
{
    unordered_map<int, int> m; // 记录 nums1[i] : 下一个比他的元素
    stack<int> stk;

    #if 0
    // 正向
    for (int i = 0; i < nums1.size(); ++i) {
        while (!stk.empty() && stk.top() < nums2[i]) {
            m[stk.top()] = nums2[i];
            stk.pop();
        }
        stk.push(nums2[i]);
    }
    #endif

    // 逆向
    for (int i = nums2.size()-1; i >= 0; --i) {
        while (!stk.empty() && stk.top() < nums2[i]) {
            stk.pop();
        }
        stk.empty() ? m[nums2[i]] = -1 : m[nums2[i]] = stk.top();
        stk.push(nums2[i]);
    }

    vector<int> ans; ans.reserve(nums1.size());
    for (int val : nums1) ans.push_back(m[val]);

    return ans;
}
}
}  // namespace _496NextGreaterNumber

namespace _503nextGreaterElements
{
//! 逆向
vector<int> nextGreaterElements(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> res(n);
    stack<int> s;
    // 假装这个数组长度翻倍了
    for (int i = 2*n - 1; i >= 0; --i) {
        while (!s.empty() && s.top() <= nums[i % n]) {
            s.pop();
        }
        res[i % n] = s.empty() ? -1 : s.top();
        s.push(nums[i % n]);
    }
    return res;
}
//! 正向
namespace _1{
vector<int> nextGreaterElements(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> ret(n, -1);
    stack<int> stk;
    for (int i = 0; i < n*2 -1; ++i) {
        while (!stk.empty() && nums[stk.top()] < nums[i % n]) {
            ret[stk.top()] = nums[i % n];
            stk.pop();
        }
        stk.push(i % n);
    }
    return ret;
}
}
}

namespace _556nextGreaterElement
{
int nextGreaterElement(int n) {
   string str = to_string(n);
   if (!next_permutation(str.begin(), str.end())) {
       return -1;
   }

   long long ans = stoll(str);
   if (ans > INT_MAX) return -1;
   return ans;
}   
}

namespace _739dailyTemperatures
{
//! 正向
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> ans(n);
    stack<int> s;

    for(int i = 0; i < n; ++i) {
        while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
            ans[s.top()] = i - s.top();
            s.pop();
        }
        s.push(i);
    }
    return ans;
}
//! 反向
namespace _1 {
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> ans(n);
    stack<int> s;

    for (int i = n-1; i >=0 ; ++i) {
        //* 保持栈中的元素比遍历到的元素大
        while (!s.empty() && temperatures[s.top()] <= temperatures[i]) {
            s.pop();
        }
       if (!s.empty()) ans[i] = s.top() - i;
       s.push(i);
    }
    return ans;
}   
}
}


//* 柱形图中的最大矩形*********************************************
namespace _84largestRectangleArea {
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    // 右边界
    vector<int> right(n, n);
    stack<int> s1;
    for (int i = 0; i < n; ++i) {
        while (!s1.empty() && heights[s1.top()] > heights[i]) {
            right[s1.top()] = i;
            s1.pop();
        }
        s1.push(i);
    }

    // 左边界
    vector<int> left(n, -1);
    stack<int>().swap(s1);
    for (int i = n-1; i >= 0; --i) {
        while (!s1.empty() && heights[s1.top()] > heights[i]) {
            left[s1.top()] = i;
            s1.pop();
        }
        s1.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, heights[i] * (right[i] - left[i] - 1));
    }

    return ans;
}
//*************************************************************************
namespace _1 {
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n, n);

    stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {
            right[stk.top()] = i;
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, (right[i]-left[i]-1)*heights[i]);
    }
    return ans;
}
}

}

//* 矩阵里的最大矩形***********************************************
namespace _85maximalRectangle {
    
int maximalRectangle(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) return 0;

    int n = matrix[0].size();
    vector<vector<int>> left(m, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == '1') {
                left[i][j] = (j == 0 ? 0 : left[i][j-1]) + 1;
            }
        }
    }

    int ret = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == '0') continue;

            int width = left[i][j];
            int area = width;
            for (int k = i - 1; k >= 0; --k) {
                if (left[k][j] == 0) break;
                width = min(width, left[k][j]);
                area = max(area, (i-k+1)*width);
            }
            ret = max(ret, area);
        }
    }

    return ret;
}
}


//! 计算器================================

//! 基本计算器 + - ()
namespace _224calculate {
    int calculate(string s) {
        stack<int> ops; // 记录括号之前的符号
        ops.push(1);
        int sign = 1;

        int ret = 0;
        int n = s.size();
        int i = 0;
        while (i < n) {
            if (s[i] == ' ') {
                ++i;
            } else if (s[i] == '+') {
                sign = ops.top();
                ++i;
            } else if (s[i] == '-') {
                sign = -ops.top();
                ++i;
            } else if (s[i] == '(') {
                ops.push(sign);
                ++i;
            } else if (s[i] == ')') {
                ops.pop();
                ++i;
            } else {
                int num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
}

//! 227基本计算器2 只有 + - * / 和括号
namespace _227calculate {
    int calculate(string s) {
        vector<int> stk;
        char preSign = '+';
        int num = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
            }
            if ((!isdigit(s[i]) && s[i] != ' ') || i == n-1) {
                switch (preSign) {
                    case '+':
                        stk.push_back(num); break;
                    case '-':
                        stk.push_back(-num); break;
                    case '*':
                        stk.back() *= num; break;
                    case '/':
                        stk.back() /= num; break;
                }
                preSign = s[i];
                num = 0;
            }
        }
        return accumulate(stk.cbegin(), stk.cend(), 0);
    }
}


namespace _772calculate {
    // 递归调用的关键在于，需要计算成对括号的位置，使用全局变量index来实现
    int index = 0;

    int cal(string& s) {
        vector<int> stk;
        int num = 0;
        char sign = '+';
        for (; index < s.size(); ++index) {
            char c = s[index];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }

            if (c == '(') {
                ++index; // index指针指到下一个字符
                num = cal(s);
            }

            //! 当遇到了新的运算符，就要对上一个运算法sign和累计的数字num作运算
            // 空格直接无视，i继续前进
            if ((!isdigit(c) && c != ' ') || index == s.size()-1) {
                int pre = 0;
                switch (sign) {
                    case '+':
                        stk.push_back(num); break;
                    case '-':
                        stk.push_back(-num); break;
                    case '*':
                        pre = stk.back(); stk.pop_back();
                        stk.push_back(pre * num); break;
                    case '/':
                        pre = stk.back(); stk.pop_back();
                        stk.push_back(pre / num); break;
                }
                sign = c;
                num = 0; // 计数归位
            }
            if (c == ')') break;
        }

        return accumulate(stk.begin(), stk.end(), 0);
    }

    int calculate(string s) {
        return cal(s);
    }
}
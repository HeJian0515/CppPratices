#pragma once
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

namespace _496NextGreaterNumber {
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
}
}  // namespace _496NextGreaterNumber

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
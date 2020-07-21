#pragma once

#include <stack>
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

        stack<int> increaseStack; // 单调递增栈存放的是位置
        int ret = 0;
        for (int i = 0; i < len; ++i) {
            while (!increaseStack.empty() && heights[increaseStack.top()]>heights[i] ) {
                // 找出当前的位置
                int pos = increaseStack.top();
                increaseStack.pop();
                // 左边界为l,右边界为i
                int l = increaseStack.empty() ? -1 : increaseStack.top();
                ret = std::max(ret, heights[pos]*(i-1-l));
            }
            increaseStack.push(i);
        }
        return ret;
    }

    int largestRectangleArea2(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);

        stack<int> mono_stack;
        for (int i = 0; i < n; ++i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();
            }
            left[i] = mono_stack.empty() ? -1 : mono_stack.top(); // 左边界
            mono_stack.push(i);
        }
        mono_stack = stack<int>{};
        for (int i = n-1; i >= 0; --i) {
            while (!mono_stack.empty() && heights[mono_stack.top() >= heights[i]]) {
                mono_stack.pop();
            }
            right[i] = mono_stack.empty() ? n : mono_stack.top(); //右边界
            mono_stack.push(i);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] -1) * heights[i]);
        }
        return ans;

    }
}
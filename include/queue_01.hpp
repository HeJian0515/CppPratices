#pragma once

#include <vector>
#include <deque>
#include <queue>

using namespace std;

// 队列实现栈
namespace _225MyStack {
class MyStack {
    queue<int> q1;
    queue<int> q2;
public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        q1.swap(q2);
    }

    int pop() {
        int ret = q1.front();
        q1.pop();
        return ret;
    }

    int top() {
        return q1.front();
    }

    bool empty() {
        return q1.empty();
    }
};
}

// 滑动窗口的最大值
namespace _239MaxValueWindow {
// 优先队列
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < k; ++i) {
       q.emplace(nums[i], i);
    }

    vector<int> ans = {q.top().first};
    for (int i = k; i < n; ++i) {
        q.emplace(nums[i], i);
        // 弹出不在窗口内的元素
        while (q.top().second <= i-k) {
            q.pop();
        }
        ans.push_back(q.top().first);
    }
    return ans;
}

namespace __deque {
vector<int> naxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;

    // 保证队列内元素单调递减
    for (int i = 0; i < k; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }

    vector<int> ans{nums[q.front()]};
    for (int i = k; i < n; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.front() <= i- k) {
            q.pop_front();
        }
        ans.push_back(nums[q.front()]);
    }
    return ans;
}
}
}
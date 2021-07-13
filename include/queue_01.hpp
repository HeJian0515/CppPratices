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
}
}

namespace _239MaxValueWindow {
    class MonotonicQueue {
        private:
            deque<int> data;
        public:
            void push(int n) {
                while(!data.empty() && data.back() < n) {
                    data.pop_back();
                }
                data.push_back(n);
            }

            int max() {return data.front();}

            void pop(int n) {
                if (!data.empty() && data.front() == n) {
                    data.pop_front();
                }
            }

    };


    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            if (i < k-1) { //! 先填满窗口前 k-1
                window.push(nums[i]);
            } else { // 窗口向前滑动
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i-k+1]);
            }
        }
        return res;
    }
}
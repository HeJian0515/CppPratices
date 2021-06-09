#pragma once
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

namespace _16cur {
vector<int> divingBoard(int shorter, int longer, int k) {
  if (k < 1) return {};
  if (shorter == longer) return {shorter * k};
  vector<int> res(k + 1, 0);  // 节省vector重新分配空间的时间
  for (int x = 0; x <= k; ++x) {
    res[x] = (longer * x + shorter * (k - x));  // 关于x单调递增，故不会有重复值
  }
  return res;
}
}  // namespace _16cur

namespace _350Array {  //! 350. 两个数组的交集 II
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
  if (nums1.size() < 1 || nums2.size() < 1) return {};
  unordered_map<int, int> map;

  for (int num : nums1) {
    ++map[num];
  }
  vector<int> res;

  for (int num : nums2) {
    if (map.count(num)) {
      res.push_back(num);
      --map[num];
      if (map[num] == 0) {
        map.erase(num);
      }
    }
  }
  return res;
}
}  // namespace _350Array

// 维护一个有序序列，初始时有序序列只有一个元素，每次将一个新的元素插入到有序序列中，将有序序列的长度增加 11，直到全部元素都加入到有序序列中。
namespace _147List {
    ListNode* insertionSortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode dummy(0);
        ListNode* dummyHead = &dummy;
        dummyHead->next = head;
        ListNode* lastSorted = head; // 为链表的已排序部分的最后一个节点
        ListNode* curr = head->next; // 为待插入的元素
        while (curr != nullptr) {
            if (lastSorted->val <= curr->val) {
                lastSorted = lastSorted->next;
            } else {
                // 从头开始找比curr大的节点，将curr插在前面
                ListNode* prev = dummyHead;
                while (prev->next->val <= curr->val) {
                    prev = prev->next;
                }
                lastSorted->next = curr->next; // 记录下一个要插入的节点
                curr->next = prev->next;
                prev->next = curr;
            }
            curr = lastSorted->next;
        }
        return dummyHead->next;
    }
}    


// 计算[0...num]中各个数1的个数
namespace _338countBits
{
vector<int> countBits(int num) {
    vector<int> bits(num + 1);
    int highBit = 0;
    for (int i = 1; i <= num; ++i) {
        if ((i & (i-1)) == 0) {
            highBit = i;
        }
        bits[i] = bits[i - highBit] + 1;
    }
    return bits;
}

vector<int> countBits_1(int num) {
    vector<int> bits(num + 1);
    for (int i = 0; i <= num; ++i) {
        bits[i] = bits[i>>1] + (i & 1);
    }
    return bits;
}

//! 动态规划
vector<int> countBits_2(int num) {
    vector<int> bits(num+1);
    for (int i = 1; i <= num; ++i) {
        bits[i] = bits[i & (i-1)] + 1;
    }
    return bits;
}
}

//! 前缀和 和 哈希表
namespace _523checkSubarraySum
{
bool checkSubarraySum(vector<int>& nums, int k)
{
    int m = nums.size();
    if (m < 2) return false;

    unordered_map<int, int> mp; // 记录余数最早出现的位置
    mp[0] = -1;
    int remainder = 0;
    for (int i = 0; i < m; ++i) {
        remainder = (remainder + nums[i]) % k; // sum[0...i]的余数
        if (mp.count(remainder)) {
            int prevIndex = mp[remainder];
            if (i - prevIndex >= 2) {
                return true;
            }
        } else {
            mp[remainder] = i;
        }
    }
    return false;
}
}

//! 前缀和 和 哈希表
namespace _525findMaxLength
{
int findMaxLength(vector<int>& nums)
{
    unordered_map<int, int> sum2Index{{0, -1}};
    int cnt = 0;

    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (nums[i] == 1) {
            ++cnt;
        } else {
            --cnt;
        }
        
        if (sum2Index.count(cnt)) {
            ans = max(ans, i - sum2Index[cnt]);
        } else {
            sum2Index[cnt] = i; 
        }
    }
    return ans;
}
}
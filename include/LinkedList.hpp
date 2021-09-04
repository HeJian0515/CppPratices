#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace {
//* 打印链表
void printList(ListNode* head) {
    while (head) {
        cout << head->val  << "->";
        head = head->next;
    }
    cout << "NULL" << endl;
}

//* 递归反转整个链表
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;

    auto newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// 将链表的前 n 个节点反转（n <= 链表长度）
ListNode* reverseListForwardN(ListNode* head, int n, ListNode*& successor) {
    if (n == 1) {
        // 记录n+1个节点
        successor = head->next;
        return head;
    }
    // 以head->next为起点，需要反转前n-1个节点
    auto last = reverseListForwardN(head->next, n - 1, successor);

    head->next->next = head;
    head->next = successor;
    return last;
}

// 反转链表的一部分
ListNode* reverseBetween(ListNode* head, int m, int n, ListNode*& successor) {
    if (m == 1) return reverseListForwardN(head, n, successor);
    
    head->next = reverseBetween(head->next, m - 1, n -1, successor);
    return head;
} 

//* 迭代反转整个链表
ListNode* reverseList_it(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode *tail = nullptr;
   // 拆成两个链表 tail 和 head 每次都将head的头变成 tail的头
    while (head) {
        auto tmp = head->next; // 下一次的头

        head->next = tail; 
        tail = head;
        head = tmp;
    }
   return tail;
}
}

namespace _92reverseBetween {

//! 反转链表中间一段
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummyNode(-1);
    ListNode* dummy = &dummyNode;
    dummy->next = head;
    ListNode* pre = dummy;
    for (int i = 0; i < left - 1; ++i) {
        pre = pre->next;
    }
    ListNode* cur = pre->next;
    ListNode* next;
    for (int i = 0; i < right - left; ++i) {
        next = cur->next;
        cur->next = next->next;
        next->next = pre->next;
        pre->next = next;
    }
    return dummy->next;
}

}

//! 求链表交点
namespace _Offer52getIntersectionNode
{
ListNode* getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode* aCur = headA;
    ListNode* bCur = headB;

    while (aCur != bCur) {
        aCur = aCur != nullptr ? aCur->next : headB;
        bCur = bCur != nullptr ? bCur->next : headA;
    }
    return aCur;
}
}

namespace _ShopeeReverseN
{
ListNode* newReverse(ListNode* head, ListNode* tail)
{
    ListNode* pre = nullptr;
    ListNode* cur = head;

    while (cur != nullptr && cur != tail) { // 只反转[head, tail) 左闭右开
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    return pre;
}

ListNode* reverseLinkedList(ListNode* head, int n) {
    if (head == nullptr || head->next == nullptr || n <= 1) return head;
    
    ListNode* nHead = head;
    ListNode* nTail = head;

    for (int i = 0; i < n; ++i) {
        if (nTail == nullptr) break;
        nTail = nTail->next;
    }

    ListNode* newHead = newReverse(nHead, nTail);
    head->next = reverseLinkedList(nTail, n);
    return newHead;
}
}

//! 烧饼排序==========================================================================
namespace _969pancakeSort
{
vector<int> res;
void sort(vector<int>& arr, int n) 
{
    if (n == 1) return;
    // 找到最大的，放到最后
    auto maxIt = max_element(arr.begin(), arr.begin()+n);
    if (maxIt != arr.begin()) {
         res.push_back(maxIt - arr.begin()+1);
        reverse(arr.begin(), maxIt); // 将最大的，先放到最前面
    }
    res.push_back(n);
    reverse(arr.begin(), arr.begin()+n); // 将最大的翻转到最后

    if (is_sorted(arr.begin(), arr.begin()+n-1)) {
        return;
    }
    sort(arr, n-1);
}

vector<int> pancakeSort(vector<int>& arr)
{
    sort(arr, arr.size());
    return res;
}
//!=============================================================
vector<int> pancakeSort_1(vector<int>& arr)
{
    vector<int> ans;
    int n = arr.size();

    vector<int> indies(n); // 记录arr中元素的位置
    for (int i = 0; i < n; ++i) indies[i] = i+1;

    // 根据arr中元素从大到小排序， 最大的元素位置排在最前面， 次大的元素位置排在第二位...
    sort(indies.begin(), indies.end(), [&arr](const int i, const int j){
        return arr[i-1] > arr[j-1];
    });
    // i, f的含义可理解为要翻转前i, f个元素
    for (int i : indies) {  // 每次都找到还没排序好的最大元素
        for (int f : ans) { // 前面的操作(翻转)可能让这次最大元素的位置发生了改变
            if (i <= f) { // 如果这次要放到最后的元素在前面翻转序列之内
                i = f+1-i;
            }
        }
        ans.push_back(i); // 表示把最大元素放到最前面
        ans.push_back(n--);// 将最大元素放到最后面
    }
    return ans;
}
}

//!=========================================合并k个升序链表============================================
namespace _23mergeKLists {

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
   if (l1 == nullptr || l2 == nullptr) return l1 ? l1 : l2;

   ListNode head, *tail = &head, *l1Ptr = l1, *l2Ptr = l2;
   while (l1Ptr && l2Ptr) {
       if (l1Ptr->val < l2Ptr->val) {
           tail->next = l1Ptr;
           l1Ptr = l1Ptr->next;
       } else {
           tail->next = l2Ptr;
           l2Ptr = l2Ptr->next;
       }
       tail = tail->next;
   }
   tail->next = (l1Ptr ? l1Ptr : l2Ptr);
   return head.next;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode* ans = nullptr;
    for (int i = 0; i < lists.size(); ++i) {
        ans = mergeTwoLists(ans, lists[i]);
    }
    return ans;
}

//*=======================分治法============================
namespace _1 {
ListNode* merge(vector<ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = l + (r - l)/2;
    return mergeTwoLists(merge(lists, l, mid), merge(lists, mid+1, r));
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    return merge(lists, 0, lists.size()-1);
}
}

//!! *=====================优先队列==================================
namespace _2 {

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        int k = lists.size();
        if (k == 1) return lists[0];
        auto cmp = [] (const ListNode* l1, const ListNode* l2) {
            return l1->val > l2->val;
        };
        priority_queue<ListNode*, vector<ListNode*>,decltype(cmp)> q(cmp);
        for(auto head : lists) {
            if (head) q.push(head);
        }

        ListNode d, *p = &d;
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            p->next = t;
            p = p->next;

            t = t->next;
            if (t) q.push(t);
        }

        return d.next;
    }
}
}

//! =========================链表排序============================================
//! 一般使用归并排序===============================================================
namespace _148sortList {

    ListNode* merge(ListNode* a, ListNode* b) {
        if (a == nullptr || b == nullptr) return a ? a : b;
        ListNode head, *tail = &head, *aCur = a, *bCur = b;

        while (aCur && bCur) {
            if (aCur->val < bCur->val) {
                tail->next = aCur;
                aCur = aCur->next;
            } else {
                tail->next = bCur;
                bCur = bCur->next;
            }
            tail = tail->next;
        }
        tail->next = (aCur ? aCur : bCur);

        return head.next;
    }

    ListNode* mergeSort(ListNode* head, ListNode* tail) {
        if (head == nullptr) return head;
        if (head->next == tail) {
            head->next = nullptr; //! 使head成为一个具有一个节点的链表
            return head;
        }
        ListNode *slow = head, *fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        ListNode *mid = slow;
        //! 左闭右开
        return merge(mergeSort(head, mid), mergeSort(mid, tail));
    }

    ListNode* sortList(ListNode* head) {
        return mergeSort(head, nullptr);
    }

//!===============自底向上================================================
namespace _1 {
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) return head;

        int len = 0;
        ListNode* node = head;
        while (node) {
            ++len;
            node = node->next;
        }

        ListNode dummy(0, head);

        for (int subLen = 1; subLen < len; subLen <<= 1) {
            ListNode* prev = &dummy, *curr = dummy.next;
            while (curr) {
                // 构建head1为头结点，长度为subLen的链表
                ListNode* head1 = curr;
                for (int i = 1; i < subLen && curr->next; ++i) {
                    curr = curr->next;
                }

                // 构建head2为头节点，长度为subLen的链表
                ListNode* head2 = curr->next;
                curr->next = nullptr;
                curr = head2;
                for (int i = 1; i < subLen && curr && curr->next; ++i) {
                    curr = curr->next;
                }

                // 记录下一个长度为subLen的头节点
                ListNode* next = nullptr;
                if (curr) {
                    next = curr->next;
                    curr->next = nullptr;
                }

                // 合并排好序的链表
                ListNode* merged = merge(head1, head2);
                // 移动到排序好的链表尾部
                prev->next = merged;
                while (prev->next) {
                    prev = prev->next;
                }
                curr = next; // 指向未排序的节点
            }
        }

        return dummy.next;
    }
}
}


//! K个一组翻转链表
namespace _25reverseKGroup  {
    ListNode* reverseK(ListNode* pre, int k) {
        if (pre == nullptr || pre->next == nullptr) return nullptr; 
        ListNode* cur = pre;
        for (int i = 0; i < k; ++i) {
            cur = cur->next;
            if (cur == nullptr) return nullptr;
        }
        cur = pre->next; // cur始终指向第一个要反转的节点
        for (int i = 0; i < k-1; ++i) {
            auto next = cur->next;
            cur->next = next->next;
            next->next = pre->next; //! 插到第一个位置
            pre->next = next;
        }
        return cur;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode d; d.next = head;
        ListNode* pre =  &d;
        while (pre) {
            pre = reverseK(pre, k);
        }
        return d.next;
    }
}

//! 判断环形链表
namespace _141hasCycle {
    bool hasCycle(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }

        return false;
    }
}

//! 找到环形链表开始位置
namespace _142detectCycle {
    ListNode* detectCycle(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) break;
        }
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }

        slow = head;
        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
}


//! 删除链表的倒数第N个节点
namespace _19removeNthFromEnd {
    ListNode* findFromEnd(ListNode* head, int k) {
        ListNode* p1 = head;
        for (int i = 0; i < k; ++i) {
            p1 = p1->next;
        }
        ListNode* p2 = head;
        while (p1) {
            p1 = p1->next;
            p2 = p2->next;
        }

        return p2;
    }

    ListNode* removeNthFormEnd(ListNode* head, int n) {
        ListNode d; d.next = head;
        // 要先找到倒数第n+1个节点
        ListNode* x = findFromEnd(&d, n+1);
        x->next = x->next->next;
        return d.next;
    }
}

//! 删除排序链表中的重复元素==========================================
namespace _83deleteDuplicates {
    ListNode* deleteDulicates(ListNode* head) {
        if (head == nullptr) return nullptr;
        ListNode *slow = head, *fast = head;
        while (fast) {
            if (fast->val != slow->val) {
                slow->next = fast;
                slow = slow->next;
            }
            fast = fast->next;
        }

        // 断开与后面重复元素的连接
        slow->next = nullptr;
        return head;
    }  
}
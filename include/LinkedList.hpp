#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
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

ListNode* successor = nullptr;
ListNode* reverseN(ListNode* head, int n) {
    if (1 == n) {
        // 记录第 n+1 个节点
        successor = head->next;
        return head;
    }
    // 以head->next为起点，需要反转前n-1个节点
    ListNode* newHead = reverseN(head->next, n-1);

    head->next->next = head;
    // 让反转之后的 head 节点和后面的节点连起来
    head->next = successor;
    return newHead;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (1 == left) {
        return reverseN(head, right);
    }

    head->next = reverseBetween(head->next, left-1, right-1);
    return head;
}

}

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

namespace _968pancakeSort
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

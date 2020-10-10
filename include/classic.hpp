#include <vector>
#include <iostream>
using namespace std;

//!======================================================== 反转链表
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

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

    ListNode *newHead = nullptr;
   // 拆成两个链表， 再结合起来
    while (head) {
        auto tmp = head->next;

        head->next = newHead;
        newHead = head;
        head = tmp;
    }
   return newHead;
}

//!======================================================== 反转链表
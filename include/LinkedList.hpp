#include <algorithm>
#include <numeric>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
